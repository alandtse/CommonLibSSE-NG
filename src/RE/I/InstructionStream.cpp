#include "RE/B/BSBitWriter.h"
#include "RE/U/UnlinkedTypes.h"

#include "RE/C/CodeTasklet.h"
#include "RE/M/MemoryManager.h"
#include "RE/S/ScriptFunction.h"

namespace
{
	using RE::BSScript::ByteCode::Argument;
	using OpCode = RE::BSScript::Internal::CodeTasklet::OpCode;

	[[nodiscard]] bool IsJumpOpcode(std::uint32_t a_opcode)
	{
		return a_opcode >= static_cast<std::uint32_t>(OpCode::kJMP) && a_opcode <= static_cast<std::uint32_t>(OpCode::kJMPF);
	}

	[[nodiscard]] std::uint32_t CallCountBias(std::uint32_t a_opcode)
	{
		switch (static_cast<OpCode>(a_opcode)) {
		case OpCode::kCALLMETHOD:
		case OpCode::kCALLSTATIC:
			return 3;
		case OpCode::kCALLPARENT:
			return 2;
		default:
			return 0;
		}
	}
}

namespace RE
{
	namespace BSScript
	{
		namespace UnlinkedTypes
		{
			InstructionStream::InstructionStream(const std::uint32_t a_recordCount) :
				threadScrapHeap(MemoryManager::GetSingleton()->GetThreadScrapHeap()),
				functionCodeSize(a_recordCount),
				argumentCount(0),
				localVarBitCount(0),
				memberVarBitCount(0),
				recordBuffer(a_recordCount, 8),
				records(recordBuffer.get()),
				recordWriteCursor(recordBuffer.get()),
				instructionListHead(nullptr),
				tailNode(nullptr),
				tailNextLink(&instructionListHead) {}

			InstructionStream::InstructionStream(InstructionStream&& a_rhs) noexcept :
				InstructionStream(0)
			{
				*this = std::move(a_rhs);
			}

			InstructionStream& InstructionStream::operator=(InstructionStream&& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					std::swap(threadScrapHeap, a_rhs.threadScrapHeap);
					std::swap(functionCodeSize, a_rhs.functionCodeSize);
					std::swap(argumentCount, a_rhs.argumentCount);
					std::swap(localVarBitCount, a_rhs.localVarBitCount);
					std::swap(memberVarBitCount, a_rhs.memberVarBitCount);
					recordBuffer.swap(a_rhs.recordBuffer);
					std::swap(records, a_rhs.records);
					std::swap(recordWriteCursor, a_rhs.recordWriteCursor);
					std::swap(instructionListHead, a_rhs.instructionListHead);
					std::swap(tailNode, a_rhs.tailNode);
					std::swap(tailNextLink, a_rhs.tailNextLink);
					if (tailNextLink == &a_rhs.instructionListHead) {
						tailNextLink = &instructionListHead;
					}
					if (a_rhs.tailNextLink == &instructionListHead) {
						a_rhs.tailNextLink = &a_rhs.instructionListHead;
					}
				}
				return *this;
			}

			InstructionStream::~InstructionStream()
			{
				for (auto* node = instructionListHead; node != nullptr;) {
					auto* next = node->next;
					for (std::uint32_t i = 0; i < node->argCount; ++i) {
						node->args[i].~Argument();
					}
					threadScrapHeap->Deallocate(node);
					node = next;
				}
			}

			void InstructionStream::ForEachInstruction(InstructionFunctor& a_functor) const
			{
				const auto*   node = instructionListHead;
				std::uint32_t argIndex = 0;

				for (std::uint32_t n = 0; n < functionCodeSize; ++n) {
					const auto record = records[n];

					if (!a_functor.VisitInstruction(record.opcode, record.info)) {
						// false ends the whole walk
						break;
					}

					bool skipArgs = false;
					for (std::uint32_t j = 0; j < static_cast<std::uint16_t>(record.info); ++j) {
						if (!skipArgs) {
							skipArgs = !a_functor.VisitArgument(node->args[argIndex]);  // false only mutes the rest of this instruction
						}
						if (++argIndex >= node->argCount) {
							node = node->next;
							argIndex = 0;
						}
					}
				}
			}

			void InstructionStream::Pack(ByteCode::PackedInstructionStream& a_out) const
			{
				// pass 1: size. The jump target width n is the smallest n with 2^n > fixedBits + n * jumpCount
				CountInstructionInfo counter(localVarBitCount, memberVarBitCount);
				ForEachInstruction(counter);

				std::uint32_t jumpBits = 1;
				while ((std::uint64_t{ 1 } << jumpBits) <= std::uint64_t{ counter.fixedBits } + std::uint64_t{ jumpBits } * counter.jumpCount) {
					++jumpBits;
				}
				const std::uint32_t totalBits = counter.fixedBits + jumpBits * counter.jumpCount;

				std::uint64_t* words = nullptr;
				if (totalBits != 0) {
					const std::size_t byteCount = ((static_cast<std::size_t>(totalBits) + 63) / 64) * 8;
					words = static_cast<std::uint64_t*>(RE::malloc(byteCount));
					std::memset(words, 0, byteCount);
				}

				// pass 2: write
				struct Fixup
				{
					std::uint32_t bitPosition;
					std::uint32_t targetIndex;
				};
				std::vector<Fixup> fixups;
				fixups.reserve(counter.jumpCount);

				BSBitWriter         writer(words);
				const std::uint64_t jumpMask = (std::uint64_t{ 1 } << jumpBits) - 1;

				auto*         node = instructionListHead;
				std::uint32_t argIndex = 0;
				for (std::uint32_t i = 0; i < functionCodeSize; ++i) {
					auto&      record = records[i];
					const auto opcode = record.opcode;
					const auto argCount = static_cast<std::uint16_t>(record.info);

					record.unk08 = writer.Position();
					writer.Write(opcode & 0x3F, 6);
					if (const auto bias = CallCountBias(opcode); bias != 0) {
						writer.Write((argCount - bias) & 0x1FF, 9);
					}

					for (std::uint32_t k = 0; k < argCount; ++k) {
						const auto& arg = node->args[argIndex];
						if (IsJumpOpcode(opcode) && k == static_cast<std::uint32_t>(argCount - 1)) {
							const std::int32_t  relative = arg.GetType() == Argument::Type::kInt ? arg.GetInt() : 0;  // GetIntLiteral leaves 0 for a non-int
							const std::uint32_t absoluteTarget = static_cast<std::uint32_t>(relative + static_cast<std::int32_t>(i));
							fixups.push_back(Fixup{ .bitPosition = writer.Position(), .targetIndex = absoluteTarget });  // unmasked: pass 3's functionCodeSize check needs the true value
							writer.Write(absoluteTarget & jumpMask, jumpBits);                                           // placeholder only; pass 3 overwrites this with the real bit offset
						} else {
							arg.WriteToBitStream(writer, localVarBitCount, memberVarBitCount);
						}

						if (++argIndex >= node->argCount) {
							node = node->next;
							argIndex = 0;
						}
					}
				}
				assert(writer.Position() == totalBits);

				// pass 3: instruction index -> bit offset (past-the-end = totalBits)
				for (const auto& fixup : fixups) {
					const std::uint32_t bitOffset = fixup.targetIndex < functionCodeSize ? records[fixup.targetIndex].unk08 : totalBits;
					writer.WriteAt(fixup.bitPosition, bitOffset, jumpBits);
				}

				a_out.Release();
				a_out.numInstructionBits = totalBits;
				a_out.jumpTargetBitCount = static_cast<std::uint16_t>(jumpBits);
				a_out.localVariableBitCount = static_cast<std::int8_t>(localVarBitCount);
				a_out.memberVariableBitCount = static_cast<std::int8_t>(memberVarBitCount);
				a_out.instructions = words;
			}

			void InstructionStream::PackTo(ByteCode::PackedInstructionStream& a_out)
			{
				Pack(a_out);
				*this = InstructionStream(0);
			}

			bool CountInstructionInfo::VisitInstruction(std::uint32_t a_opcode, std::uint32_t a_info)
			{
				opcode = a_opcode;
				argCount = static_cast<std::uint16_t>(a_info);
				argIndex = 0;
				fixedBits += 6 + (CallCountBias(a_opcode) != 0 ? 9 : 0);
				return true;
			}

			bool CountInstructionInfo::VisitArgument(ByteCode::Argument& a_arg)
			{
				if (IsJumpOpcode(opcode) && argIndex == argCount - 1) {
					++jumpCount;
				} else {
					fixedBits += a_arg.GetBitCount(localBits, memberBits);
				}
				++argIndex;
				return true;
			}

		}
	}
}

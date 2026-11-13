#include "RE/P/PackedInstructionStream.h"

#include "RE/A/Argument.h"
#include "RE/C/CodeTasklet.h"

namespace
{
	void ReleaseArgument(RE::BSScript::BSBitReader& a_reader, std::uint32_t a_localBits, std::uint32_t a_memberBits)
	{
		RE::BSScript::ByteCode::Argument argument{};
		argument.ReadFromBitStream(a_reader, a_localBits, a_memberBits);
		if (argument.IsString() || argument.IsIdentifier()) {
			auto ptr = argument.GetString().data();
			RE::BSStringPool::Entry::release(ptr);  // releases the stream's original reference
		}
		// argument's own destructor releases the reference ReadFromBitStream just took
	}
}

namespace RE::BSScript::ByteCode
{
	PackedInstructionStream::PackedInstructionStream() :
		numInstructionBits(0),
		jumpTargetBitCount(0),
		localVariableBitCount(0),
		memberVariableBitCount(0),
		instructions(nullptr)
	{}

	PackedInstructionStream::PackedInstructionStream(PackedInstructionStream&& a_rhs) noexcept :
		numInstructionBits(std::exchange(a_rhs.numInstructionBits, 0)),
		jumpTargetBitCount(std::exchange(a_rhs.jumpTargetBitCount, 0)),
		localVariableBitCount(std::exchange(a_rhs.localVariableBitCount, 0)),
		memberVariableBitCount(std::exchange(a_rhs.memberVariableBitCount, 0)),
		instructions(std::exchange(a_rhs.instructions, nullptr))
	{}

	PackedInstructionStream& PackedInstructionStream::operator=(PackedInstructionStream&& a_rhs) noexcept
	{
		if (this != std::addressof(a_rhs)) {
			Release();
			numInstructionBits = std::exchange(a_rhs.numInstructionBits, 0);
			jumpTargetBitCount = std::exchange(a_rhs.jumpTargetBitCount, 0);
			localVariableBitCount = std::exchange(a_rhs.localVariableBitCount, 0);
			memberVariableBitCount = std::exchange(a_rhs.memberVariableBitCount, 0);
			instructions = std::exchange(a_rhs.instructions, nullptr);
		}
		return *this;
	}

	std::uint32_t PackedInstructionStream::GetInstructionNumberForOffset(std::uint32_t a_bitOffset) const
	{
		BSBitReader reader(instructions, 0);

		std::uint32_t instructionNumber = 0;
		while (true) {
			constexpr auto INVALID_INSTRUCTION_NUMBER = 0xFFFFFFFF;
			const auto     position = reader.getBitPosition(instructions);
			if (position >= a_bitOffset) {
				return position == a_bitOffset ? instructionNumber : INVALID_INSTRUCTION_NUMBER;
			}

			++instructionNumber;
			if (!VisitNextInstructionOperands(reader, &Argument::SkipFromBitStream)) {
				return INVALID_INSTRUCTION_NUMBER;
			}
		}
	}

	std::uint32_t PackedInstructionStream::GetBitOffsetForInstructionNumber(std::uint32_t a_instructionNumber) const
	{
		BSBitReader reader(instructions, 0);

		std::uint32_t skipped = 0;
		bool          decoded = true;
		while (reader.getBitPosition(instructions) < numInstructionBits && skipped < a_instructionNumber) {
			++skipped;
			decoded = VisitNextInstructionOperands(reader, &Argument::SkipFromBitStream);
			if (!decoded) {
				break;
			}
		}

		const auto position = reader.getBitPosition(instructions);
		return decoded && position < numInstructionBits ? position : numInstructionBits;  // the original re-seats the reader at the end, which is the same value
	}

	bool PackedInstructionStream::VisitNextInstructionOperands(BSBitReader& a_reader, VisitArgumentFn a_visitArgument) const
	{
		using OpCode = Internal::CodeTasklet::OpCode;

		const auto opcode = static_cast<OpCode>(a_reader.readRawBits(6));
		const auto localBits = static_cast<std::uint32_t>(static_cast<std::uint8_t>(localVariableBitCount));
		const auto memberBits = static_cast<std::uint32_t>(static_cast<std::uint8_t>(memberVariableBitCount));
		const auto visit = [&](std::uint64_t a_count) {
			for (std::uint64_t i = 0; i < a_count; ++i) {
				a_visitArgument(a_reader, localBits, memberBits);
			}
		};

		switch (opcode) {
		case OpCode::kNOP:
			break;
		case OpCode::kIADD:
		case OpCode::kFADD:
		case OpCode::kISUB:
		case OpCode::kFSUB:
		case OpCode::kIMUL:
		case OpCode::kFMUL:
		case OpCode::kIDIV:
		case OpCode::kFDIV:
		case OpCode::kIMOD:
		case OpCode::kCMP_EQ:
		case OpCode::kCMP_LT:
		case OpCode::kCMP_LTE:
		case OpCode::kCMP_GT:
		case OpCode::kCMP_GTE:
		case OpCode::kSTRCAT:
		case OpCode::kPROPGET:
		case OpCode::kPROPSET:
		case OpCode::kARRAY_GETELEMENT:
		case OpCode::kARRAY_SETELEMENT:
			visit(3);
			break;
		case OpCode::kNOT:
		case OpCode::kINEG:
		case OpCode::kFNEG:
		case OpCode::kASSIGN:
		case OpCode::kCAST:
		case OpCode::kARRAY_CREATE:
		case OpCode::kARRAY_LENGTH:
			visit(2);
			break;
		case OpCode::kRETURN:
			visit(1);
			break;
		case OpCode::kARRAY_FINDELEMENT:
		case OpCode::kARRAY_RFINDELEMENT:
			visit(4);
			break;
		case OpCode::kJMP:
			a_reader.readRawBits(jumpTargetBitCount);
			break;
		case OpCode::kJMPT:
		case OpCode::kJMPF:
			visit(1);
			a_reader.readRawBits(jumpTargetBitCount);
			break;
		case OpCode::kCALLMETHOD:
		case OpCode::kCALLSTATIC:
			visit(3 + a_reader.readRawBits(9));
			break;
		case OpCode::kCALLPARENT:
			visit(2 + a_reader.readRawBits(9));
			break;
		default:  // opcodes above kARRAY_RFINDELEMENT
			return false;
		}
		return true;
	}

	void PackedInstructionStream::ForEachInstruction(InstructionFunctor& a_functor) const
	{
		using OpCode = Internal::CodeTasklet::OpCode;

		BSBitReader reader(instructions, 0);

		std::uint32_t instructionStart = 0;
		while (instructionStart < numInstructionBits) {
			constexpr std::uint32_t kNoJumpTarget = 0xFFFFFFFF;
			const auto              opcode = static_cast<OpCode>(reader.readRawBits(6));
			std::uint32_t           argCount = 0;
			std::uint32_t           jumpTargetIndex = kNoJumpTarget;

			switch (opcode) {
			case OpCode::kNOP:
				break;
			case OpCode::kIADD:
			case OpCode::kFADD:
			case OpCode::kISUB:
			case OpCode::kFSUB:
			case OpCode::kIMUL:
			case OpCode::kFMUL:
			case OpCode::kIDIV:
			case OpCode::kFDIV:
			case OpCode::kIMOD:
			case OpCode::kCMP_EQ:
			case OpCode::kCMP_LT:
			case OpCode::kCMP_LTE:
			case OpCode::kCMP_GT:
			case OpCode::kCMP_GTE:
			case OpCode::kSTRCAT:
			case OpCode::kPROPGET:
			case OpCode::kPROPSET:
			case OpCode::kARRAY_GETELEMENT:
			case OpCode::kARRAY_SETELEMENT:
				argCount = 3;
				break;
			case OpCode::kNOT:
			case OpCode::kINEG:
			case OpCode::kFNEG:
			case OpCode::kASSIGN:
			case OpCode::kCAST:
			case OpCode::kARRAY_CREATE:
			case OpCode::kARRAY_LENGTH:
				argCount = 2;
				break;
			case OpCode::kRETURN:
				argCount = 1;
				break;
			case OpCode::kARRAY_FINDELEMENT:
			case OpCode::kARRAY_RFINDELEMENT:
				argCount = 4;
				break;
			case OpCode::kJMP:
				argCount = 1;
				jumpTargetIndex = 0;
				break;
			case OpCode::kJMPT:
			case OpCode::kJMPF:
				argCount = 2;
				jumpTargetIndex = 1;
				break;
			case OpCode::kCALLMETHOD:
			case OpCode::kCALLSTATIC:
				argCount = static_cast<std::uint32_t>(reader.readRawBits(9)) + 3;
				break;
			case OpCode::kCALLPARENT:
				argCount = static_cast<std::uint32_t>(reader.readRawBits(9)) + 2;
				break;
			default:
				return;
			}

			if (!a_functor.VisitInstruction(static_cast<std::uint32_t>(opcode), instructionStart, argCount)) {
				return;
			}

			Argument argument;
			bool     visit = true;
			for (std::uint32_t i = 0; i < argCount; ++i) {
				if (i == jumpTargetIndex) {
					argument.SetInt(static_cast<std::int32_t>(reader.readRawBits(jumpTargetBitCount)));  // absolute bit offset
				} else if (!argument.ReadFromBitStream(reader, localVariableBitCount, memberVariableBitCount)) {
					return;
				}

				if (visit) {
					visit = a_functor.VisitArgument(argument);
				}
			}

			instructionStart = reader.getBitPosition(instructions);
		}
	}

	void PackedInstructionStream::Release()
	{
		if (instructions) {
			BSBitReader reader(instructions, 0);
			while (reader.getBitPosition(instructions) < numInstructionBits) {
				if (!VisitNextInstructionOperands(reader, &ReleaseArgument)) {
					break;
				}
			}
			free(instructions);
		}

		numInstructionBits = 0;
		jumpTargetBitCount = 0;
		localVariableBitCount = 0;
		memberVariableBitCount = 0;
		instructions = nullptr;
	}
}

#pragma once

#include "RE/A/Argument.h"
#include "RE/B/BSTArray.h"
#include "RE/P/PackedInstructionStream.h"

namespace RE
{
	namespace BSScript
	{
		namespace Internal
		{
			struct VDescTable;
		}

		namespace ByteCode
		{
			struct InstructionDefinition
			{
			public:
				// members
				std::uint64_t unk00;         // 00
				const char*   opCodeName;    // 08 - ex: iadd
				const char*   opCodeArgs;    // 10 - ex: SII
				std::byte     majorVersion;  // 18 - Papyrus major version when opCode was made
				std::byte     minorVersion;  // 19 - Papyrus minor version when opCode was made
				std::uint16_t pad1A;         // 1A
				std::uint32_t pad1C;         // 1C
			};

			static_assert(sizeof(InstructionDefinition) == 0x20);
		}

		namespace UnlinkedTypes
		{
			struct InstructionNode
			{
				inline static constexpr std::uint32_t kArgumentsPerNode = 0x20;

				InstructionNode*    prev;      // 00 - never touched here (opcode?)
				InstructionNode*    next;      // 08
				std::uint32_t       argCount;  // 10
				std::uint32_t       pad14;     // 14
				ByteCode::Argument* args;      // 18
			};
			static_assert(sizeof(InstructionNode) == 0x20);

			class InstructionStream
			{
			public:
				class InstructionFunctor
				{
				public:
					inline static constexpr auto RTTI = RTTI_BSScript__UnlinkedTypes__InstructionStream__InstructionFunctor;
					inline static constexpr auto VTABLE = VTABLE_BSScript__UnlinkedTypes__InstructionStream__InstructionFunctor;
					virtual ~InstructionFunctor() = default;

					enum class ForEachResult
					{
						kStop = 0,
						kContinue = 1
					};

					// add
					virtual ForEachResult VisitArgument(ByteCode::Argument& a_arg) = 0;                    // 01
					virtual ForEachResult VisitInstruction(std::uint32_t opCode, std::uint32_t info) = 0;  // 02
				};

				struct InstructionRecord
				{
					// members
					std::uint32_t opcode;  // 00
					std::uint32_t info;    // 04
					std::uint32_t unk08;   // 08
				};

				static_assert(sizeof(InstructionRecord) == 0xC);

				explicit InstructionStream(const BSTArray<InstructionRecord>& a_records, const BSTArray<ByteCode::Argument>& a_arguments);

				InstructionStream(const InstructionStream&) = delete;
				InstructionStream& operator=(const InstructionStream&) = delete;

				InstructionStream(InstructionStream&& a_rhs) noexcept;
				InstructionStream& operator=(InstructionStream&& a_rhs) noexcept;

				~InstructionStream();

				void ForEachInstruction(InstructionFunctor& a_functor) const;

				void Pack(ByteCode::PackedInstructionStream& a_out) const;

				// Packs and consumes this stream
				void PackTo(ByteCode::PackedInstructionStream& a_out);

				void AddArgument(const ByteCode::Argument& a_argument);

				// members
				ScrapHeap*                                        threadScrapHeap;      // 00
				std::uint32_t                                     functionCodeSize;     // 08
				std::uint32_t                                     argumentCount;        // 0C
				std::uint32_t                                     localVarBitCount;     // 10
				std::uint32_t                                     memberVarBitCount;    // 14
				MemoryManager::AutoScrapBuffer<InstructionRecord> recordBuffer;         // 18
				InstructionRecord*                                records;              // 20
				InstructionRecord*                                recordWriteCursor;    // 28
				InstructionNode*                                  instructionListHead;  // 30
				InstructionNode*                                  tailNode;             // 38
				InstructionNode**                                 tailNextLink;         // 40
			};

			static_assert(sizeof(InstructionStream) == 0x48);

			class CountInstructionInfo final : public InstructionStream::InstructionFunctor
			{
			public:
				inline static constexpr auto RTTI = RTTI_BSScript__UnlinkedTypes____CountInstructionInfo;
				inline static constexpr auto VTABLE = VTABLE_BSScript__UnlinkedTypes____CountInstructionInfo;

				explicit CountInstructionInfo(const std::uint32_t a_localBits, const std::uint32_t a_memberBits) :
					localBits(a_localBits), memberBits(a_memberBits) {}

				ForEachResult VisitInstruction(std::uint32_t a_opcode, std::uint32_t a_info) override;
				ForEachResult VisitArgument(ByteCode::Argument& a_arg) override;

				// members
				std::uint32_t fixedBits{ 0 };
				std::uint32_t jumpCount{ 0 };
				std::uint32_t localBits;
				std::uint32_t memberBits;
				std::uint32_t opcode{ 0 };
				std::uint32_t argCount{ 0 };
				std::uint32_t argIndex{ 0 };
			};
		}
	}
}

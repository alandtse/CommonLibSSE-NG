#pragma once

#include "RE/A/Argument.h"
#include "RE/B/BSBitReader.h"

namespace RE
{
	namespace BSScript
	{
		namespace ByteCode
		{
			struct PackedInstructionStream
			{
				class InstructionFunctor
				{
				public:
					inline static constexpr auto RTTI = RTTI_BSScript__ByteCode__PackedInstructionStream__InstructionFunctor;
					inline static constexpr auto VTABLE = VTABLE_BSScript__ByteCode__PackedInstructionStream__InstructionFunctor;

					virtual ~InstructionFunctor() = default;  // 00

					// add
					virtual bool VisitArgument(Argument& a_argument) = 0;                                                            // 01
					virtual bool VisitInstruction(std::uint32_t a_opcode, std::uint32_t a_bitOffset, std::uint32_t a_argCount) = 0;  // 02
				};
				static_assert(sizeof(InstructionFunctor) == 0x8);

				PackedInstructionStream();

				~PackedInstructionStream() { Release(); }

				// the stream owns its buffer and one string reference per identifier/string operand, so it is move-only
				PackedInstructionStream(const PackedInstructionStream&) = delete;
				PackedInstructionStream& operator=(const PackedInstructionStream&) = delete;

				PackedInstructionStream(PackedInstructionStream&& a_rhs) noexcept;
				PackedInstructionStream& operator=(PackedInstructionStream&& a_rhs) noexcept;

				using VisitArgumentFn = void (*)(BSBitReader&, std::uint32_t, std::uint32_t);

				std::uint32_t GetInstructionNumberForOffset(std::uint32_t a_bitOffset) const;

				std::uint32_t GetBitOffsetForInstructionNumber(std::uint32_t a_instructionNumber) const;

				bool VisitNextInstructionOperands(BSBitReader& a_reader, VisitArgumentFn a_visitArgument) const;

				void ForEachInstruction(InstructionFunctor& a_functor) const;

				void Release();

				// members
				std::uint32_t numInstructionBits;      // 00
				std::uint16_t jumpTargetBitCount;      // 04
				std::int8_t   localVariableBitCount;   // 06
				std::int8_t   memberVariableBitCount;  // 07
				void*         instructions;            // 08
			};
			static_assert(sizeof(PackedInstructionStream) == 0x10);
			static_assert(std::is_nothrow_move_constructible_v<PackedInstructionStream> && !std::is_copy_constructible_v<PackedInstructionStream>);
		}
	}
}

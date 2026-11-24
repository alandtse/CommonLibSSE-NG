#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class BSPathingRequest;
	struct IMovementPlayIdleResult;
	struct BSPathingSolution;

	class BSPathingStreamRead
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathingStreamRead;
		inline static constexpr auto VTABLE = VTABLE_BSPathingStreamRead;

		// add
		virtual bool ReadString(BSFixedString* a_out) = 0;                                   // 00
		virtual bool ReadFloat(float* a_out) = 0;                                            // 01
		virtual bool ReadUInt64(std::uint64_t* a_out) = 0;                                   // 02
		virtual bool ReadInt64(std::int64_t* a_out) = 0;                                     // 03
		virtual bool ReadUInt32(std::uint32_t* a_out) = 0;                                   // 04
		virtual bool ReadInt32(std::int32_t* a_out) = 0;                                     // 05
		virtual bool ReadUInt16(std::uint16_t* a_out) = 0;                                   // 06
		virtual bool ReadInt16(std::int16_t* a_out) = 0;                                     // 07
		virtual bool ReadUInt8(std::uint8_t* a_out) = 0;                                     // 08
		virtual bool ReadInt8(std::int8_t* a_out) = 0;                                       // 09
		virtual bool ReadBool(bool* a_out) = 0;                                              // 0A
		virtual bool ReadFormIDWithResult(std::uint32_t* a_formID, bool* a_outSuccess) = 0;  // 0B
		virtual bool ReadFormID(std::uint32_t* a_formID) = 0;                                // 0C
		virtual bool ReadRequest(BSPathingRequest** a_out);                                  // 0D
		virtual bool ReadSolution(BSPathingSolution** a_out);                                // 0E
		virtual bool ReadPlayIdleResult(IMovementPlayIdleResult** a_out);                    // 0F
		virtual ~BSPathingStreamRead();                                                      // 10
		virtual std::uint32_t GetType() = 0;                                                 // 11 - crc32 of the class name
		virtual std::uint16_t GetFormVersion() = 0;                                          // 12
		virtual std::uint32_t GetDynamicDataVersionNumber() = 0;                             // 13
	};
	static_assert(sizeof(BSPathingStreamRead) == 0x8);
}

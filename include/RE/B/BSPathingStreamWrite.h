#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class BSPathingRequest;
	struct IMovementPlayIdleResult;
	struct BSPathingSolution;

	class BSPathingStreamWrite
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathingStreamWrite;
		inline static constexpr auto VTABLE = VTABLE_BSPathingStreamWrite;

		// add
		virtual bool WriteString(BSFixedString* a_string) = 0;              // 00
		virtual bool WriteFloat(float a_value) = 0;                         // 01
		virtual bool WriteUInt64(std::uint64_t a_value) = 0;                // 02
		virtual bool WriteInt64(std::int64_t a_value) = 0;                  // 03
		virtual bool WriteUInt32(std::uint32_t a_value) = 0;                // 04
		virtual bool WriteInt32(std::int32_t a_value) = 0;                  // 05
		virtual bool WriteUInt16(std::uint16_t a_value) = 0;                // 06
		virtual bool WriteInt16(std::int16_t a_value) = 0;                  // 07
		virtual bool WriteUInt8(std::uint8_t a_value) = 0;                  // 08
		virtual bool WriteInt8(std::int8_t a_value) = 0;                    // 09
		virtual bool WriteBool(bool a_value) = 0;                           // 0A
		virtual bool WriteFormID(std::uint32_t a_formID) = 0;               // 0B
		virtual bool WriteRequest(BSPathingRequest** a_ref);                // 0C
		virtual bool WriteSolution(BSPathingSolution** a_ref);              // 0D
		virtual bool WritePlayIdleResult(IMovementPlayIdleResult** a_ref);  // 0E
		virtual ~BSPathingStreamWrite();                                    // 0F
		virtual std::uint32_t GetType() = 0;                                // 10 - crc32 of the class name
	};
	static_assert(sizeof(BSPathingStreamWrite) == 0x8);
}

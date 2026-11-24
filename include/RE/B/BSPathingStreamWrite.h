#pragma once

namespace RE
{
	class BSPathingRequest;
	struct BSPathingSolution;

	class BSPathingStreamWrite
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathingStreamWrite;
		inline static constexpr auto VTABLE = VTABLE_BSPathingStreamWrite;

		// add
		virtual void Unk_00(void) = 0;                          // 00
		virtual bool WriteFloat(float a_value) = 0;             // 01
		virtual void Unk_02(void) = 0;                          // 02
		virtual void Unk_03(void) = 0;                          // 03
		virtual bool WriteUInt32(std::uint32_t a_value) = 0;    // 04
		virtual void Unk_05(void) = 0;                          // 05
		virtual bool WriteUInt16(std::uint16_t a_value) = 0;    // 06
		virtual void Unk_07(void) = 0;                          // 07
		virtual bool WriteUInt8(std::uint8_t a_value) = 0;      // 08
		virtual void Unk_09(void) = 0;                          // 09
		virtual bool WriteBool(bool a_value) = 0;               // 0A
		virtual bool WriteFormID(std::uint32_t a_formID) = 0;   // 0B
		virtual bool WriteRequest(BSPathingRequest** a_ref);    // 0C
		virtual bool WriteSolution(BSPathingSolution** a_ref);  // 0D
		virtual void Unk_0E(void);                              // 0E
		virtual void Unk_0F(void);                              // 0F
		virtual void Unk_10(void) = 0;                          // 10
	};
	static_assert(sizeof(BSPathingStreamWrite) == 0x8);
}

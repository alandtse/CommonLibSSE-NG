#pragma once

namespace RE
{
	class BSPathingRequest;
	struct BSPathingSolution;

	class BSPathingStreamRead
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathingStreamRead;
		inline static constexpr auto VTABLE = VTABLE_BSPathingStreamRead;

		// add
		virtual void Unk_00(void) = 0;                                                       // 00
		virtual bool ReadFloat(float* a_out) = 0;                                            // 01
		virtual void Unk_02(void) = 0;                                                       // 02
		virtual void Unk_03(void) = 0;                                                       // 03
		virtual bool ReadUInt32(std::uint32_t* a_out) = 0;                                   // 04
		virtual void Unk_05(void) = 0;                                                       // 05
		virtual bool ReadUInt16(std::uint16_t* a_out) = 0;                                   // 06
		virtual void Unk_07(void) = 0;                                                       // 07
		virtual bool ReadUInt8(std::uint8_t* a_out) = 0;                                     // 08
		virtual void Unk_09(void) = 0;                                                       // 09
		virtual bool ReadBool(bool* a_out) = 0;                                              // 0A
		virtual bool ReadFormIDWithResult(std::uint32_t* a_formID, bool* a_outSuccess) = 0;  // 0B
		virtual bool ReadFormID(std::uint32_t* a_formID);                                    // 0C
		virtual bool ReadRequest(BSPathingRequest** a_out);                                  // 0D
		virtual bool ReadSolution(BSPathingSolution** a_out);                                // 0E
		virtual void Unk_0F(void);                                                           // 0F
		virtual void Unk_10(void);                                                           // 10
		virtual void Unk_11(void);                                                           // 11
		virtual void Unk_12(void);                                                           // 12
		virtual void Unk_13(void);                                                           // 13
	};
	static_assert(sizeof(BSPathingStreamRead) == 0x8);
}

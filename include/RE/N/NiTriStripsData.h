#pragma once

#include "RE/N/NiTriBasedGeomData.h"

namespace RE
{
	// Verified against SkyrimSE.exe: the strip get/set accessors write numStrips (+0x70),
	// stripLengths (+0x78), and stripLists (+0x80) directly at these offsets.
	class NiTriStripsData : public NiTriBasedGeomData
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiTriStripsData;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiTriStripsData;
		inline static constexpr auto VTABLE = VTABLE_NiTriStripsData;

		std::uint16_t  numStrips;     // 70
		std::uint16_t* stripLengths;  // 78
		std::uint16_t* stripLists;    // 80
	};
	static_assert(sizeof(NiTriStripsData) == 0x88);
}

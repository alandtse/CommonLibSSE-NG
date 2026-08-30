#pragma once

#include "RE/N/NiTriBasedGeomData.h"

namespace RE
{
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

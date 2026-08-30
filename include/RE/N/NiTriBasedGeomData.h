#pragma once

#include "RE/N/NiGeometryData.h"

namespace RE
{
	class NiTriBasedGeomData : public NiGeometryData
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiTriBasedGeomData;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiTriBasedGeomData;
		inline static constexpr auto VTABLE = VTABLE_NiTriBasedGeomData;

		std::uint16_t numTriangles;     // 68
		std::uint16_t activeTriangles;  // 6A
	};
	static_assert(sizeof(NiTriBasedGeomData) == 0x70);
}

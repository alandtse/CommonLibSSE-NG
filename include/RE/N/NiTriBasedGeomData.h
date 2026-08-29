#pragma once

#include "RE/N/NiGeometryData.h"

namespace RE
{
	// Verified against SkyrimSE.exe: numTriangles/activeTriangles read/written directly
	// at +0x68/+0x6A by NiTriShapeData/NiTriStripsData's triangle-count accessors.
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

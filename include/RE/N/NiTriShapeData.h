#pragma once

#include "RE/N/NiTriBasedGeomData.h"

namespace RE
{
	// Verified against SkyrimSE.exe: the triangle get/set accessors read/write triList
	// (+0x78, swapped+freed on set) and triListLength (+0x70, = triangle count * 3).
	class NiTriShapeData : public NiTriBasedGeomData
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiTriShapeData;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiTriShapeData;
		inline static constexpr auto VTABLE = VTABLE_NiTriShapeData;

		std::uint32_t  triListLength;  // 70
		std::uint16_t* triList;        // 78
	};
	static_assert(sizeof(NiTriShapeData) == 0x80);
}

#pragma once

#include "RE/N/NiTriBasedGeomData.h"

namespace RE
{
	class NiTriShapeData : public NiTriBasedGeomData
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiTriShapeData;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiTriShapeData;
		inline static constexpr auto VTABLE = VTABLE_NiTriShapeData;

		std::uint32_t  triListLength;  // 70 - triangle count * 3, not the triangle count itself
		std::uint16_t* triList;        // 78
	};
	static_assert(sizeof(NiTriShapeData) == 0x80);
}

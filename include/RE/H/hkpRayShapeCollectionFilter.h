#pragma once

#include "RE/H/hkBaseTypes.h"
#include "RE/H/hkpShape.h"

namespace RE
{
	class hkpShapeContainer;

	struct hkpShapeRayCastInput;

	class hkpRayShapeCollectionFilter
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpRayShapeCollectionFilter;
		inline static constexpr auto VTABLE = VTABLE_hkpRayShapeCollectionFilter;

		// add
		virtual hkBool IsCollisionEnabled(const hkpShapeRayCastInput& a_input, const hkpShape& a_shape, const hkpShapeContainer& a_container, hkpShapeKey a_key) const = 0;  // 00

		virtual ~hkpRayShapeCollectionFilter();  // 01
	};
	static_assert(sizeof(hkpRayShapeCollectionFilter) == 0x08);
}

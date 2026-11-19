#pragma once

#include "RE/H/hkBaseTypes.h"

namespace RE
{
	class hkpCollidable;

	struct hkpWorldRayCastInput;

	class hkpRayCollidableFilter
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpRayCollidableFilter;
		inline static constexpr auto VTABLE = VTABLE_hkpRayCollidableFilter;

		virtual ~hkpRayCollidableFilter();  // 00

		// add
		virtual hkBool IsCollisionEnabled(const hkpWorldRayCastInput& a_input, const hkpCollidable& a_collidable) const = 0;  // 01
	};
	static_assert(sizeof(hkpRayCollidableFilter) == 0x08);
}

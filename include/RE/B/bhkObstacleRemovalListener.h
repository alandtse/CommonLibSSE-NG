#pragma once

#include "RE/H/hkpEntityListener.h"

namespace RE
{
	// Installed by NavMeshObstacleManager on the bodies of dynamic obstacles.
	class bhkObstacleRemovalListener : public hkpEntityListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkObstacleRemovalListener;
		inline static constexpr auto VTABLE = VTABLE_bhkObstacleRemovalListener;

		~bhkObstacleRemovalListener() override;  // 00
	};
	static_assert(sizeof(bhkObstacleRemovalListener) == 0x8);
}

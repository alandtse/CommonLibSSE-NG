#pragma once

namespace RE
{
	// Installed by NavMeshObstacleManager on the bodies of dynamic obstacles.
	class bhkObstacleRemovalListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkObstacleRemovalListener;
		inline static constexpr auto VTABLE = VTABLE_bhkObstacleRemovalListener;

		virtual ~bhkObstacleRemovalListener();  // 00

		// members
		// (none)
	};
	static_assert(sizeof(bhkObstacleRemovalListener) == 0x8);
}

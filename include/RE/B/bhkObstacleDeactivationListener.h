#pragma once

#include "RE/H/hkpEntityActivationListener.h"

namespace RE
{
	// Installed by NavMeshObstacleManager on the bodies of dynamic obstacles.
	class bhkObstacleDeactivationListener : public hkpEntityActivationListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkObstacleDeactivationListener;
		inline static constexpr auto VTABLE = VTABLE_bhkObstacleDeactivationListener;

		~bhkObstacleDeactivationListener() override;  // 00

		// override (hkpEntityActivationListener)
		void Unk_01(void) override;  // 01
		void Unk_02(void) override;  // 02
	};
	static_assert(sizeof(bhkObstacleDeactivationListener) == 0x8);
}

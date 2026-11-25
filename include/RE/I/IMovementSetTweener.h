#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	struct MovementPlayIdleData;

	class IMovementSetTweener : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementSetTweener;
		inline static constexpr auto VTABLE = VTABLE_IMovementSetTweener;

		~IMovementSetTweener() override;  // 00

		// add
		virtual bool SetPlayIdleData(const MovementPlayIdleData& a_data) = 0;  // 01 - copies the data into the arbiter and returns true
		virtual void ResetTweener() = 0;                                       // 02 - rebuilds the actor transform and resets every tweener agent
		virtual void UpdateTweener() = 0;                                      // 03 - applies the tweened transform when bUseTweenedAnimations:Pathfinding is set
	};
	static_assert(sizeof(IMovementSetTweener) == 0x8);
}

#pragma once

#include "RE/I/IMovementInterface.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class IMovementPlannerDirectControl : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementPlannerDirectControl;
		inline static constexpr auto VTABLE = VTABLE_IMovementPlannerDirectControl;

		~IMovementPlannerDirectControl() override;  // 00

		// add
		virtual void EnablePlannerDirectControl() = 0;                // 01
		virtual void SetPlannerDirection(NiPoint3* a_direction) = 0;  // 02
		virtual void SetPlannerSpeed(float a_speed) = 0;              // 03
		virtual void SetPlannerRotation(NiPoint3* a_rotation) = 0;    // 04
		virtual void DisablePlannerDirectControl() = 0;               // 05
	};
	static_assert(sizeof(IMovementPlannerDirectControl) == 0x8);
}

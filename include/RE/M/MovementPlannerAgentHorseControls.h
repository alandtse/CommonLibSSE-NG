#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	class IMovementControllerRegisterInterface;

	// secondary bases (not declared in CLib): IMovementPlannerAgent
	class MovementPlannerAgentHorseControls : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPlannerAgentHorseControls;
		inline static constexpr auto VTABLE = VTABLE_MovementPlannerAgentHorseControls;

		// members
		void*                                 vptr_IMovementPlannerAgent;  // 18
		IMovementControllerRegisterInterface* registerInterface;           // 20
	};
	static_assert(sizeof(MovementPlannerAgentHorseControls) == 0x28);
}

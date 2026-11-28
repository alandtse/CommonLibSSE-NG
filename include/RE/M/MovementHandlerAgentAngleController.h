#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	// secondary bases (not declared in CLib): IMovementHandlerAgent
	class MovementHandlerAgentAngleController : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgentAngleController;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerAgentAngleController;

		// members
		void* vptr_IMovementHandlerAgent;  // 18
	};
	static_assert(sizeof(MovementHandlerAgentAngleController) == 0x20);
}

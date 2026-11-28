#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	// secondary bases (not declared in CLib): IMovementHandlerAgent
	class MovementHandlerAgentStrafing : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgentStrafing;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerAgentStrafing;

		// members
		void* vptr_IMovementHandlerAgent;  // 18
	};
	static_assert(sizeof(MovementHandlerAgentStrafing) == 0x20);
}

#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	// secondary bases (not declared in CLib): IMovementHandlerAgent
	class MovementHandlerAgentDirectionPassThrough : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgentDirectionPassThrough;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerAgentDirectionPassThrough;

		// members
		void* vptr_IMovementHandlerAgent;  // 18
	};
	static_assert(sizeof(MovementHandlerAgentDirectionPassThrough) == 0x20);
}

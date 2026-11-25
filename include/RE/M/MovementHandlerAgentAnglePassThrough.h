#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	// secondary bases (not declared in CLib): IMovementHandlerAgent
	class MovementHandlerAgentAnglePassThrough : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgentAnglePassThrough;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerAgentAnglePassThrough;

		// members
		void* vptr_IMovementHandlerAgent;  // 18
	};
	static_assert(sizeof(MovementHandlerAgentAnglePassThrough) == 0x20);
}

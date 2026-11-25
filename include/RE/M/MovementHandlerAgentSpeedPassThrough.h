#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	// secondary bases (not declared in CLib): IMovementHandlerAgent
	class MovementHandlerAgentSpeedPassThrough : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgentSpeedPassThrough;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerAgentSpeedPassThrough;

		// members
		void* vptr_IMovementHandlerAgent;  // 18
	};
	static_assert(sizeof(MovementHandlerAgentSpeedPassThrough) == 0x20);
}

#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	// secondary bases (not declared in CLib): IMovementHandlerAgent
	class MovementHandlerAgentAngleGain : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgentAngleGain;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerAgentAngleGain;

		// members
		void* vptr_IMovementHandlerAgent;  // 18
	};
	static_assert(sizeof(MovementHandlerAgentAngleGain) == 0x20);
}

#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	// secondary bases (not declared in CLib): IMovementHandlerAgent, IMovementSetSprinting
	class MovementHandlerAgentSprintActionTrigger : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgentSprintActionTrigger;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerAgentSprintActionTrigger;

		// members
		void*         vptr_IMovementHandlerAgent;  // 18
		void*         vptr_IMovementSetSprinting;  // 20
		std::uint32_t ownerHandle;                 // 28 - Activate stores result of owner-handle slot call
		std::uint32_t characterHandle;             // 2C - ObjectRefHandle of the Character; Activate stores it, sub_1406FD8A0 resolves it
		void*         unk30;                       // 30 - zeroed by ctor
		std::uint32_t state;                       // 38 - read as IMovementSetSprinting-subobject int in UpdateHandler; serialized
		std::uint8_t  unk3C;                       // 3C - bool, serialized
		std::uint8_t  sprinting;                   // 3D - bool, serialized; written by sub_1406FD8A0(bool) which fires the sprint action
		std::uint8_t  unk3E[2];                    // 3E
	};
	static_assert(sizeof(MovementHandlerAgentSprintActionTrigger) == 0x40);
}

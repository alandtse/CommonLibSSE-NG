#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	// secondary bases (not declared in CLib): IMovementHandlerAgent
	class MovementHandlerAgentPlayerControlsActionTrigger : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgentPlayerControlsActionTrigger;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerAgentPlayerControlsActionTrigger;

		// members
		void*         vptr_IMovementHandlerAgent;  // 18
		std::uint32_t characterHandle;             // 20 - ObjectRefHandle; Activate stores the Character handle, Deactivate resets to the null handle
		std::uint8_t  unk24[4];                    // 24
	};
	static_assert(sizeof(MovementHandlerAgentPlayerControlsActionTrigger) == 0x28);
}

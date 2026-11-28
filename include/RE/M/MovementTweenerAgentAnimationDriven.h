#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	// secondary bases (not declared in CLib): IMovementTweenerAgent
	class MovementTweenerAgentAnimationDriven : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementTweenerAgentAnimationDriven;
		inline static constexpr auto VTABLE = VTABLE_MovementTweenerAgentAnimationDriven;

		// members
		void*         vptr_IMovementTweenerAgent;  // 18
		std::uint32_t state;                       // 20 - 0 inactive, 1 animation-driven motion enabled; SaveGame/LoadGame, Activate/Deactivate
		std::uint32_t ownerHandle;                 // 24 - Activate: result of slot +8 call on the agent owner
		void*         unk28;                       // 28 - released/zeroed in dtor
		std::uint32_t characterHandle;             // 30 - ObjectRefHandle of the Character whose animation-driven motion is toggled
		std::uint8_t  unk34[4];                    // 34
	};
	static_assert(sizeof(MovementTweenerAgentAnimationDriven) == 0x38);
}

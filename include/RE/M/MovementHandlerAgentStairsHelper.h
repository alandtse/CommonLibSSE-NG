#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	class Actor;

	// secondary bases (not declared in CLib): IMovementHandlerAgent
	class MovementHandlerAgentStairsHelper : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgentStairsHelper;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerAgentStairsHelper;

		// members
		void*        vptr_IMovementHandlerAgent;  // 18
		Actor*       owner;                       // 20 - Activate stores the resolved owner; UpdateHandler calls Actor::GetCharController on it
		std::uint8_t unk28[8];                    // 28
	};
	static_assert(sizeof(MovementHandlerAgentStairsHelper) == 0x30);
}

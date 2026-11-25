#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	class IMovementControllerRegisterInterface;

	// secondary bases (not declared in CLib): IMovementPlannerAgent, IMovementSetKeepOffsetFromActor
	class MovementPlannerAgentKeepOffset : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPlannerAgentKeepOffset;
		inline static constexpr auto VTABLE = VTABLE_MovementPlannerAgentKeepOffset;

		// members
		void*                                 vptr_IMovementPlannerAgent;            // 18
		void*                                 vptr_IMovementSetKeepOffsetFromActor;  // 20
		IMovementControllerRegisterInterface* registerInterface;                     // 28
		std::uint8_t                          unk30[48];                             // 30 - ctor BSReadWriteLock(this+0x30)
	};
	static_assert(sizeof(MovementPlannerAgentKeepOffset) == 0x60);
}

#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	// secondary bases (not declared in CLib): IMovementPlannerAgent, IMovementPathManagerAgent, IMovementQueryPathFollowing, IMovementSetPathFollowing
	class MovementAgentPathFollowerVirtual : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementAgentPathFollowerVirtual;
		inline static constexpr auto VTABLE = VTABLE_MovementAgentPathFollowerVirtual;

		// members
		void*        vptr_IMovementPlannerAgent;        // 18
		void*        vptr_IMovementPathManagerAgent;    // 20
		void*        vptr_IMovementQueryPathFollowing;  // 28
		void*        vptr_IMovementSetPathFollowing;    // 30
		std::uint8_t unk38[40];                         // 38 - ctor BSReadWriteLock(this+0x38)
	};
	static_assert(sizeof(MovementAgentPathFollowerVirtual) == 0x60);
}

#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/M/MovementControllerAI.h"

namespace RE
{
	class IMovementControllerRegisterInterface;

	// secondary bases (not declared in CLib): IMovementTweenerAgent, ITweenerNodeFollowerSetup
	class MovementTweenerAgentNodeFollower : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementTweenerAgentNodeFollower;
		inline static constexpr auto VTABLE = VTABLE_MovementTweenerAgentNodeFollower;

		// members
		void*                                 vptr_IMovementTweenerAgent;      // 18
		void*                                 vptr_ITweenerNodeFollowerSetup;  // 20
		IMovementControllerRegisterInterface* registerInterface;               // 28
		std::uint32_t                         ownerHandle;                     // 30 - Activate stores result of owner-handle slot call
		std::uint32_t                         characterHandle;                 // 34 - ObjectRefHandle, ctor init = null handle; Activate stores the Character handle
		void*                                 unk38;                           // 38 - refcounted pointer released in dtor
		BSReadWriteLock                       lock;                            // 40 - ctor BSReadWriteLock(this+0x40)
	};
	static_assert(sizeof(MovementTweenerAgentNodeFollower) == 0x48);
}

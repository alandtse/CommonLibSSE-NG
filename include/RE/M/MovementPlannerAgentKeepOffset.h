#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/M/MovementControllerAI.h"
#include "RE/N/NiPoint3.h"

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
		BSReadWriteLock                       lock;                                  // 30 - ctor BSReadWriteLock(this+0x30)
		std::uint32_t                         targetHandle;                          // 38 - ObjectRefHandle of the actor to follow; ctor init = null handle; serialized via LookupObjectByRefHandle
		NiPoint3                              localOffset;                           // 3C
		NiPoint3                              offset;                                // 48 - ctor zero-inits; serialized; UpdateSmallDelta adds it to the followed actor position
		float                                 maxDistance;                           // 54
		float                                 minDistance;                           // 58 - minDistance: see maxDistance; serialized
		std::uint8_t                          unk5C[4];                              // 5C
	};
	static_assert(sizeof(MovementPlannerAgentKeepOffset) == 0x60);
}

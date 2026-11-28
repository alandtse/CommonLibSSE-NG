#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/M/MovementControllerAI.h"

namespace RE
{
	class BSPathingRequest;
	struct BSPathingSolution;

	// secondary bases (not declared in CLib): IMovementPlannerAgent, IMovementPathManagerAgent, IMovementQueryPathFollowing, IMovementQueryFlight
	class MovementAgentPathFollowerFlight : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementAgentPathFollowerFlight;
		inline static constexpr auto VTABLE = VTABLE_MovementAgentPathFollowerFlight;

		// members
		void*              vptr_IMovementPlannerAgent;        // 18
		void*              vptr_IMovementPathManagerAgent;    // 20
		void*              vptr_IMovementQueryPathFollowing;  // 28
		void*              vptr_IMovementQueryFlight;         // 30
		std::uint32_t      state;                             // 38 - 0..2, SaveGame/LoadGame; UpdateSmallDelta tests < 3
		float              curveProgress;                     // 3C - accumulates speed*dt; compared against BSBezierCurve::QApproximateLength; serialized
		BSPathingRequest*  request;                           // 40 - SaveGame stream slot 0x60 / LoadGame slot 0x68
		BSPathingSolution* solution;                          // 48 - LoadGame stream slot 0x70; node count at solution+0xA0
		float              unk50;                             // 50 - serialized
		float              distanceTravelled;                 // 54 - serialized
		std::uint32_t      nodeIndex;                         // 58 - compared with solution node count, incremented; serialized
		std::uint32_t      prevNodeIndex;                     // 5C - copy of nodeIndex; serialized
		std::uint8_t       bezierCurve[48];                   // 60 - BSBezierCurve
		std::uint32_t      ownerHandle;                       // 90 - Activate stores result of owner-handle slot call
		std::uint8_t       unk94[4];                          // 94
		void*              messageInterface;                  // 98 - dtor calls vtable slot 4 on it then nulls it
		BSReadWriteLock    lock;                              // A0 - ctor BSReadWriteLock(this+0xA0)
	};
	static_assert(sizeof(MovementAgentPathFollowerFlight) == 0xA8);
}

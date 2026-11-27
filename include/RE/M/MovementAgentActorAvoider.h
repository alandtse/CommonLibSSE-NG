#pragma once

#include "RE/A/AvoidedActorInfo.h"
#include "RE/B/BSTArray.h"
#include "RE/M/MovementControllerAI.h"

namespace RE
{
	class BSPathingRequest;
	class ActorState;

	// the secondary vtables at 18-2F belong to IMovementPlannerAgent, IMovementPathManagerAgent
	// and IMovementQueryActorAvoidance
	class MovementAgentActorAvoider : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementAgentActorAvoider;
		inline static constexpr auto VTABLE = VTABLE_MovementAgentActorAvoider;

		void FindActorsToAvoid(float a_delta)
		{
			using func_t = void(MovementAgentActorAvoider*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89723, 92200) };
			func(this, a_delta);
		}
		bool IsActorNearPath(void* a_actorInfo)
		{
			using func_t = bool(MovementAgentActorAvoider*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89724, 92201) };
			return func(this, a_actorInfo);
		}

		// members
		void*                      secondaryVtables[3];  // 18
		std::uint32_t              ownerHandle;          // 30
		std::uint32_t              pad34;                // 34
		void*                      movementController;   // 38
		BSPathingRequest*          request;              // 40
		BSTArray<AvoidedActorInfo> avoidedActors;        // 48
		std::int32_t               unk60;                // 60
		std::uint32_t              unk64;                // 64
		std::uint32_t              avoidanceState;       // 68
		std::uint32_t              unk6C;                // 6C
	};
	static_assert(sizeof(MovementAgentActorAvoider) == 0x70);
}

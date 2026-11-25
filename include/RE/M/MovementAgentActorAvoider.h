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

		void CheckBlockedByActors(void* a_arg1, std::uint32_t* a_outStatus)
		{
			using func_t = void(MovementAgentActorAvoider*, void*, std::uint32_t*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89715, 92192) };
			func(this, a_arg1, a_outStatus);
		}
		void AddActorAvoidNodes(BSPathingRequest** a_request)
		{
			using func_t = void(MovementAgentActorAvoider*, BSPathingRequest**);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89716, 92193) };
			func(this, a_request);
		}
		void FindActorsToAvoid()
		{
			using func_t = void(MovementAgentActorAvoider*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89723, 92200) };
			func(this);
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

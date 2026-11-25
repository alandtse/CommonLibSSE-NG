#pragma once

#include "RE/I/IMovementAgentDataTracker.h"
#include "RE/I/IMovementQueryTweener.h"
#include "RE/I/IMovementSetTweener.h"
#include "RE/M/MovementControllerAI.h"
#include "RE/M/MovementPlayIdleData.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiTransform.h"

namespace RE
{
	class IMovementControllerRegisterInterface;
	class IMovementTweenerAgent;
	struct MovementTweenerAgentOutputData;

	// blends the animation-driven tweener transform into the pathing output
	class MovementTweenerArbiter :
		public MovementArbiter,       // 000
		public IMovementSetTweener,   // 018
		public IMovementQueryTweener  // 020
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementTweenerArbiter;
		inline static constexpr auto VTABLE = VTABLE_MovementTweenerArbiter;

		~MovementTweenerArbiter() override;  // 00

		// members
		NiTransform                                                                       tweenerTransform;       // 028
		NiTransform                                                                       motionTransform;        // 05C - rotation is multiplied in and velocity integrated into its position by UpdateSmallDelta; the name is a guess
		NiTransform                                                                       actorTransform;         // 090 - filled from the actor state and sent to the agents
		NiPoint3                                                                          tweenerVelocity;        // 0C4
		float                                                                             tweenerYawRate;         // 0D0
		MovementPlayIdleData                                                              playIdleData;           // 0D4
		std::uint32_t                                                                     ownerHandle;            // 15C
		void*                                                                             tweenerAgentsData;      // 160
		std::uint32_t                                                                     tweenerAgentsCapacity;  // 168
		std::uint32_t                                                                     pad16C;                 // 16C
		std::uint32_t                                                                     tweenerAgentsSize;      // 170
		std::uint32_t                                                                     pad174;                 // 174
		IMovementControllerRegisterInterface*                                             registerInterface;      // 178
		IMovementAgentDataTracker<IMovementTweenerAgent, MovementTweenerAgentOutputData>* agentDataTracker;       // 180
	};
	static_assert(sizeof(MovementTweenerArbiter) == 0x188);
}

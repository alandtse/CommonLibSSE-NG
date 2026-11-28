#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IMovementAgentDataTracker.h"
#include "RE/I/IMovementPlannerSetArbitration.h"
#include "RE/M/MovementControllerAI.h"

namespace RE
{
	class IMovementControllerRegisterInterface;
	class IMovementPlannerAgent;
	struct MovementArbitrationMaxWeightParameters;
	struct MovementArbitrationMaxWeightPoint;
	struct MovementArbitrationVectorAdd;
	struct MovementPlannerAgentReturnDataSmallDelta;

	// arbitrates the planner agents' direction output
	class MovementPlannerArbiter :
		public MovementArbiter,                // 00
		public IMovementPlannerSetArbitration  // 18
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPlannerArbiter;
		inline static constexpr auto VTABLE = VTABLE_MovementPlannerArbiter;

		~MovementPlannerArbiter() override;  // 00

		// members
		float                                                                                       blockedTime;            // 20 - accumulates while LimitSpeedForPredictedCollisions forces speed to 0
		bool                                                                                        initialized;            // 24
		std::uint8_t                                                                                pad25;                  // 25
		std::uint16_t                                                                               pad26;                  // 26
		std::uint32_t                                                                               ownerHandle;            // 28
		std::uint32_t                                                                               pad2C;                  // 2C
		void*                                                                                       agentsData;             // 30
		std::uint32_t                                                                               agentsCapacity;         // 38
		std::uint32_t                                                                               pad3C;                  // 3C
		std::uint32_t                                                                               agentsSize;             // 40
		std::uint32_t                                                                               pad44;                  // 44
		MovementArbitrationVectorAdd*                                                               vectorArbitration;      // 48
		MovementArbitrationMaxWeightPoint*                                                          pointArbitration;       // 50
		MovementArbitrationMaxWeightParameters*                                                     parametersArbitration;  // 58
		IMovementControllerRegisterInterface*                                                       registerInterface;      // 60
		IMovementAgentDataTracker<IMovementPlannerAgent, MovementPlannerAgentReturnDataSmallDelta>* agentDataTracker;       // 68
	};
	static_assert(sizeof(MovementPlannerArbiter) == 0x70);
}

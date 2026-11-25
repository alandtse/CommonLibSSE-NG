#pragma once

#include "RE/I/IMovementAgentDataTracker.h"
#include "RE/M/MovementControllerAI.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class IMovementControllerRegisterInterface;
	class IMovementHandlerAgent;
	struct MovementHandlerOutputDataSmallDelta;
	struct MovementHandlerUpdateDataSmallDelta;

	// runs the handler agents each small delta and carries their combined speed and rotation output
	class MovementHandlerArbiter : public MovementArbiter  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerArbiter;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerArbiter;

		~MovementHandlerArbiter() override;  // 00

		// members
		float                                                                                  lastSpeed;              // 18
		float                                                                                  lastHeading;            // 1C
		float                                                                                  lastRotationZ;          // 20
		float                                                                                  lastDeltaTime;          // 24
		float                                                                                  outputSpeed;            // 28
		NiPoint3                                                                               outputAngularVelocity;  // 2C - copied from MovementHandlerOutputDataSmallDelta::angularVelocity
		NiPoint3                                                                               outputRotation;         // 38
		std::uint32_t                                                                          ownerHandle;            // 44
		void*                                                                                  handlerAgentsData;      // 48
		std::uint32_t                                                                          handlerAgentsCapacity;  // 50
		std::uint32_t                                                                          pad54;                  // 54
		std::uint32_t                                                                          handlerAgentsSize;      // 58
		std::uint32_t                                                                          pad5C;                  // 5C
		IMovementControllerRegisterInterface*                                                  registerInterface;      // 60
		void*                                                                                  unk68;                  // 68
		IMovementAgentDataTracker<IMovementHandlerAgent, MovementHandlerUpdateDataSmallDelta>* updateDataTracker;      // 70
		IMovementAgentDataTracker<IMovementHandlerAgent, MovementHandlerOutputDataSmallDelta>* outputDataTracker;      // 78
	};
	static_assert(sizeof(MovementHandlerArbiter) == 0x80);
}

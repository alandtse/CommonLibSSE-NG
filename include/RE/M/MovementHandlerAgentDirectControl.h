#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/M/MovementControllerAI.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	// secondary bases (not declared in CLib): IMovementHandlerAgent
	class MovementHandlerAgentDirectControl : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgentDirectControl;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerAgentDirectControl;

		// members
		void*           vptr_IMovementHandlerAgent;  // 18
		NiPoint3        direction;                   // 20 - Init fills from ActorState; ClearForcedMovement zeroes
		float           speed;                       // 2C - Init = ActorState::SpeedToNormalized(...)
		NiPoint3        rotation;                    // 30 - Init sets Z (0x38) = ActorState::RotationSpeedToNormalized(...)
		float           directionBlendTime;          // 3C - zeroed by ctor and ClearForcedMovement
		float           speedBlendTime;              // 40 - UpdateHandler subtracts frame delta; cleared by ClearForcedMovement
		float           rotationBlendTime;           // 44 - zeroed by ctor and ClearForcedMovement
		void*           movementParameters;          // 48 - released/zeroed in dtor
		BSReadWriteLock lock;                        // 50 - ctor BSReadWriteLock(this+0x50); UpdateHandler locks it
		NiPoint3        targetDirection;             // 58 - blended toward by UpdateHandler (FUN_1406faf20 lerp)
		float           targetSpeed;                 // 64 - zeroed by ctor and ClearForcedMovement
		NiPoint3        targetRotation;              // 68 - blended toward by UpdateHandler
		std::uint8_t    unk74[4];                    // 74
	};
	static_assert(sizeof(MovementHandlerAgentDirectControl) == 0x78);
}

#pragma once

#include "RE/M/MovementControllerAI.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	// secondary bases (not declared in CLib): IMovementTweenerAgent, IMovementSetCorrectionData
	class MovementTweenerAgentFixedDelta : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementTweenerAgentFixedDelta;
		inline static constexpr auto VTABLE = VTABLE_MovementTweenerAgentFixedDelta;

		// members
		void*         vptr_IMovementTweenerAgent;       // 18
		void*         vptr_IMovementSetCorrectionData;  // 20
		float         elapsedTime;                      // 28 - zeroed by ctor
		float         correctionMatrix[9];              // 2C
		std::uint32_t ownerHandle;                      // 50 - Activate stores result of owner-handle slot call
		NiPoint3      translationCorrection;            // 54 - ctor zero-inits; serialized as floats
		NiPoint3      translationStartVelocity;         // 60 - ctor zero-inits; serialized
		NiPoint3      translationEndVelocity;           // 6C - ctor zero-inits; serialized
		NiPoint3      rotationCorrection;               // 78 - ctor zero-inits; serialized
		NiPoint3      rotationStartVelocity;            // 84 - ctor zero-inits; serialized
		NiPoint3      rotationEndVelocity;              // 90 - ctor zero-inits; serialized
		float         correctionTimes[3];               // 9C - zeroed by ctor
		void*         unkA8;                            // A8 - released/zeroed in dtor
	};
	static_assert(sizeof(MovementTweenerAgentFixedDelta) == 0xB0);
}

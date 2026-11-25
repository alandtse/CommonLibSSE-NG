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
		std::uint32_t unk28;                            // 28 - zeroed by ctor
		float         correctionMatrix[9];              // 2C
		std::uint32_t ownerHandle;                      // 50 - Activate stores result of owner-handle slot call
		NiPoint3      unk54;                            // 54 - ctor zero-inits; serialized as floats
		NiPoint3      unk60;                            // 60 - ctor zero-inits; serialized
		NiPoint3      unk6C;                            // 6C - ctor zero-inits; serialized
		NiPoint3      unk78;                            // 78 - ctor zero-inits; serialized
		NiPoint3      unk84;                            // 84 - ctor zero-inits; serialized
		NiPoint3      unk90;                            // 90 - ctor zero-inits; serialized
		std::uint8_t  unk9C[12];                        // 9C - zeroed by ctor
		void*         unkA8;                            // A8 - released/zeroed in dtor
	};
	static_assert(sizeof(MovementTweenerAgentFixedDelta) == 0xB0);
}

#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/M/MovementControllerAI.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class IMovementControllerRegisterInterface;

	// secondary bases (not declared in CLib): IMovementPlannerAgent
	class MovementPlannerAgentDirectControl : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPlannerAgentDirectControl;
		inline static constexpr auto VTABLE = VTABLE_MovementPlannerAgentDirectControl;

		// members
		void*                                 vptr_IMovementPlannerAgent;  // 18
		IMovementControllerRegisterInterface* registerInterface;           // 20
		BSReadWriteLock                       lock;                        // 28 - guards direction/rotation; ctor BSReadWriteLock(this+0x28), UpdateSmallDelta read-locks it
		NiPoint3                              direction;                   // 30 - ctor zero-inits; UpdateSmallDelta copies to returnData.direction
		std::uint32_t                         unk3C;                       // 3C - ctor zero-inits
		NiPoint3                              rotation;                    // 40 - ctor zero-inits; UpdateSmallDelta copies to returnData.rotation
		std::uint8_t                          unk4C[4];                    // 4C
	};
	static_assert(sizeof(MovementPlannerAgentDirectControl) == 0x50);
}

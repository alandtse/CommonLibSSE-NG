#pragma once

#include "RE/M/MovementHandlerOutputDataSmallDelta.h"
#include "RE/M/MovementHandlerUpdateDataSmallDelta.h"
#include "RE/M/MovementPlannerUpdateDataSmallDelta.h"

namespace RE
{
	// built on the stack by MovementControllerAI each frame and passed to every arbiter
	struct MovementUpdateDataSmallDelta
	{
	public:
		// members
		float                               deltaTime;          // 00
		float                               unk4;               // 04
		MovementPlannerUpdateDataSmallDelta plannerUpdateData;  // 08
		MovementHandlerUpdateDataSmallDelta handlerUpdateData;  // 10
		MovementHandlerOutputDataSmallDelta handlerOutputData;  // 98
	};
	static_assert(sizeof(MovementUpdateDataSmallDelta) == 0xD8);
}

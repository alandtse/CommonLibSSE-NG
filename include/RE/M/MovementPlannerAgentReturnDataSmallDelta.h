#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class IMovementParameters;
	struct MovementHandlerUpdateDataSmallDelta;

	// filled in by each planner agent's UpdateSmallDelta
	struct MovementPlannerAgentReturnDataSmallDelta
	{
	public:
		// members
		float                                directionWeight;     // 00
		NiPoint3                             direction;           // 04
		float                                speed;               // 10
		float                                rotationWeight;      // 14
		NiPoint3                             rotation;            // 18
		float                                unk24;               // 24
		float                                unk28;               // 28 - the actor state planner writes 0.1
		std::uint32_t                        unk2C;               // 2C
		IMovementParameters*                 movementParameters;  // 30 - NiPointer
		MovementHandlerUpdateDataSmallDelta* handlerUpdateData;   // 38
		void*                                avoidShapes;         // 40 - points into handlerUpdateData
		std::uint64_t                        unk48;               // 48
		std::uint64_t                        unk50;               // 50
	};
	static_assert(sizeof(MovementPlannerAgentReturnDataSmallDelta) == 0x58);
}

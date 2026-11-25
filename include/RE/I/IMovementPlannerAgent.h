#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	struct MovementPlannerAgentReturnDataSmallDelta;
	struct MovementPlannerUpdateDataSmallDelta;

	class IMovementPlannerAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementPlannerAgent;
		inline static constexpr auto VTABLE = VTABLE_IMovementPlannerAgent;

		virtual ~IMovementPlannerAgent();  // 00

		// add
		virtual const BSFixedString& GetAgentType() const;                                                                                                         // 01
		virtual void                 UpdateSmallDelta(MovementPlannerUpdateDataSmallDelta* a_updateData, MovementPlannerAgentReturnDataSmallDelta* a_returnData);  // 02
		virtual void                 UpdateLargeDelta(void* a_updateData, void* a_returnData);                                                                     // 03
	};
	static_assert(sizeof(IMovementPlannerAgent) == 0x8);
}

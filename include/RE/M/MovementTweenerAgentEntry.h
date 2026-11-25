#pragma once

#include "RE/N/NiTransform.h"

namespace RE
{
	class IMovementTweenerAgent;

	// Element of MovementTweenerArbiter::tweenerAgentsData.
	struct MovementTweenerAgentEntry
	{
	public:
		// members
		NiTransform            adjustedTransform;  // 00
		std::uint8_t           pad34[4];           // 34
		IMovementTweenerAgent* agent;              // 38
	};
	static_assert(sizeof(MovementTweenerAgentEntry) == 0x40);
}

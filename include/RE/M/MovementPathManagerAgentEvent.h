#pragma once

#include "RE/B/BSPathingLocation.h"

namespace RE
{
	// Output of IMovementPathManagerAgent::PollPathEvent, one per agent.
	struct MovementPathManagerAgentEvent
	{
	public:
		// members
		std::uint32_t     eventType;  // 00 - arbiter takes the maximum over all agents
		std::uint8_t      pad04[4];   // 04
		BSPathingLocation location;   // 08
		float             radius;     // 38
		std::uint8_t      pad3C[4];   // 3C
	};
	static_assert(sizeof(MovementPathManagerAgentEvent) == 0x40);
}

#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	// arbiter and agent names a MovementControllerNPC is reconciled against
	struct MovementAgentConfig
	{
	public:
		// members
		std::uint32_t capacityArbiters;  // 000
		std::uint32_t pad004;            // 004
		BSFixedString arbiterNames[32];  // 008
		std::uint32_t arbiterCount;      // 108
		std::uint32_t pad10C;            // 10C
		std::uint32_t capacityAgents;    // 110
		std::uint32_t pad114;            // 114
		BSFixedString agentNames[128];   // 118
		std::uint32_t agentCount;        // 518
		std::uint32_t pad51C;            // 51C
	};
	static_assert(sizeof(MovementAgentConfig) == 0x520);
}

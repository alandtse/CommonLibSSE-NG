#pragma once

#include "RE/N/NavmeshCostFilterRule.h"

namespace RE
{
	// Rule list with 4 inline NavmeshCostFilterRule entries (or a heap pointer when over capacity).
	struct NavmeshCostFilterSet
	{
	public:
		// members
		std::uint32_t capacityAndLocalFlag;  // 00
		std::uint32_t pad04;                 // 04
		std::uint8_t  storage[0x40];         // 08
		std::uint32_t ruleCount;             // 48
		std::uint32_t pad4C;                 // 4C
		std::uint32_t requiredMask;          // 50
		std::uint32_t forbiddenMask;         // 54
	};
	static_assert(sizeof(NavmeshCostFilterSet) == 0x58);
}

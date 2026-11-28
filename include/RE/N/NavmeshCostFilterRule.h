#pragma once

namespace RE
{
	// Per triangle-flag cost multiplier rule used by NavmeshCostFilterSet::ApplyCostRules.
	struct NavmeshCostFilterRule
	{
	public:
		// members
		std::uint32_t mask;              // 00 - triangle flag mask
		float         mulDestHasFlag;    // 04 - destination triangle has the flag
		float         mulDestLacksFlag;  // 08 - destination triangle lacks the flag
		float         mulTransition;     // 0C - from/to flags differ on the mask
	};
	static_assert(sizeof(NavmeshCostFilterRule) == 0x10);
}

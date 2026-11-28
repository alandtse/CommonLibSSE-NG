#pragma once

#include "RE/A/AStarNode.h"

namespace RE
{
	// Bucketed priority list: bucket index is (g + h) / maxCost * 20, overflow in the last bucket.
	struct AStarOpenList
	{
	public:
		// members
		float         maxCost;     // 00
		std::uint32_t pad04;       // 04
		AStarNode*    bucket[20];  // 08
	};
	static_assert(sizeof(AStarOpenList) == 0xA8);
}

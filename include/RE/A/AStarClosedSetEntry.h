#pragma once

#include "RE/A/AStarNode.h"

namespace RE
{
	// Scatter table entry of the A* closed set (CRC32 hashed on key).
	struct AStarClosedSetEntry
	{
	public:
		// members
		std::uint64_t        key;   // 00
		AStarNode*           node;  // 08
		AStarClosedSetEntry* next;  // 10 - chain; null means empty slot
	};
	static_assert(sizeof(AStarClosedSetEntry) == 0x18);
}

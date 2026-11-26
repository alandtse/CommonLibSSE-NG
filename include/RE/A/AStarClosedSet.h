#pragma once

#include "RE/A/AStarClosedSetEntry.h"

namespace RE
{
	// Scatter table keyed by AStarNode::key (CRC32 hashed); capacity is a power of two, minimum 8.
	struct AStarClosedSet
	{
	public:
		// members
		std::uint32_t        pad00;       // 00
		std::int32_t         capacity;    // 04
		std::int32_t         freeCount;   // 08
		std::uint32_t        freeCursor;  // 0C
		AStarClosedSetEntry* sentinel;    // 10
		std::uint8_t         pad18[8];    // 18
		AStarClosedSetEntry* entries;     // 20
	};
	static_assert(sizeof(AStarClosedSet) == 0x28);
}

#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSNavmesh;

	// Node type for AStarSearch<BSFastNavmeshTriLocation, BSFastNavmeshEdgeHandle, 3>;
	// the other AStarSearch instantiations use different node layouts.
	struct AStarNode
	{
	public:
		// members
		float         gCost;         // 00 - cost from start
		float         hCost;         // 04 - heuristic to goal; open list priority is gCost + hCost
		BSNavmesh*    navMesh;       // 08
		std::uint16_t triIndex;      // 10
		std::uint16_t pad12;         // 12
		std::uint32_t pad14;         // 14
		NiPoint3      center;        // 18 - triangle centroid / entry point
		std::uint32_t pad24;         // 24
		BSNavmesh*    edgeNavMesh;   // 28 - BSFastNavmeshEdgeHandle navmesh
		std::uint16_t edgeTriIndex;  // 30
		std::uint16_t pad32;         // 32
		std::uint32_t pad34;         // 34
		std::int32_t  edgeIndex;     // 38
		std::uint32_t pad3C;         // 3C
		std::uint64_t key;           // 40 - closed set key: triIndex | navmeshId << 16
		AStarNode*    parent;        // 48
		AStarNode**   openPrevSlot;  // 50 - intrusive open list link slot
		AStarNode*    openNext;      // 58
	};
	static_assert(sizeof(AStarNode) == 0x60);
}

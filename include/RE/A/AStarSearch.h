#pragma once

#include "RE/A/AStarClosedSet.h"
#include "RE/A/AStarNode.h"
#include "RE/A/AStarNodePool.h"
#include "RE/A/AStarOpenList.h"

namespace RE
{
	// AStarSearch<BSFastNavmeshTriLocation, BSFastNavmeshEdgeHandle, 3>
	class AStarSearch
	{
	public:
		virtual ~AStarSearch();                                       // 00
		virtual bool ExpandNode(AStarNode* a_node, void* a_out) = 0;  // 01 - a_out is a BSTSmallArray<AStarNode*, 3>
		virtual bool IsGoalNode(AStarNode* a_node) = 0;               // 02

		// members
		AStarNodePool  nodePool;         // 08
		AStarClosedSet closedSet;        // 48
		AStarOpenList  openList;         // 70
		void*          unk118;           // 118
		void*          unk120;           // 120
		AStarNode*     firstNode;        // 128
		std::uint32_t  unk130;           // 130 - 0x80000000 after construction
		std::uint8_t   unk134[0x1C];     // 134
		std::uint32_t  unk150;           // 150
		std::uint32_t  pad154;           // 154
		bool           onTaskletThread;  // 158
		std::uint8_t   pad159[7];        // 159
	};
	static_assert(sizeof(AStarSearch) == 0x160);
}

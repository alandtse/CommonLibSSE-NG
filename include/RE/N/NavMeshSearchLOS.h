#pragma once

#include "RE/A/AStarSearch.h"

namespace RE
{
	class NavMeshSearchLOS : public AStarSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_NavMeshSearchLOS;
		inline static constexpr auto VTABLE = VTABLE_NavMeshSearchLOS;

		~NavMeshSearchLOS() override;                              // 00
		bool ExpandNode(AStarNode* a_node, void* a_out) override;  // 01
		bool IsGoalNode(AStarNode* a_node) override;               // 02

		// members
		void*         request;        // 160
		std::uint8_t  pad168[0x20];   // 168
		void*         rayCache;       // 188
		bool          flag;           // 190
		std::uint8_t  pad191[0x27];   // 191
		std::uint8_t  sentinelFD;     // 1B8
		std::uint8_t  pad1B9[7];      // 1B9
		AStarNode*    fallbackNodeA;  // 1C0
		AStarNode*    fallbackNodeB;  // 1C8
		AStarNode*    fallbackNodeC;  // 1D0
		float         bestDistance;   // 1D8
		std::uint32_t pad1DC;         // 1DC
	};
	static_assert(sizeof(NavMeshSearchLOS) == 0x1E0);
}

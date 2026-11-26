#pragma once

#include "RE/A/AStarSearch.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class NavMeshSearchFlee : public AStarSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_NavMeshSearchFlee;
		inline static constexpr auto VTABLE = VTABLE_NavMeshSearchFlee;

		~NavMeshSearchFlee() override;                             // 00
		bool ExpandNode(AStarNode* a_node, void* a_out) override;  // 01
		bool IsGoalNode(AStarNode* a_node) override;               // 02

		// members
		void*        request;              // 160
		std::uint8_t startLocation[0x20];  // 168
		NiPoint3     fleeFrom;             // 188
		float        maxHeuristic;         // 194
		bool         flag;                 // 198
		std::uint8_t pad199[3];            // 199
		NiPoint3     goalPoint;            // 19C
	};
	static_assert(sizeof(NavMeshSearchFlee) == 0x1A8);
}

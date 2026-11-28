#pragma once

#include "RE/B/BSNavmeshSearch.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class NavMeshSearchMaxCost : public BSNavmeshSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_NavMeshSearchMaxCost;
		inline static constexpr auto VTABLE = VTABLE_NavMeshSearchMaxCost;

		~NavMeshSearchMaxCost() override;             // 00
		bool IsGoalNode(AStarNode* a_node) override;  // 02

		// members
		void*        request;             // 1B0
		void*        secondaryNavmeshes;  // 1B8
		void*        loadedNavmeshes;     // 1C0
		float        maxCost;             // 1C8
		bool         enabled;             // 1CC
		std::uint8_t pad1CD[3];           // 1CD
	};
	static_assert(sizeof(NavMeshSearchMaxCost) == 0x1D0);
}

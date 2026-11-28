#pragma once

#include "RE/B/BSNavmeshSearch.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class NavMeshSearchHide : public BSNavmeshSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_NavMeshSearchHide;
		inline static constexpr auto VTABLE = VTABLE_NavMeshSearchHide;

		~NavMeshSearchHide() override;                // 00
		bool IsGoalNode(AStarNode* a_node) override;  // 02

		// members
		void*                   request;             // 1B0
		BSNavmeshSearchLocation startLocation;       // 1B8
		void*                   secondaryNavmeshes;  // 1D8
		void*                   loadedNavmeshes;     // 1E0
		NiPoint3                avoidCenter;         // 1E8
		float                   avoidWeightSum;      // 1F4
		NiPoint3                hidePosition;        // 1F8
		std::uint8_t            pad204[4];           // 204
	};
	static_assert(sizeof(NavMeshSearchHide) == 0x208);
}

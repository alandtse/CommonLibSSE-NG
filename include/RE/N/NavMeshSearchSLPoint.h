#pragma once

#include "RE/B/BSNavmeshSearch.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class NavMeshSearchSLPoint : public BSNavmeshSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_NavMeshSearchSLPoint;
		inline static constexpr auto VTABLE = VTABLE_NavMeshSearchSLPoint;

		~NavMeshSearchSLPoint() override;             // 00
		bool IsGoalNode(AStarNode* a_node) override;  // 02

		// members
		std::uint8_t pad1B0[0x28];        // 1B0
		void*        request;             // 1D8
		void*        secondaryNavmeshes;  // 1E0
		void*        loadedNavmeshes;     // 1E8
		float        minRange;            // 1F0
		float        maxRange;            // 1F4
	};
	static_assert(sizeof(NavMeshSearchSLPoint) == 0x1F8);
}

#pragma once

#include "RE/A/AStarSearch.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSNavmesh;
	class BSNavmeshSearchFilters;

	struct BSNavmeshSearchLocation
	{
	public:
		// members
		BSNavmesh*    navmesh;        // 00
		std::uint16_t triangleIndex;  // 08
		std::uint8_t  pad0A[6];       // 0A
		NiPoint3      position;       // 10
		std::uint32_t pad1C;          // 1C
	};
	static_assert(sizeof(BSNavmeshSearchLocation) == 0x20);

	class BSNavmeshSearch : public AStarSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSNavmeshSearch;
		inline static constexpr auto VTABLE = VTABLE_BSNavmeshSearch;

		~BSNavmeshSearch() override;                               // 00
		bool ExpandNode(AStarNode* a_node, void* a_out) override;  // 01
		bool IsGoalNode(AStarNode* a_node) override;               // 02

		// members
		BSNavmeshSearchLocation startLocation;                // 160
		BSNavmeshSearchLocation goalLocation;                 // 180
		BSNavmeshSearchFilters* filters;                      // 1A0
		float                   preferredTriangleMultiplier;  // 1A8
		std::uint32_t           pad1AC;                       // 1AC
	};
	static_assert(sizeof(BSNavmeshSearch) == 0x1B0);
}

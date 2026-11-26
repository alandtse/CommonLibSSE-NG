#pragma once

#include "RE/A/AStarSearch.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class NavMeshSearchFitSphere : public AStarSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_NavMeshSearchFitSphere;
		inline static constexpr auto VTABLE = VTABLE_NavMeshSearchFitSphere;

		~NavMeshSearchFitSphere() override;                        // 00
		bool ExpandNode(AStarNode* a_node, void* a_out) override;  // 01
		bool IsGoalNode(AStarNode* a_node) override;               // 02

		// members
		NiPoint3      center;                   // 160
		float         minRadius;                // 16C
		float         clearRadius;              // 170
		std::uint32_t pad174;                   // 174
		void**        loadedNavmeshesData;      // 178
		std::uint32_t loadedNavmeshesCapacity;  // 180
		std::uint32_t pad184;                   // 184
		std::uint32_t loadedNavmeshesSize;      // 188
		std::uint32_t pad18C;                   // 18C
		void*         filterContext;            // 190
		bool          allowFlag;                // 198
		bool          landingZoneFlag;          // 199
		std::uint8_t  pad19A[6];                // 19A
	};
	static_assert(sizeof(NavMeshSearchFitSphere) == 0x1A0);
}

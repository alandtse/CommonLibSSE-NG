#pragma once

#include "RE/A/AStarSearch.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class PathingRequestClosePoint;

	class NavMeshSearchClosePoint : public AStarSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_NavMeshSearchClosePoint;
		inline static constexpr auto VTABLE = VTABLE_NavMeshSearchClosePoint;

		~NavMeshSearchClosePoint() override;                       // 00
		bool ExpandNode(AStarNode* a_node, void* a_out) override;  // 01
		bool IsGoalNode(AStarNode* a_node) override;               // 02

		// members
		PathingRequestClosePoint* request;              // 160
		std::uint8_t              startLocation[0x20];  // 168
		float                     searchRadius;         // 188
		std::uint8_t              pad18C[0x18];         // 18C
		NiPoint3                  avoidCenter;          // 1A4
		float                     avoidRadius;          // 1B0
		std::uint32_t             pad1B4;               // 1B4
		void*                     filterContext;        // 1B8
		bool                      startInTerrainPlus;   // 1C0
		std::uint8_t              pad1C1[7];            // 1C1
	};
	static_assert(sizeof(NavMeshSearchClosePoint) == 0x1C8);
}

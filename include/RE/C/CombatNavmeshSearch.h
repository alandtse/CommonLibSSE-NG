#pragma once

#include "RE/B/BSFastNavmeshTriLocation.h"
#include "RE/B/BSPathingRequest.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	struct CombatNavmeshSearchNode;

	class CombatNavmeshSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatNavmeshSearch;
		inline static constexpr auto VTABLE = VTABLE_CombatNavmeshSearch;

		virtual ~CombatNavmeshSearch();  // 00

		// members
		std::uint8_t                               pad08[0x118 - 0x08];    // 008
		CombatNavmeshSearchNode*                   savedGoalNode;          // 118
		CombatNavmeshSearchNode*                   currentNode;            // 120
		std::uint8_t                               pad128[0x08];           // 128
		BSTSmallArray<CombatNavmeshSearchNode*, 3> neighbors;              // 130
		bool                                       shouldYield;            // 158
		std::uint8_t                               pad159[0x07];           // 159
		void*                                      unk160;                 // 160
		BSTSmartPointer<BSPathingRequest>          request;                // 168 - refcount at +08
		std::uint8_t                               pad170[0x1D0 - 0x170];  // 170
		BSFastNavmeshTriLocation*                  bestGoal;               // 1D0 - null until A* result==2; confirmed SE+VR binary RE
		void*                                      unk1D8;                 // 1D8
		std::uint32_t                              status;                 // 1E0 - 2 = no goal, 1 = goal found
		std::uint32_t                              pad1E4;                 // 1E4
	};
	static_assert(sizeof(CombatNavmeshSearch) == 0x1E8, "size");
}

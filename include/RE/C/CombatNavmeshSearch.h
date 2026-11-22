#pragma once

#include "RE/B/BSFastNavmeshTriLocation.h"
#include "RE/B/BSNavmeshSearch.h"
#include "RE/B/BSPathingRequest.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	class CombatNavmeshSearch : public BSNavmeshSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatNavmeshSearch;
		inline static constexpr auto VTABLE = VTABLE_CombatNavmeshSearch;

		~CombatNavmeshSearch() override;

		// members
		void*                             pad08[(0x160 - 0x08) / 8];  // 008
		void*                             unk160;                     // 160
		BSTSmartPointer<BSPathingRequest> request;                    // 168 - refcount at +08
		std::uint8_t                      pad170[0x1D0 - 0x170];      // 170
		BSFastNavmeshTriLocation*         bestGoal;                   // 1D0 - null until A* result==2; confirmed SE+VR binary RE
		std::uint64_t                     unk1D8;                     // 1D8
		std::uint32_t                     unk1E0;                     // 1E0 - set to 2 by the goal-policy ctor when the goal is rejected
		std::uint32_t                     pad1E4;                     // 1E4
	};
	static_assert(sizeof(CombatNavmeshSearch) == 0x1E8, "size");
}

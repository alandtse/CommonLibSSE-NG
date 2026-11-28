#pragma once

#include "RE/B/BSFastNavmeshTriLocation.h"
#include "RE/B/BSNavmeshSearch.h"

namespace RE
{
	class CombatNavmeshSearch : public BSNavmeshSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatNavmeshSearch;
		inline static constexpr auto VTABLE = VTABLE_CombatNavmeshSearch;

		~CombatNavmeshSearch() override;

		// members
		void*                     pad1B0[(0x1D0 - 0x1B0) / 8];  // 1B0
		BSFastNavmeshTriLocation* bestGoal;                     // 1D0 - null until A* result==2
	};
	static_assert(sizeof(CombatNavmeshSearch) == 0x1D8, "size");
}

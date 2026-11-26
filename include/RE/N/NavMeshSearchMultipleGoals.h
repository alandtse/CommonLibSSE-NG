#pragma once

#include "RE/B/BSNavmeshSearch.h"

namespace RE
{
	class NavMeshSearchMultipleGoals : public BSNavmeshSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_NavMeshSearchMultipleGoals;
		inline static constexpr auto VTABLE = VTABLE_NavMeshSearchMultipleGoals;

		~NavMeshSearchMultipleGoals() override;  // 00

		// members
		void*          goalKeysAllocator;  // 1B0
		std::uint64_t* goalKeysData;       // 1B8
		std::uint32_t  goalKeysCapacity;   // 1C0
		std::uint32_t  pad1C4;             // 1C4
		std::uint32_t  goalKeysSize;       // 1C8
		std::uint32_t  pad1CC;             // 1CC
		std::int32_t   foundGoalIndex;     // 1D0
		std::uint32_t  pad1D4;             // 1D4
	};
	static_assert(sizeof(NavMeshSearchMultipleGoals) == 0x1D8);
}

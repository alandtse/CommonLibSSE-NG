#pragma once

#include "RE/C/CombatFlankingSearchData.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatPathingSearchPolicyStandard
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingSearchPolicyStandard;

		// members
		void*     request;          // 00
		std::byte pad08;            // 08
		bool      isLargeActor;     // 09
		bool      requestFlagBit4;  // 0A
		bool      requestFlagBit5;  // 0B
		std::byte pad0C[0x4];       // 0C
	};
	static_assert(sizeof(CombatPathingSearchPolicyStandard) == 0x10);

	class CombatPathingSearchPolicyFlank : public CombatPathingSearchPolicyStandard
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingSearchPolicyFlank;

		// members
		std::byte                           pad10[0x8];            // 10
		NiPointer<CombatFlankingSearchData> flankingSearchData;    // 18
		std::byte                           pad20[0xC];            // 20
		std::uint32_t                       flankedCellsCapacity;  // 2C
		std::byte                           pad30[0x8];            // 30
		void*                               flankedCellsSentinel;  // 38
		std::byte                           pad40[0x8];            // 40
		void*                               flankedCellsBuckets;   // 48
		void*                               searchContext;         // 50
	};
	static_assert(sizeof(CombatPathingSearchPolicyFlank) == 0x58);
}

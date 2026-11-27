#pragma once

#include "RE/C/CombatObject.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class CombatFlankingSearchData : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatFlankingSearchData;
		inline static constexpr auto VTABLE = VTABLE_CombatFlankingSearchData;

		~CombatFlankingSearchData() override;  // 00

		// members
		NiPoint3      startPosition;   // 10
		NiPoint3      targetPosition;  // 1C
		NiPoint3      startDirection;  // 28
		NiPoint3      flankPosition;   // 34
		float         startAngle;      // 40
		float         goalAngle;       // 44
		float         angleProgress;   // 48
		float         startDistance;   // 4C
		float         maxDistance;     // 50
		float         minDistance;     // 54
		std::uint32_t directionIndex;  // 58
	};
	static_assert(sizeof(CombatFlankingSearchData) == 0x60);
}

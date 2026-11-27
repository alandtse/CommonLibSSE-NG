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
		NiPoint3      unk10;           // 10
		NiPoint3      unk1C;           // 1C
		NiPoint3      unk28;           // 28
		NiPoint3      unk34;           // 34
		float         unk40;           // 40
		float         unk44;           // 44
		float         unk48;           // 48
		float         unk4C;           // 4C
		float         unk50;           // 50
		float         unk54;           // 54
		std::uint32_t directionIndex;  // 58
	};
	static_assert(sizeof(CombatFlankingSearchData) == 0x60);
}

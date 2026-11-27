#pragma once

#include "RE/C/CombatObject.h"

namespace RE
{
	class CombatCoverSearchDebugData : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatCoverSearchDebugData;
		inline static constexpr auto VTABLE = VTABLE_CombatCoverSearchDebugData;

		~CombatCoverSearchDebugData() override;  // 00

		// members
		CombatObject* unk10;        // 10
		std::byte     unk18[0x18];  // 18
	};
	static_assert(sizeof(CombatCoverSearchDebugData) == 0x30);
}

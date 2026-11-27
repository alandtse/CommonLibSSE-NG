#pragma once

#include "RE/C/CombatObject.h"

namespace RE
{
	class CombatPathingDebugData : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingDebugData;
		inline static constexpr auto VTABLE = VTABLE_CombatPathingDebugData;

		~CombatPathingDebugData() override;  // 00

		// members
		std::byte unk10[0x58];  // 10
	};
	static_assert(sizeof(CombatPathingDebugData) == 0x68);
}

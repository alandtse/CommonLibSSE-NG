#pragma once

#include "RE/A/AITimer.h"

namespace RE
{
	class CombatBehaviorCastImmediateSpell
	{
	public:
		// members
		AITimer      timer00;     // 00
		std::uint8_t unk08;       // 08
		std::byte    unk09[0x3];  // 09
	};
	static_assert(sizeof(CombatBehaviorCastImmediateSpell) == 0xC);
}

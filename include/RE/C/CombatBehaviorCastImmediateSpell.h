#pragma once

#include "RE/A/AITimer.h"

namespace RE
{
	class CombatBehaviorCastImmediateSpell
	{
	public:
		// members
		AITimer   timer00;     // 00
		bool      isDualCast;  // 08
		std::byte unk09[0x3];  // 09
	};
	static_assert(sizeof(CombatBehaviorCastImmediateSpell) == 0xC);
}

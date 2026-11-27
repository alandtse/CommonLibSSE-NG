#pragma once

#include "RE/A/AITimer.h"

namespace RE
{
	class CombatBehaviorCastConcentrationSpell
	{
	public:
		// members
		AITimer   timer00;     // 00
		bool      isDualCast;  // 08
		std::byte unk09[0x3];  // 09
	};
	static_assert(sizeof(CombatBehaviorCastConcentrationSpell) == 0xC);
}

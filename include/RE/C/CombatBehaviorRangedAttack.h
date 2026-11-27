#pragma once

#include "RE/A/AITimeStamp.h"
#include "RE/A/AITimer.h"

namespace RE
{
	class CombatBehaviorRangedAttack
	{
	public:
		// members
		AITimer     timer00;      // 00
		AITimeStamp timeStamp08;  // 08
	};
	static_assert(sizeof(CombatBehaviorRangedAttack) == 0xC);
}

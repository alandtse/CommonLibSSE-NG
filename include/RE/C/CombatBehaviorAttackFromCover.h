#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorAttackFromCover
	{
	public:
		// members
		AITimer                 timer00;   // 00
		AITimer                 timer08;   // 08
		NiPointer<CombatObject> object10;  // 10
	};
	static_assert(sizeof(CombatBehaviorAttackFromCover) == 0x18);
}

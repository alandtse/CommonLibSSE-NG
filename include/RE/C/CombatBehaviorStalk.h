#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorStalk
	{
	public:
		// members
		NiPointer<CombatObject> object00;  // 00
		AITimer                 timer08;   // 08
		NiPointer<CombatObject> object10;  // 10
	};
	static_assert(sizeof(CombatBehaviorStalk) == 0x18);
}

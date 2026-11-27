#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorFindCover
	{
	public:
		// members
		NiPointer<CombatObject> object00;  // 00
		NiPointer<CombatObject> object08;  // 08
		NiPointer<CombatObject> object10;  // 10
		AITimer                 timer18;   // 18
	};
	static_assert(sizeof(CombatBehaviorFindCover) == 0x20);
}

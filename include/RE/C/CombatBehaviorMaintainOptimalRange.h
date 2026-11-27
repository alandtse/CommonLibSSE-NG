#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorMaintainOptimalRange
	{
	public:
		// members
		NiPointer<CombatObject> object00;  // 00
		AITimer                 timer08;   // 08
	};
	static_assert(sizeof(CombatBehaviorMaintainOptimalRange) == 0x10);
}

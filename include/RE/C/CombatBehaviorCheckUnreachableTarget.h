#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorCheckUnreachableTarget
	{
	public:
		// members
		NiPointer<CombatObject> object00;  // 00
		AITimer                 timer08;   // 08
	};
	static_assert(sizeof(CombatBehaviorCheckUnreachableTarget) == 0x10);
}

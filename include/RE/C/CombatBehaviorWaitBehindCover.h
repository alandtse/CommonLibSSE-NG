#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorWaitBehindCover
	{
	public:
		// members
		NiPointer<CombatObject> object00;  // 00
		NiPointer<CombatObject> object08;  // 08
		AITimer                 timer10;   // 10
	};
	static_assert(sizeof(CombatBehaviorWaitBehindCover) == 0x18);
}

#pragma once

#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorPursueTarget
	{
	public:
		// members
		NiPointer<CombatObject> object00;  // 00
	};
	static_assert(sizeof(CombatBehaviorPursueTarget) == 0x8);
}

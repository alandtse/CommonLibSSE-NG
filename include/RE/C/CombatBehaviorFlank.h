#pragma once

#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorFlank
	{
	public:
		// members
		NiPointer<CombatObject> object00;  // 00
		NiPointer<CombatObject> object08;  // 08
		NiPointer<CombatObject> object10;  // 10
		NiPointer<CombatObject> object18;  // 18
	};
	static_assert(sizeof(CombatBehaviorFlank) == 0x20);
}

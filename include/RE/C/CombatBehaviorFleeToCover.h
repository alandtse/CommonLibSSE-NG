#pragma once

#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorFleeToCover
	{
	public:
		// members
		NiPointer<CombatObject> object00;  // 00
		NiPointer<CombatObject> object08;  // 08
		NiPointer<CombatObject> object10;  // 10
	};
	static_assert(sizeof(CombatBehaviorFleeToCover) == 0x18);
}

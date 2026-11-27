#pragma once

#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorSearchWander
	{
	public:
		// members
		NiPointer<CombatObject> object00;  // 00
	};
	static_assert(sizeof(CombatBehaviorSearchWander) == 0x8);
}

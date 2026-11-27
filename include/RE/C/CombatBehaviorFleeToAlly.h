#pragma once

#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorFleeToAlly
	{
	public:
		// members
		NiPointer<CombatObject> object00;  // 00
	};
	static_assert(sizeof(CombatBehaviorFleeToAlly) == 0x8);
}

#pragma once

#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorStrafe
	{
	public:
		// members
		NiPointer<CombatObject> object00;  // 00
	};
	static_assert(sizeof(CombatBehaviorStrafe) == 0x8);
}

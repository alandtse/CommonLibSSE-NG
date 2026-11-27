#pragma once

#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorSearchCenter
	{
	public:
		// members
		NiPointer<CombatObject> object00;  // 00
	};
	static_assert(sizeof(CombatBehaviorSearchCenter) == 0x8);
}

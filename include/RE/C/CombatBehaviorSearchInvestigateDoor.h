#pragma once

#include "RE/A/AITimer.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorSearchInvestigateDoor
	{
	public:
		// members
		NiPointer<CombatObject> object00;    // 00
		ObjectRefHandle         handle08;    // 08
		AITimer                 timer0C;     // 0C
		std::byte               unk14[0x4];  // 14
	};
	static_assert(sizeof(CombatBehaviorSearchInvestigateDoor) == 0x18);
}

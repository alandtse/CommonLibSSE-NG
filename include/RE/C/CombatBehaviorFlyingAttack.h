#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorFlyingAttack
	{
	public:
		// members
		NiPointer<CombatObject> object00;    // 00
		NiPointer<CombatObject> object08;    // 08
		NiPointer<CombatObject> object10;    // 10
		NiPoint3                unk18;       // 18
		AITimer                 timer24;     // 24
		std::byte               unk2C[0x4];  // 2C
	};
	static_assert(sizeof(CombatBehaviorFlyingAttack) == 0x30);
}

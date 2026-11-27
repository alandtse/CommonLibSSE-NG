#pragma once

#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorLand
	{
	public:
		// members
		NiPointer<CombatObject> object00;    // 00
		NiPointer<CombatObject> object08;    // 08
		float                   unk10;       // 10
		std::byte               unk14[0x4];  // 14
	};
	static_assert(sizeof(CombatBehaviorLand) == 0x18);
}

#pragma once

#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorFlee
	{
	public:
		// members
		NiPointer<CombatObject> object00;    // 00
		float                   unk08;       // 08
		std::byte               unk0C[0x4];  // 0C
	};
	static_assert(sizeof(CombatBehaviorFlee) == 0x10);
}

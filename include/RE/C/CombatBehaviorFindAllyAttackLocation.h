#pragma once

#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorFindAllyAttackLocation
	{
	public:
		// members
		NiPointer<CombatObject> object00;  // 00
		std::uint64_t           unk08;     // 08
	};
	static_assert(sizeof(CombatBehaviorFindAllyAttackLocation) == 0x10);
}

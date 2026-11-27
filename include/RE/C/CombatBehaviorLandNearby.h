#pragma once

#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorLandNearby
	{
	public:
		// members
		NiPointer<CombatObject> object00;     // 00
		NiPointer<CombatObject> object08;     // 08
		float                   maxDistance;  // 10
		std::byte               unk14[0x4];   // 14
	};
	static_assert(sizeof(CombatBehaviorLandNearby) == 0x18);
}

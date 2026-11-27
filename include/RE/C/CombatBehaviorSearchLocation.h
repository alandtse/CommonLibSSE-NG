#pragma once

#include "RE/A/AITimer.h"
#include "RE/B/BSPathingLocation.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class TESForm;

	class CombatBehaviorSearchLocation
	{
	public:
		// members
		NiPointer<CombatObject> object00;    // 00
		AITimer                 timer08;     // 08
		NiPoint3                unk10;       // 10
		std::byte               unk1C[0x4];  // 1C
		TESForm*                space20;     // 20
		BSPathingLocation       location28;  // 28
	};
	static_assert(sizeof(CombatBehaviorSearchLocation) == 0x58);
}

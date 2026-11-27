#pragma once

#include "RE/A/AITimer.h"
#include "RE/B/BGSWorldLocation.h"
#include "RE/B/BSPathingLocation.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorSearchLocation
	{
	public:
		// members
		NiPointer<CombatObject> object00;        // 00
		AITimer                 timer08;         // 08
		BGSWorldLocation        searchLocation;  // 10
		BSPathingLocation       location28;      // 28
	};
	static_assert(sizeof(CombatBehaviorSearchLocation) == 0x58);
}

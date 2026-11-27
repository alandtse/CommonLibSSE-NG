#pragma once

#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatTargetLocation;
	class CombatTargetLocationSearch;

	class CombatTargetLocationSearchResult : public RE::CombatObject
	{
	public:
		// members
		NiPointer<CombatTargetLocationSearch> search;    // 10
		NiPointer<CombatTargetLocation>       location;  // 18
	};
	static_assert(sizeof(CombatTargetLocationSearchResult) == 0x20);
}

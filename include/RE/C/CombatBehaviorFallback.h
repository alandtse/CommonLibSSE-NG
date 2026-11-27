#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatBehavior.h"
#include "RE/C/CombatPath.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorFallback : public CombatBehaviorAction
	{
	public:
		void Enter();
		void Update();

		// members
		NiPointer<CombatPath> path;     // 00
		AITimer               timer08;  // 08
		AITimer               timer10;  // 10
	};
	static_assert(sizeof(CombatBehaviorFallback) == 0x18);
}

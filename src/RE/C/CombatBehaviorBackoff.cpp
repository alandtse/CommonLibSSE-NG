#include "RE/C/CombatBehaviorBackoff.h"

namespace RE
{
	void CombatBehaviorBackoff::Enter()
	{
		using func_t = decltype(&CombatBehaviorBackoff::Enter);
		REL::Relocation<func_t> func{ RELOCATION_ID(46724, 0) };
		return func(this);
	}

	void CombatBehaviorBackoff::Update()
	{
		using func_t = decltype(&CombatBehaviorBackoff::Update);
		REL::Relocation<func_t> func{ RELOCATION_ID(46725, 0) };
		return func(this);
	}
}

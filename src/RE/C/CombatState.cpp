#include "RE/C/CombatState.h"

namespace RE
{
	bool CombatState::QTargetLost() const
	{
		using func_t = decltype(&CombatState::QTargetLost);
		REL::Relocation<func_t> func{ RELOCATION_ID(48026, 0) };
		return func(this);
	}

	bool CombatState::CheckShouldHide() const
	{
		using func_t = decltype(&CombatState::CheckShouldHide);
		REL::Relocation<func_t> func{ RELOCATION_ID(45661, 0) };
		return func(this);
	}

	bool CombatState::CheckShouldFlee() const
	{
		using func_t = decltype(&CombatState::CheckShouldFlee);
		REL::Relocation<func_t> func{ RELOCATION_ID(45660, 0) };
		return func(this);
	}
}

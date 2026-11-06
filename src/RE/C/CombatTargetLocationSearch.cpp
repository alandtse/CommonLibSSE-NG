#include "RE/C/CombatTargetLocationSearch.h"

namespace RE
{
	CombatTargetLocationSearch* CombatTargetLocationSearch::Ctor(Actor* actor, Actor* target, float R)
	{
		using func_t = CombatTargetLocationSearch*(CombatTargetLocationSearch*, Actor*, Actor*, float);
		static REL::Relocation<func_t> func{ RELOCATION_ID(45702, 47011) };
		return func(this, actor, target, R);
	}
}

#include "RE/C/CombatController.h"

#include "RE/A/Actor.h"
#include "RE/N/NiPoint3.h"

using namespace REL;

namespace RE
{
	bool CombatController::CheckCombatArea(Actor* attacker) const
	{
		using func_t = decltype(&CombatController::CheckCombatArea);
		REL::Relocation<func_t> func{ RELOCATION_ID(32508, 0) };
		return func(this, attacker);
	}

	bool CombatController::CheckStraightPath(NiPoint3& dst, float dist, float min_dist) const
	{
		using func_t = decltype(&CombatController::CheckStraightPath);
		REL::Relocation<func_t> func{ RELOCATION_ID(32513, 0) };
		return func(this, dst, dist, min_dist);
	}
}

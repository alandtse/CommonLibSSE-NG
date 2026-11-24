#pragma once

#include "RE/C/CombatBehaviorContextMagic.h"

namespace RE
{
	class TESShout;

	class CombatBehaviorContextShout : public CombatBehaviorContextMagic
	{
	public:
		float CalcCastMagicChance() const;

		bool TryCastShout()
		{
			using func_t = bool(CombatBehaviorContextShout*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(48803, 49758) };
			return func(this);
		}

		// members
		TESShout* shout;  // 20
	};
	static_assert(sizeof(CombatBehaviorContextShout) == 0x28);
}

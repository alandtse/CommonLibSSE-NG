#include "RE/C/CombatBehaviorBlockAttack.h"

#include "RE/C/CombatBehaviorTreeNode.h"

namespace RE
{
	void CombatBehaviorBlockAttack::Enter()
	{
		using func_t = decltype(&CombatBehaviorBlockAttack::Enter);
		REL::Relocation<func_t> func{ RELOCATION_ID(46628, 0) };
		return func(this);
	}

	void CombatBehaviorBlockAttack::Exit()
	{
		using func_t = decltype(&CombatBehaviorBlockAttack::Exit);
		REL::Relocation<func_t> func{ RELOCATION_ID(46630, 0) };
		return func(this);
	}

	void CombatBehaviorBlockAttack::Update()
	{
		using func_t = decltype(&CombatBehaviorBlockAttack::Update);
		REL::Relocation<func_t> func{ RELOCATION_ID(46629, 0) };
		return func(this);
	}
}

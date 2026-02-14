#include "RE/C/ChildSelectorBase.h"

namespace RE
{
	bool ChildSelectorBase::ValidateChildren(CombatBehaviorTreeNode* node, BSFixedString const& type)
	{
		using func_t = decltype(&ChildSelectorBase::ValidateChildren);
		REL::Relocation<func_t> func{ RELOCATION_ID(46151, 0) };
		return func(node, type);
	}
}

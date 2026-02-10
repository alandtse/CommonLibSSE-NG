#pragma once

#include "RE/C/CombatBehavior.h"
#include "RE/C/CombatBehaviorThread.h"
#include "RE/C/CombatBehaviorTreeNode.h"
#include "RE/C/ConditionalChildSelector.h"
#include "RE/N/NextChildSelector.h"
#include "RE/R/RandomValueChildSelector.h"
#include "RE/T/TLSData.h"
#include "RE/V/ValueChildSelector.h"
#include "RE/W/WeightedRandomChildSelector.h"

namespace RE
{
	template <typename Selector>
	class CombatBehaviorChildSelector : public CombatBehaviorNode, public Selector
	{
	public:
		static bool Validate(CombatBehaviorTreeNode* node)
		{
			return CombatBehaviorNode::Validate(node) && Selector::Validate(node);
		}

		void Enter()
		{
			auto cur_thread = GetStaticTLSData()->combatAIThread;
			auto ind = Selector::SelectChild(cur_thread->active_node, 0xFFFFFFFF);
			if (ind == -1) {
				cur_thread->SetFailed(true);
				cur_thread->Ascend();
			} else {
				cur_thread->Descend(ind);
			}
		}
	};

}

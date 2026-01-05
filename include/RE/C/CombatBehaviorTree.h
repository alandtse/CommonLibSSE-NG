#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"

namespace RE
{
	class CombatBehaviorTreeNode;

	class CombatBehaviorTree
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatBehaviorTree;
		inline static constexpr auto VTABLE = VTABLE_CombatBehaviorTree;

		class TreeBuilder
		{
		public:
			// members
			BSTArray<CombatBehaviorTreeNode*> nodeArray;  // 00
		};
		static_assert(sizeof(TreeBuilder) == 0x18);

		virtual void Initialize();  // 00

		static TreeBuilder* AddNode(TreeBuilder* a_out, const char* a_name, CombatBehaviorTreeNode* a_node)
		{
			using func_t = TreeBuilder*(TreeBuilder*, const char*, CombatBehaviorTreeNode*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(46261, 47516) };
			return func(a_out, a_name, a_node);
		}

		// members
		BSFixedString           name;  // 08
		CombatBehaviorTreeNode* root;  // 10
	};
	static_assert(sizeof(CombatBehaviorTree) == 0x18);
}

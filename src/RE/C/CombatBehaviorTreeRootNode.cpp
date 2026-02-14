#include "RE/C/CombatBehaviorTreeRootNode.h"

namespace RE
{
	void CombatBehaviorTreeRootNode::Enter(CombatBehaviorThread* thread)
	{
		using func_t = decltype(&CombatBehaviorTreeRootNode::Enter);
		REL::Relocation<func_t> func{ RELOCATION_ID(46323, 0) };
		return func(this, thread);
	}

	void CombatBehaviorTreeRootNode::Update(CombatBehaviorThread* thread)
	{
		using func_t = decltype(&CombatBehaviorTreeRootNode::Update);
		REL::Relocation<func_t> func{ RELOCATION_ID(46324, 0) };
		return func(this, thread);
	}

	void CombatBehaviorTreeRootNode::Abort(CombatBehaviorThread* thread)
	{
		using func_t = decltype(&CombatBehaviorTreeRootNode::Abort);
		REL::Relocation<func_t> func{ RELOCATION_ID(46325, 0) };
		return func(this, thread);
	}

	void CombatBehaviorTreeRootNode::SaveGame(CombatBehaviorThread* thread, BGSSaveFormBuffer* buf)
	{
		using func_t = decltype(&CombatBehaviorTreeRootNode::SaveGame);
		REL::Relocation<func_t> func{ RELOCATION_ID(46327, 0) };
		return func(this, thread, buf);
	}

	void CombatBehaviorTreeRootNode::LoadGame(CombatBehaviorThread* thread, BGSLoadFormBuffer* buf)
	{
		using func_t = decltype(&CombatBehaviorTreeRootNode::LoadGame);
		REL::Relocation<func_t> func{ RELOCATION_ID(46328, 0) };
		return func(this, thread, buf);
	}

	bool CombatBehaviorTreeRootNode::Validate(CombatBehaviorTreeNode* node) const
	{
		using func_t = decltype(&CombatBehaviorTreeRootNode::Validate);
		REL::Relocation<func_t> func{ RELOCATION_ID(46326, 0) };
		return func(this, node);
	}

	const BSFixedString& CombatBehaviorTreeRootNode::GetType() const
	{
		using func_t = decltype(&CombatBehaviorTreeRootNode::GetType);
		REL::Relocation<func_t> func{ RELOCATION_ID(46329, 0) };
		return func(this);
	}
}

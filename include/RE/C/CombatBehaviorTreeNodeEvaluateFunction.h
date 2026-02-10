#pragma once

namespace RE
{
	template <typename Expr>
	class CombatBehaviorTreeNodeEvaluateFunction : public CombatBehaviorTreeNode
	{
	public:
		~CombatBehaviorTreeNodeEvaluateFunction() = default;

		void Update(CombatBehaviorThread* thread) override
		{
			auto old_active = thread->active_node;

			if (!this->expr) {
				thread->fail_state = CombatBehaviorThread::FailState::kFailed;
			}

			if (thread->active_node == old_active)
				thread->Ascend();
		}

		const BSFixedString& GetType() const override
		{
			static BSFixedString ans("CombatBehaviorTreeNodeEvaluateFunction");
			return ans;
		}

		// members
		Expr expr;
	};
}

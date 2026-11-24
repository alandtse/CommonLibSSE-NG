#pragma once

namespace RE
{
	class IMovementPlannerAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementPlannerAgent;
		inline static constexpr auto VTABLE = VTABLE_IMovementPlannerAgent;

		virtual ~IMovementPlannerAgent();  // 00

		// add
		virtual void Unk_01(void);  // 01
		virtual void Unk_02(void);  // 02 - planner update
		virtual void Unk_03(void);  // 03
	};
	static_assert(sizeof(IMovementPlannerAgent) == 0x8);
}

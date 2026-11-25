#pragma once

namespace RE
{
	// per-step action run by a path follower (door approach, jump)
	struct IPathFollowerAction
	{
	public:
		inline static constexpr auto RTTI = RTTI_IPathFollowerAction;
		inline static constexpr auto VTABLE = VTABLE_IPathFollowerAction;

		virtual ~IPathFollowerAction();  // 00

		// add
		virtual bool UpdateSpeed(void* a_updateData, float a_deltaTime, float* a_speed);     // 01 - base returns false (no override)
		virtual bool Prepare(void* a_updateData, float* a_prepareData, void* a_param3) = 0;  // 02
		virtual bool GetTargetSpeed(void* a_param1, void* a_updateData, float* a_out) = 0;   // 03
	};
	static_assert(sizeof(IPathFollowerAction) == 0x8);
}

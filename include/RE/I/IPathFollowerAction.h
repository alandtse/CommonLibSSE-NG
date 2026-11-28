#pragma once

namespace RE
{
	struct PathFollowerStateUpdateData;

	// per-step action run by a path follower (door approach, jump)
	struct IPathFollowerAction
	{
	public:
		inline static constexpr auto RTTI = RTTI_IPathFollowerAction;
		inline static constexpr auto VTABLE = VTABLE_IPathFollowerAction;

		virtual ~IPathFollowerAction();  // 00

		// add
		virtual bool UpdateSpeed(PathFollowerStateUpdateData* a_updateData, float a_pathIndex, float* a_speed);  // 01 - base returns false (no override)
		virtual bool Prepare(PathFollowerStateUpdateData* a_updateData, float* a_out) = 0;                       // 02
		virtual bool GetTargetSpeed(PathFollowerStateUpdateData* a_updateData, float* a_out) = 0;                // 03
	};
	static_assert(sizeof(IPathFollowerAction) == 0x8);
}

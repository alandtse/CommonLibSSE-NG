#pragma once

namespace RE
{
	struct MovementPlannerUpdateDataSmallDelta
	{
	public:
		// members
		float deltaTime;  // 00
		float unk4;       // 04
	};
	static_assert(sizeof(MovementPlannerUpdateDataSmallDelta) == 0x8);
}

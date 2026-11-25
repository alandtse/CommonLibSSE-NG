#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	// turn requested by the path follower at a path node
	struct PathFollowerTurnTarget
	{
	public:
		void GetFacingAngles(NiPoint3* a_position, float* a_current, float a_zOffset, float* a_outFacing)
		{
			using func_t = void(PathFollowerTurnTarget*, NiPoint3*, float*, float, float*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90623, 93153) };
			func(this, a_position, a_current, a_zOffset, a_outFacing);
		}

		// members
		std::uint32_t mode;            // 00 - 1: explicit angle, 2/3: look at targetPosition
		NiPoint3      targetPosition;  // 04
		float         targetAngle;     // 10
		float         tolerance;       // 14
	};
	static_assert(sizeof(PathFollowerTurnTarget) == 0x18);
}

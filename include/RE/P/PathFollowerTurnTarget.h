#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	// turn requested by the path follower at a path node
	struct PathFollowerTurnTarget
	{
	public:
		// members
		std::uint32_t flag;         // 00
		NiPoint3      direction;    // 04
		float         targetAngle;  // 10
		float         tolerance;    // 14
	};
	static_assert(sizeof(PathFollowerTurnTarget) == 0x18);
}

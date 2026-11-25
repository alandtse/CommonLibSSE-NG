#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	// Input to BSPathingGoal::SetFromDescriptor.
	struct BSPathingGoalDescriptor
	{
	public:
		enum class Type : std::uint32_t
		{
			kNone = 0,
			kOrientation = 1,
			kPosition = 2,
			kPositionFlying = 3
		};

		// members
		stl::enumeration<Type, std::uint32_t> type;       // 00
		NiPoint3                              point;      // 04
		float                                 angle;      // 10
		float                                 tolerance;  // 14
	};
	static_assert(sizeof(BSPathingGoalDescriptor) == 0x18);
}

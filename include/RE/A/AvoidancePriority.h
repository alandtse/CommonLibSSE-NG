#pragma once

namespace RE
{
	// Avoidance ordering key: larger compares as higher priority (radius first, then formID).
	struct AvoidancePriority
	{
	public:
		// members
		std::uint32_t radius;  // 00 - (int)ActorState radius; 0xFFFFFFFF for non-moving or non-AI actors
		std::uint32_t formID;  // 04
	};
	static_assert(sizeof(AvoidancePriority) == 0x8);
}

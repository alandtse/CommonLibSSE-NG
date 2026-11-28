#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	// input/output of the movement handler agents' per-frame update
	struct MovementHandlerUpdateDataSmallDelta
	{
	public:
		// members
		std::uint8_t  obstacles[0x20];    // 00 - scrap array: allocator, data, capacity, size
		std::uint8_t  avoidShapes[0x20];  // 20 - scrap array
		NiPoint3      targetDirection;    // 40 - x: -pitch, z: heading
		float         speed;              // 4C
		NiPoint3      targetRotation;     // 50
		std::uint32_t unk5C;              // 5C
		std::uint32_t unk60;              // 60
		float         minSpeed;           // 64
		std::uint32_t unk68;              // 68
		float         deltaTime;          // 6C
		float         acceleration;       // 70
		float         deceleration;       // 74
		std::uint32_t unk78;              // 78
		float         unk7C;              // 7C - angle output clamp
		float         unk80;              // 80
		std::uint32_t pad84;              // 84
	};
	static_assert(sizeof(MovementHandlerUpdateDataSmallDelta) == 0x88);
}

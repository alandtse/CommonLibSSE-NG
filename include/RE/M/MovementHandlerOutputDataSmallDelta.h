#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	// handler results at 00-1F, tweener results at 20-3F
	struct MovementHandlerOutputDataSmallDelta
	{
	public:
		// members
		NiPoint3      rotation;                // 00
		float         speed;                   // 0C
		NiPoint3      angularVelocity;         // 10
		float         deltaTime;               // 1C
		NiPoint3      tweenedRotation;         // 20
		float         tweenedSpeed;            // 2C
		NiPoint3      tweenedAngularVelocity;  // 30
		std::uint32_t unk3C;                   // 3C
	};
	static_assert(sizeof(MovementHandlerOutputDataSmallDelta) == 0x40);
}

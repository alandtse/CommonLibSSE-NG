#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	// per-frame translation and rotation produced by MovementControllerAI::UpdateSmallDelta
	struct MovementUpdateDeltas
	{
	public:
		// members
		NiPoint3 translationDelta;  // 00
		float    pad0C;             // 0C
		NiPoint3 rotationDelta;     // 10
	};
	static_assert(sizeof(MovementUpdateDeltas) == 0x1C);
}

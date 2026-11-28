#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/N/NiTransform.h"

namespace RE
{
	struct MovementCorrectionData
	{
	public:
		// members
		NiTransform transform;                 // 00 - ActorState::GetTransform with the clip rotation applied
		NiPoint3    translationDelta;          // 34
		NiPoint3    rotationDelta;             // 40
		NiPoint3    translationStartVelocity;  // 4C
		NiPoint3    translationEndVelocity;    // 58
		NiPoint3    rotationStartVelocity;     // 64
		NiPoint3    rotationEndVelocity;       // 70
		float       startTime;                 // 7C
		float       endTime;                   // 80
		float       tailEndTime;               // 84
	};
	static_assert(sizeof(MovementCorrectionData) == 0x88);
}

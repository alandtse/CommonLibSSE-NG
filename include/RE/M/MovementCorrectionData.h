#pragma once

#include "RE/N/NiMatrix3.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	// Argument of MovementTweenerAgentFixedDelta::SetCorrectionData; 0x88 is the extent read, not a known allocation size.
	struct MovementCorrectionData
	{
	public:
		// members
		NiMatrix3    rotation;                  // 00
		std::uint8_t unk24[16];                 // 24
		NiPoint3     translationDelta;          // 34
		NiPoint3     rotationDelta;             // 40
		NiPoint3     translationStartVelocity;  // 4C
		NiPoint3     translationEndVelocity;    // 58
		NiPoint3     rotationStartVelocity;     // 64
		NiPoint3     rotationEndVelocity;       // 70
		float        startTime;                 // 7C
		float        endTime;                   // 80
		float        tailEndTime;               // 84
	};
	static_assert(sizeof(MovementCorrectionData) == 0x88);
}

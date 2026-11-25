#pragma once

#include "RE/N/NiMatrix3.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	// Out argument of IMovementTweenerAgent::GetMotionTransform.
	struct MovementTweenerAgentOutputData
	{
	public:
		// members
		NiPoint3  translation;  // 00 - implementations write the zero vector here
		NiMatrix3 rotation;     // 0C - implementations write identity here
		float     unk30;        // 30
	};
	static_assert(sizeof(MovementTweenerAgentOutputData) == 0x34);
}

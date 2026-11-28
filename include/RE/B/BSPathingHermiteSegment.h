#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	// Cubic Hermite path segment: p(t) = ((a t + b) t + c) t + p0.
	struct BSPathingHermiteSegment
	{
	public:
		// members
		NiPoint3 cubicCoeff;          // 00
		NiPoint3 quadCoeff;           // 0C
		NiPoint3 startTangent;        // 18
		NiPoint3 startPoint;          // 24
		NiPoint3 chord;               // 30
		float    invChordLengthSqXY;  // 3C
	};
	static_assert(sizeof(BSPathingHermiteSegment) == 0x40);
}

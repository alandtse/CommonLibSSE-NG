#pragma once

#include "RE/H/hkVector4.h"

namespace RE
{
	// source: activeragdoll; not independently Ghidra-verified (no consumer found)
	class BSLookAtModifierBoneData
	{
	public:
		// members
		std::int16_t index;                    // 00
		std::uint8_t pad02[14];                // 02
		float        forwardAxisLS[4];         // 10 (hkVector4)
		float        limitAngleDegrees;        // 20
		float        onGain;                   // 24
		float        offGain;                  // 28
		bool         enabled;                  // 2C
		std::uint8_t pad2D[3];                 // 2D
		float        currentForwardAxisLS[4];  // 30 (hkVector4)
	};
	static_assert(sizeof(BSLookAtModifierBoneData) == 0x40);
}

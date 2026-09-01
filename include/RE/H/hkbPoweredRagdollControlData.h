#pragma once

namespace RE
{
	// source: activeragdoll; not independently Ghidra-verified (no consumer found)
	class alignas(0x10) hkbPoweredRagdollControlData
	{
	public:
		// members
		float maxForce = 50.0f;                     // 00
		float tau = 0.8f;                           // 04
		float damping = 1.0f;                       // 08
		float proportionalRecoveryVelocity = 2.0f;  // 0C
		float constantRecoveryVelocity = 1.0f;      // 10
	};
}

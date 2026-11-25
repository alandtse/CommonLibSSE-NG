#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	// per-actor entry in MovementAgentActorAvoider's avoided-actor array
	struct AvoidedActorInfo
	{
	public:
		// members
		NiPoint3      position;      // 00
		NiPoint3      lastPosition;  // 0C - sentinel until an avoid node is added
		std::uint8_t  unk18[0x14];   // 18
		ActorHandle   actorHandle;   // 2C
		float         radius;        // 30
		std::uint32_t unk34;         // 34
		float         unk38;         // 38
		std::uint8_t  flag;          // 3C
		std::uint8_t  pad3D[3];      // 3D
	};
	static_assert(sizeof(AvoidedActorInfo) == 0x40);
}

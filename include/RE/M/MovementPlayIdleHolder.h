#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/M/MovementPlayIdleData.h"

namespace RE
{
	// ref-counted idle selection held by MovementAgentPathFollowerStandard
	struct MovementPlayIdleHolder
	{
	public:
		// members
		std::uint32_t        refCount;         // 00
		MovementPlayIdleData idleData;         // 04
		std::uint8_t         selection[0x58];  // 8C - contents not decoded
		BSFixedString        selectionName;    // E8
		std::uint8_t         flag;             // F0
		std::uint8_t         pad[7];           // F1
	};
	static_assert(sizeof(MovementPlayIdleHolder) == 0xF8);
}

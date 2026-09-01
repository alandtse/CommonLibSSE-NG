#pragma once

#include "RE/H/hkbGenerator.h"

namespace RE
{
	// source: activeragdoll; not independently Ghidra-verified (no consumer found).
	// Total size (0x50) is not directly asserted by activeragdoll but is forced by
	// hkbBlendingTransitionEffect's confirmed offsetof(fromGenerator)==0x60 combined
	// with its preceding field list.
	class hkbTransitionEffect : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbTransitionEffect;
		inline static constexpr auto VTABLE = VTABLE_hkbTransitionEffect;

		// members
		std::uint8_t selfTransitionMode;  // 48
		std::uint8_t eventMode;           // 49
		std::uint8_t defaultEventMode;    // 4A
		std::uint8_t unk4B[5];            // 4B - gap, content unconfirmed
	};
	static_assert(offsetof(hkbTransitionEffect, eventMode) == 0x49);
	static_assert(sizeof(hkbTransitionEffect) == 0x50);
}

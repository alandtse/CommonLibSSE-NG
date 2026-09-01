#pragma once

#include "RE/B/bhkConstraint.h"

namespace RE
{
	// source: activeragdoll; not independently Ghidra-verified (no consumer found)
	class bhkGroupConstraint : public bhkConstraint
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkGroupConstraint;
		inline static constexpr auto VTABLE = VTABLE_bhkGroupConstraint;

		// members
		std::uint32_t collisionGroup;  // 20
		std::uint32_t pad24;           // 24
	};
	static_assert(sizeof(bhkGroupConstraint) == 0x28);
}

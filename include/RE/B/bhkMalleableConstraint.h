#pragma once

#include "RE/B/bhkConstraint.h"

namespace RE
{
	// source: activeragdoll; not independently Ghidra-verified (no consumer found)
	class bhkMalleableConstraint : public bhkConstraint
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkMalleableConstraint;
		inline static constexpr auto VTABLE = VTABLE_bhkMalleableConstraint;
	};
	static_assert(sizeof(bhkMalleableConstraint) == 0x20);
}

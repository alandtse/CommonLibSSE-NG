#pragma once

#include "RE/B/bhkConstraint.h"

namespace RE
{
	// source: activeragdoll; not independently Ghidra-verified (no consumer found)
	class bhkRagdollConstraint : public bhkConstraint
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkRagdollConstraint;
		inline static constexpr auto VTABLE = VTABLE_bhkRagdollConstraint;
	};
	static_assert(sizeof(bhkRagdollConstraint) == 0x20);
}

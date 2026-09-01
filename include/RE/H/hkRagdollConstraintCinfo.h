#pragma once

#include "RE/H/hkConstraintCinfo.h"

namespace RE
{
	// source: activeragdoll; not independently Ghidra-verified (no consumer found)
	class hkRagdollConstraintCinfo : public hkConstraintCinfo
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkRagdollConstraintCinfo;
		inline static constexpr auto VTABLE = VTABLE_hkRagdollConstraintCinfo;

		hkRagdollConstraintCinfo();
	};
	static_assert(sizeof(hkRagdollConstraintCinfo) == 0x28);
}

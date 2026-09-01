#pragma once

#include "RE/H/hkConstraintCinfo.h"

namespace RE
{
	// source: activeragdoll; not independently Ghidra-verified (no consumer found)
	class hkMalleableConstraintCinfo : public hkConstraintCinfo
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkMalleableConstraintCinfo;
		inline static constexpr auto VTABLE = VTABLE_hkMalleableConstraintCinfo;

		hkMalleableConstraintCinfo();
	};
	static_assert(sizeof(hkMalleableConstraintCinfo) == 0x28);
}

#pragma once

#include "RE/H/hkConstraintCinfo.h"

namespace RE
{
	// source: activeragdoll; not independently Ghidra-verified (no consumer found)
	class hkFixedConstraintCinfo : public hkConstraintCinfo
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkFixedConstraintCinfo;
		inline static constexpr auto VTABLE = VTABLE_hkFixedConstraintCinfo;

		// members
		std::uint64_t unk28 = 0;  // 28
		std::uint8_t  unk30 = 0;  // 30 - type or something
	};
}

#pragma once

#include "RE/H/hkRefPtr.h"
#include "RE/N/NiRefObject.h"

namespace RE
{
	class hkpSimpleShapePhantom;

	// source: activeragdoll; not independently Ghidra-verified (no consumer found)
	class bhkSimpleShapePhantom : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkSimpleShapePhantom;
		inline static constexpr auto VTABLE = VTABLE_bhkSimpleShapePhantom;

		// members
		hkRefPtr<hkpSimpleShapePhantom> phantom;  // 10
	};
	static_assert(sizeof(bhkSimpleShapePhantom) == 0x18);
}

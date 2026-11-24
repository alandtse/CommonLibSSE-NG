#pragma once

#include "RE/T/TESPackage.h"

namespace RE
{
	class Actor;
	class TESObjectREFR;
	class TESPackage;

	// Knowledge visitor state used while a guard looks for the target of a guard-warn package.
	class GuardWarnSearch
	{
	public:
		// members
		TESObjectREFR* targetRef;      // 00
		Actor*         actor;          // 08
		TESPackage*    package;        // 10
		std::uint64_t  unk18;          // 18
		TESObjectREFR* centerRef;      // 20
		PackageTarget* packageTarget;  // 28
		bool           hasOwner;       // 30
		std::uint8_t   pad31[7];       // 31
		std::uint64_t  center;         // 38
		float          radius;         // 40
		float          radiusSq;       // 44
		float          centerDistSq;   // 48
		std::uint32_t  pad4C;          // 4C
	};
	static_assert(sizeof(GuardWarnSearch) == 0x50);
}

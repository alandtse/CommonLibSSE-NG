#pragma once

#include "RE/T/TESPackage.h"

namespace RE
{
	class Actor;
	class NiPoint3;
	class TESObjectREFR;

	// Functor with no vtable that a guard runs over its knowledge entries to find the target of a guard-warn package.
	class GuardWarnSearch
	{
	public:
		bool Visit(std::uint32_t a_handle, void** a_knowledge)
		{
			using func_t = bool(GuardWarnSearch*, std::uint32_t, void**);
			static REL::Relocation<func_t> func{ RELOCATION_ID(26620, 27293) };
			return func(this, a_handle, a_knowledge);
		}
		bool IsTargetRef(TESObjectREFR* a_ref)
		{
			using func_t = bool(GuardWarnSearch*, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(26621, 27294) };
			return func(this, a_ref);
		}

		// members
		TESObjectREFR* targetRef;      // 00
		Actor*         actor;          // 08
		TESPackage*    package;        // 10
		TESObjectREFR* foundRef;       // 18
		TESObjectREFR* centerRef;      // 20
		PackageTarget* packageTarget;  // 28
		bool           hasOwner;       // 30
		std::uint8_t   pad31[7];       // 31
		NiPoint3*      center;         // 38
		float          radius;         // 40
		float          radiusSq;       // 44
		float          centerDistSq;   // 48
		std::uint32_t  pad4C;          // 4C
	};
	static_assert(sizeof(GuardWarnSearch) == 0x50);
}

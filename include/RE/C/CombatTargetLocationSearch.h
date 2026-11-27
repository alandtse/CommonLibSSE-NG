#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSCoreTypes.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class Actor;
	class CombatTargetLocationSearchResult;

	class CombatTargetLocationSearch : public CombatObject
	{
	public:
		struct Candidate
		{
			std::uint32_t navKey;    // 00
			float         angle[4];  // 04
			NiPoint3      position;  // 14
		};
		static_assert(sizeof(Candidate) == 0x20);

		CombatTargetLocationSearch* Ctor(Actor* a_actor, Actor* a_target, float a_radius);

		// members
		CombatTargetLocationSearchResult* result;             // 10
		BSTArray<std::uint32_t>           candidateKeys;      // 18
		BSTArray<Candidate>               candidates;         // 30
		ActorHandle                       actor;              // 48
		ActorHandle                       target;             // 4C
		FormID                            targetFormID;       // 50
		NiPoint3                          searchOrigin;       // 54
		float                             radius;             // 60
		float                             actorRadius;        // 64
		std::uint32_t                     state;              // 68
		std::uint32_t                     selectedCandidate;  // 6C
		BSSpinLock                        lock;               // 70
	};
	static_assert(sizeof(CombatTargetLocationSearch) == 0x78);
}

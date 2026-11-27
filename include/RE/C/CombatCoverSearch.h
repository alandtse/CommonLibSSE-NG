#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/C/CombatAimController.h"
#include "RE/C/CombatCoverLocation.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatCoverSearchResult;

	class CombatCoverSearch : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatCoverSearch;
		inline static constexpr auto VTABLE = VTABLE_CombatCoverSearch;

		class Params
		{
		public:
			// members
			ActorHandle                    attackerHandle;          // 00
			std::uint32_t                  mode;                    // 04
			float                          attackerRadius;          // 08
			float                          attackerBoundSize;       // 0C
			std::uint8_t                   unk10;                   // 10
			std::uint8_t                   unk11;                   // 11
			std::byte                      pad12[0x2];              // 12
			float                          minDistance;             // 14
			float                          maxDistance;             // 18
			NiPoint3                       attackerPosition;        // 1C
			NiPoint3                       targetPosition;          // 28
			std::byte                      secondaryThreats[0x18];  // 38
			NiPointer<CombatAimController> aimController;           // 50
		};
		static_assert(sizeof(Params) == 0x58);

		~CombatCoverSearch() override;  // 00

		// members
		Params                   params;         // 10
		CombatCoverSearchResult* result;         // 68
		std::uint32_t            unk70;          // 70
		NiPoint3                 foundPosition;  // 74
		BSSpinLock               lock;           // 80
	};
	static_assert(sizeof(CombatCoverSearch) == 0x88);

	class CombatCoverSearchResult : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatCoverSearchResult;
		inline static constexpr auto VTABLE = VTABLE_CombatCoverSearchResult;

		~CombatCoverSearchResult() override;  // 00

		// members
		CombatCoverSearch*             coverSearch;  // 10
		NiPointer<CombatCoverLocation> location;     // 18
	};
	static_assert(sizeof(CombatCoverSearchResult) == 0x20);
}

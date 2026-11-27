#pragma once

#include "RE/C/CombatAimController.h"
#include "RE/C/CombatArea.h"
#include "RE/C/CombatFlankingSearchData.h"
#include "RE/C/CombatTargetLocationSearch.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BGSLoadGameBuffer;
	class BGSSaveGameBuffer;
	class CombatCoverSearch;

	class CombatPathingSphere
	{
	public:
		// members
		NiPoint3 center;  // 00
		float    radius;  // 0C
	};
	static_assert(sizeof(CombatPathingSphere) == 0x10);

	class CombatPathingGoalPolicyStandard
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingGoalPolicyStandard;

		// members
		NiPoint3  goalLocation;  // 00
		std::byte pad0C[0x14];   // 0C
	};
	static_assert(sizeof(CombatPathingGoalPolicyStandard) == 0x20);

	class CombatPathingGoalPolicyFindTargetLocation
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingGoalPolicyFindTargetLocation;

		void SaveGame(BGSSaveGameBuffer* a_buf);
		void LoadGame(BGSLoadGameBuffer* a_buf);

		// members
		void*                                 navmesh;               // 00
		std::uint16_t                         triangle;              // 08
		std::byte                             pad0A[0x6];            // 0A
		NiPoint3                              goalLocation;          // 10
		std::byte                             pad1C[0x4];            // 1C
		NiPointer<CombatTargetLocationSearch> targetLocationSearch;  // 20
		void*                                 search;                // 28
	};
	static_assert(sizeof(CombatPathingGoalPolicyFindTargetLocation) == 0x30);

	class CombatPathingGoalPolicyFlank : public CombatPathingGoalPolicyFindTargetLocation
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingGoalPolicyFlank;

		void SaveGame(BGSSaveGameBuffer* a_buf);
		void LoadGame(BGSLoadGameBuffer* a_buf);

		// members
		NiPointer<CombatFlankingSearchData> flankingSearchData;  // 30
	};
	static_assert(sizeof(CombatPathingGoalPolicyFlank) == 0x38);

	class CombatPathingGoalPolicyFlankDistant
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingGoalPolicyFlankDistant;

		// members
		NiPoint3  referencePosition;  // 00
		NiPoint3  center;             // 0C
		float     radius;             // 18
		std::byte pad1C[0x4];         // 1C
	};
	static_assert(sizeof(CombatPathingGoalPolicyFlankDistant) == 0x20);

	class CombatPathingGoalPolicyRetreat
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingGoalPolicyRetreat;

		void SaveGame(BGSSaveGameBuffer* a_buf);
		void LoadGame(BGSLoadGameBuffer* a_buf);

		// members
		CombatPathingSphere sphere;  // 00
	};
	static_assert(sizeof(CombatPathingGoalPolicyRetreat) == 0x10);

	class CombatPathingGoalPolicyFlee
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingGoalPolicyFlee;

		// members
		CombatPathingSphere sphere;  // 00
		void*               search;  // 10
	};
	static_assert(sizeof(CombatPathingGoalPolicyFlee) == 0x18);

	class CombatPathingGoalPolicyReturnToCombatArea
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingGoalPolicyReturnToCombatArea;

		void SaveGame(BGSSaveGameBuffer* a_buf);
		void LoadGame(BGSLoadGameBuffer* a_buf);

		// members
		void*                 navmesh;         // 00
		std::uint16_t         triangle;        // 08
		std::byte             pad0A[0x6];      // 0A
		NiPoint3              position;        // 10
		std::byte             pad1C[0x4];      // 1C
		NiPointer<CombatArea> combatArea;      // 20
		NiPoint3              resultPosition;  // 28
		std::byte             pad34[0x4];      // 34
	};
	static_assert(sizeof(CombatPathingGoalPolicyReturnToCombatArea) == 0x38);

	class CombatPathingGoalPolicySearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingGoalPolicySearch;

		// members
		std::uint32_t state;                      // 00
		std::byte     pad04[0x4];                 // 04
		void*         actor;                      // 08
		void*         ignoredLocations_data;      // 10
		std::uint32_t ignoredLocations_capacity;  // 18
		std::byte     pad1C[0x4];                 // 1C
		std::uint32_t ignoredLocations_size;      // 20
		std::byte     pad24[0x4];                 // 24
		NiPoint3      searchOrigin;               // 28
		void*         areaMap;                    // 38
	};
	static_assert(sizeof(CombatPathingGoalPolicySearch) == 0x40);

	class CombatPathingGoalPolicySearchWander
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingGoalPolicySearchWander;

		// members
		std::uint32_t state;          // 00
		std::byte     pad04[0x4];     // 04
		void*         actor;          // 08
		NiPoint3      wanderOrigin;   // 10
		void*         areaMap;        // 20
		void*         searchContext;  // 28
	};
	static_assert(sizeof(CombatPathingGoalPolicySearchWander) == 0x30);

	class CombatPathingGoalPolicyExitWater
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingGoalPolicyExitWater;

		// members
		void*    search;    // 00
		NiPoint3 location;  // 08
	};
	static_assert(sizeof(CombatPathingGoalPolicyExitWater) == 0x18);

	class CombatPathingGoalPolicyFindAttackLocation
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingGoalPolicyFindAttackLocation;

		void SaveGame(BGSSaveGameBuffer* a_buf);

		// members
		NiPointer<CombatAimController> aimController;      // 00
		NiPoint3                       center;             // 08
		float                          radius;             // 14
		std::byte                      pad18[0xC];         // 18
		std::uint32_t                  cellCacheCapacity;  // 24
		std::byte                      pad28[0x8];         // 28
		void*                          cellCacheSentinel;  // 30
		std::byte                      pad38[0x8];         // 38
		void*                          cellCacheBuckets;   // 40
	};
	static_assert(sizeof(CombatPathingGoalPolicyFindAttackLocation) == 0x48);

	class CombatPathingGoalPolicyFindCover
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingGoalPolicyFindCover;

		// members
		CombatCoverSearch* coverSearch;  // 00
	};
	static_assert(sizeof(CombatPathingGoalPolicyFindCover) == 0x8);

	class CombatPathingGoalPolicyFindHideCover
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingGoalPolicyFindHideCover;

		// members
		std::byte unk00[0x8];  // 00
	};
	static_assert(sizeof(CombatPathingGoalPolicyFindHideCover) == 0x8);

	class CombatPathingGoalPolicyLocation
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathingGoalPolicyLocation;

		// members
		void*         navmesh;      // 00
		std::uint16_t triangle;     // 08
		std::byte     pad0A[0x16];  // 0A
	};
	static_assert(sizeof(CombatPathingGoalPolicyLocation) == 0x20);
}

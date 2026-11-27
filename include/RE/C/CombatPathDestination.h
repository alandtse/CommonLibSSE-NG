#pragma once

#include "RE/A/AITimer.h"
#include "RE/B/BGSWorldLocation.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"

namespace RE
{
	class CombatPathDestination
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathDestination;
	};

	class CombatPathDestinationLocation : public CombatPathDestination
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathDestinationLocation;

		// members
		BGSWorldLocation location;    // 00
		float            goalRadius;  // 18
	};
	static_assert(sizeof(CombatPathDestinationLocation) == 0x20);

	class CombatPathDestinationLocations : public CombatPathDestination
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathDestinationLocations;

		// members
		BSTArray<CombatPathDestinationLocation> locations;  // 00
	};
	static_assert(sizeof(CombatPathDestinationLocations) == 0x18);

	class CombatPathDestinationRef : public CombatPathDestination
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathDestinationRef;

		// members
		ObjectRefHandle  target;       // 00
		std::uint32_t    pad04;        // 04
		BGSWorldLocation location;     // 08
		float            goalRadius;   // 20
		AITimer          updateTimer;  // 24
		std::uint32_t    pad2C;        // 2C
	};
	static_assert(sizeof(CombatPathDestinationRef) == 0x30);

	class CombatPathDestinationRefs : public CombatPathDestinationRef
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathDestinationRefs;

		class Entry
		{
		public:
			// members
			ObjectRefHandle target;      // 00
			float           goalRadius;  // 04
		};
		static_assert(sizeof(Entry) == 0x8);

		// members
		BSTArray<Entry> targets;  // 30
	};
	static_assert(sizeof(CombatPathDestinationRefs) == 0x48);

	class CombatPathDestinationNone : public CombatPathDestination
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathDestinationNone;
	};
}

#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/M/MovementControllerAI.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	// secondary bases (not declared in CLib): IMovementPathManagerAgent
	class MovementPathManagerAgentAvoidBox : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPathManagerAgentAvoidBox;
		inline static constexpr auto VTABLE = VTABLE_MovementPathManagerAgentAvoidBox;

		// members
		void*             vptr_IMovementPathManagerAgent;  // 18
		std::uint32_t     ownerHandle;                     // 20 - ActorState vtable slot 1 result, set by Activate
		std::uint8_t      unk24[4];                        // 24
		void*             registerInterface;               // 28
		std::uint32_t     state;                           // 30 - saved/loaded; LoadGame resets 1 -> 0
		std::uint32_t     normalizedSpeed;                 // 34 - saved/loaded
		BSPathingLocation blockedLocation;                 // 38 - saved/loaded; copied to the out struct when EvaluateAvoidBox returns 4
		NiPoint3          lastPosition;                    // 68 - ctor FLT_MAX
		std::uint8_t      unk74[4];                        // 74
		std::int32_t      requestId;                       // 78 - ctor -1
		std::uint8_t      unk7C[4];                        // 7C
		void*             unk80;                           // 80
		std::uint8_t      unk88[8];                        // 88
		BSReadWriteLock   lock;                            // 90 - BSReadWriteLock taken by CheckBlockedByAvoidBox
		void*             unk98;                           // 98 - ref-counted saveable object, saved/loaded; released by Activate
		void*             unkA0;                           // A0 - saveable object, saved
		std::uint32_t     unkA8;                           // A8 - saved/loaded
		std::uint8_t      unkAC[4];                        // AC
	};
	static_assert(sizeof(MovementPathManagerAgentAvoidBox) == 0xB0);
}

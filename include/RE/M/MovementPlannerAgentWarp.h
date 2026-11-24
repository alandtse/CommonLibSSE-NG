#pragma once

#include "RE/B/BSPathingLocation.h"
#include "RE/I/IMovementPlannerAgent.h"
#include "RE/I/IMovementSetWarp.h"
#include "RE/M/MovementControllerAI.h"
#include "RE/P/PathingSolutionQueue.h"

namespace RE
{
	class Character;

	class MovementPlannerAgentWarp :
		public MovementAgent,          // 00
		public IMovementPlannerAgent,  // 18
		public IMovementSetWarp        // 20
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPlannerAgentWarp;
		inline static constexpr auto VTABLE = VTABLE_MovementPlannerAgentWarp;

		~MovementPlannerAgentWarp() override;  // 00

		// members
		BSPathingLocation     savedLocation;   // 28
		BSPathingLocation     warpLocation;    // 58
		float                 warpTimer;       // 88
		std::uint32_t         pad8C;           // 8C
		Character*            character;       // 90
		PathingSolutionQueue* solutionQueueA;  // 98
		PathingSolutionQueue* solutionQueueB;  // A0
		void*                 controller;      // A8
		std::uint32_t         warpState;       // B0 - 0 to 3
		std::uint32_t         unkB4;           // B4
		std::uint8_t          lock[0x8];       // B8 - Mutex
	};
	static_assert(sizeof(MovementPlannerAgentWarp) == 0xC0);
}

#pragma once

#include "RE/I/IMovementPlannerAgent.h"
#include "RE/I/IMovementQueryState.h"
#include "RE/I/IMovementSetState.h"
#include "RE/M/MovementControllerAI.h"

namespace RE
{
	class MovementAgentActorState :
		public MovementAgent,          // 00
		public IMovementPlannerAgent,  // 18
		public IMovementSetState,      // 20
		public IMovementQueryState     // 28
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementAgentActorState;
		inline static constexpr auto VTABLE = VTABLE_MovementAgentActorState;

		~MovementAgentActorState() override;  // 00

		// members
		std::uint32_t plannedStateType;    // 30
		std::uint8_t  unk34[0x10];         // 34
		float         turnAngleThreshold;  // 44
		std::uint8_t  unk48[0x8];          // 48
		void*         controller;          // 50
		std::uint32_t turnState;           // 58 - 0 or 1, hysteresis
		std::uint32_t pad5C;               // 5C
		void*         movementParameters;  // 60
		std::uint8_t  lock[0x8];           // 68 - MutexRW
		std::uint32_t strafeFlag;          // 70
		std::uint32_t pad74;               // 74
	};
	static_assert(sizeof(MovementAgentActorState) == 0x78);
}

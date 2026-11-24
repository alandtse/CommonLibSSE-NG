#pragma once

#include "RE/I/IMovementPlannerAgent.h"
#include "RE/I/IMovementQueryState.h"
#include "RE/I/IMovementSetState.h"
#include "RE/M/MovementControllerAI.h"
#include "RE/N/NiPoint3.h"

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
		std::uint32_t plannedStateType;    // 30 - MovementPlannedState: nonzero when set
		NiPoint3      plannedPosition;     // 34
		float         plannedField10;      // 40
		float         angleThreshold;      // 44 - |heading error| that clears turnState
		std::uint32_t unk48;               // 48
		std::uint32_t pad4C;               // 4C
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

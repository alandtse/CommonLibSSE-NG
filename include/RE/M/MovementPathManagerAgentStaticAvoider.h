#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	struct BSPathingSolution;

	// secondary bases (not declared in CLib): IMovementPathManagerAgent, IMovementQueryStaticAvoider, IMovementSetStaticAvoider
	class MovementPathManagerAgentStaticAvoider : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPathManagerAgentStaticAvoider;
		inline static constexpr auto VTABLE = VTABLE_MovementPathManagerAgentStaticAvoider;

		// members
		void*              vptr_IMovementPathManagerAgent;    // 18
		void*              vptr_IMovementQueryStaticAvoider;  // 20
		void*              vptr_IMovementSetStaticAvoider;    // 28
		std::uint32_t      ownerHandle;                       // 30 - Activate stores result of owner-handle slot call
		std::uint8_t       unk34[4];                          // 34
		void*              messageInterface;                  // 38 - interface pointer; dtor calls vtable slot 4 on it then nulls it
		std::uint8_t       errorFrames[16];                   // 40 - BSTArray of movement error frames
		std::uint8_t       unk50[32];                         // 50
		std::uint32_t      avoidNodesCapacity;                // 70
		std::uint8_t       unk74[4];                          // 74
		std::uint8_t       avoidNodesStorage[40];             // 78 - inline storage of the small array: 1 element of 0x24 bytes (+4 pad)
		std::uint32_t      avoidNodeCount;                    // A0 - BSTSmallArray size; ModifyPathingRequest zeroes it after copying to the request
		std::uint8_t       unkA4[4];                          // A4
		BSPathingSolution* solution;                          // A8 - SetPathingData stores a_solution; ResetPathingState releases and nulls
		float              totalDisplacementThreshold;        // B0 - float, running minimum set in SetPathingData, compared in PollPathEvent; serialized
		float              totalTimeThreshold;                // B4
		std::uint32_t      pathFailureSuppressed;             // B8 - serialized; SetTriggerPathFailure(bool) stores (a_trigger == 0)
		std::uint8_t       unkBC[4];                          // BC
	};
	static_assert(sizeof(MovementPathManagerAgentStaticAvoider) == 0xC0);
}

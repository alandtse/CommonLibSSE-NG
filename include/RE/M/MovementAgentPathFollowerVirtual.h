#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/M/MovementControllerAI.h"

namespace RE
{
	class BSPathingRequest;
	struct BSPathingSolution;

	// secondary bases (not declared in CLib): IMovementPlannerAgent, IMovementPathManagerAgent, IMovementQueryPathFollowing, IMovementSetPathFollowing
	class MovementAgentPathFollowerVirtual : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementAgentPathFollowerVirtual;
		inline static constexpr auto VTABLE = VTABLE_MovementAgentPathFollowerVirtual;

		// members
		void*              vptr_IMovementPlannerAgent;        // 18
		void*              vptr_IMovementPathManagerAgent;    // 20
		void*              vptr_IMovementQueryPathFollowing;  // 28
		void*              vptr_IMovementSetPathFollowing;    // 30
		BSReadWriteLock    lock;                              // 38 - ctor BSReadWriteLock(this+0x38)
		std::uint32_t      state;                             // 40 - serialized; sub_141115090 sets 3
		std::uint8_t       unk44[4];                          // 44
		BSPathingRequest*  request;                           // 48 - SaveGame/LoadGame stream slot 0x60/0x68; flags at request+0xD0
		BSPathingSolution* solution;                          // 50 - LoadGame stream slot 0x70 then BSPathingSolution::IsNodeChainValid
		void*              messageInterface;                  // 58 - dtor calls vtable slot 4 on it then nulls it; same role as PathFollowerStandard.messageInterface
	};
	static_assert(sizeof(MovementAgentPathFollowerVirtual) == 0x60);
}

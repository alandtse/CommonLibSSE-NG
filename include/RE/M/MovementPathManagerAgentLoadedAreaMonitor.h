#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	struct BSPathingSolution;

	// secondary bases (not declared in CLib): IMovementPathManagerAgent
	class MovementPathManagerAgentLoadedAreaMonitor : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPathManagerAgentLoadedAreaMonitor;
		inline static constexpr auto VTABLE = VTABLE_MovementPathManagerAgentLoadedAreaMonitor;

		// members
		void*              vptr_IMovementPathManagerAgent;  // 18
		std::uint32_t      ownerHandle;                     // 20 - Activate stores result of owner-handle slot call
		std::uint8_t       unk24[4];                        // 24
		BSPathingSolution* solution;                        // 28 - intrusive-refcounted (dtor decrements *ptr); SaveGame/LoadGame WriteSolution/ReadSolution(this+0x28)
	};
	static_assert(sizeof(MovementPathManagerAgentLoadedAreaMonitor) == 0x30);
}

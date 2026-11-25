#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	struct BSPathingSolution;

	// secondary bases (not declared in CLib): IMovementPlannerAgent, IMovementPathManagerAgent
	class MovementPlannerAgentNavmeshBounds : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPlannerAgentNavmeshBounds;
		inline static constexpr auto VTABLE = VTABLE_MovementPlannerAgentNavmeshBounds;

		// members
		void*              vptr_IMovementPlannerAgent;      // 18
		void*              vptr_IMovementPathManagerAgent;  // 20
		std::uint32_t      ownerHandle;                     // 28 - Activate stores result of owner-handle slot call
		std::uint8_t       unk2C[4];                        // 2C
		void*              unk30;                           // 30 - released and zeroed in dtor
		std::uint8_t       unk38[8];                        // 38
		std::uint32_t      unk40;                           // 40 - serialized first; LoadGame sets -1 when read value is 0
		float              unk44;                           // 44 - serialized
		float              unk48;                           // 48 - serialized
		std::uint8_t       unk4C[4];                        // 4C
		void*              unk50;                           // 50 - intrusive-refcounted object holding a BSPathingLocation (dtor decrements, BSPathingLocation::dtor)
		std::uint32_t      obstacleArrayCapacity;           // 58 - BSTSmallArray allocator word; whole-array dtor FUN_1410fe750 (elements 0xA8 bytes, size at +0x2A8 from 0x58)
		std::uint8_t       unk5C[4];                        // 5C
		std::uint8_t       obstacleStorage[672];            // 60 - inline storage: 4 elements of 0xA8 bytes
		std::uint32_t      obstacleCount;                   // 300 - BSTSmallArray size
		std::uint8_t       unk304[4];                       // 304
		BSPathingSolution* solution;                        // 308 - intrusive-refcounted; SaveGame/LoadGame stream slot 0x68/0x70; dtor BSPathingSolution::dtor
		float              unk310;                          // 310 - LoadGame stores 0x40000000 (2.0f) here after reading the solution
		std::uint8_t       unk314[4];                       // 314
	};
	static_assert(sizeof(MovementPlannerAgentNavmeshBounds) == 0x318);
}

#pragma once

#include "RE/I/IMovementPlannerAgent.h"
#include "RE/I/IMovementSetWarp.h"
#include "RE/M/MovementControllerAI.h"
#include "RE/N/NiPoint3.h"

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
		std::uint8_t  unk28[0x30];   // 28
		NiPoint3      warpPosition;  // 58
		std::uint8_t  unk64[0x24];   // 64
		float         warpTimer;     // 88
		std::uint32_t pad8C;         // 8C
		Character*    character;     // 90
		std::uint8_t  unk98[0x10];   // 98
		void*         controller;    // A8
		std::uint32_t warpState;     // B0 - 0 to 3
		std::uint32_t padB4;         // B4
		std::uint8_t  lock[0x8];     // B8 - Mutex
	};
	static_assert(sizeof(MovementPlannerAgentWarp) == 0xC0);
}

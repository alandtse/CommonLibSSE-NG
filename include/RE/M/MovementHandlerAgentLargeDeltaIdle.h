#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	class IMovementControllerRegisterInterface;

	// secondary bases (not declared in CLib): IMovementHandlerAgent
	class MovementHandlerAgentLargeDeltaIdle : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgentLargeDeltaIdle;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerAgentLargeDeltaIdle;

		// members
		void*                                 vptr_IMovementHandlerAgent;  // 18
		IMovementControllerRegisterInterface* registerInterface;           // 20
		std::uint32_t                         state;                       // 28 - 0/1; Activate clears when 1, UpdateHandler sets 1, SaveGame/LoadGame serialize
		std::uint8_t                          unk2C[4];                    // 2C
	};
	static_assert(sizeof(MovementHandlerAgentLargeDeltaIdle) == 0x30);
}

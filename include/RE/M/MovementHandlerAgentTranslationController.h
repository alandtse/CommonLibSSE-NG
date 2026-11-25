#pragma once

#include "RE/M/MovementControllerAI.h"

namespace RE
{
	// secondary bases (not declared in CLib): IMovementHandlerAgent, IMovementSetTranslationControllerType
	class MovementHandlerAgentTranslationController : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgentTranslationController;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerAgentTranslationController;

		// members
		void*         vptr_IMovementHandlerAgent;                  // 18
		void*         vptr_IMovementSetTranslationControllerType;  // 20
		std::uint8_t  unk28;                                       // 28 - bool, serialized first in SaveGame
		std::uint8_t  unk29[7];                                    // 29
		void*         unk30;                                       // 30 - zeroed by ctor
		std::uint32_t controllerType;                              // 38 - 0..2, switch in UpdateHandler (1 = strafe-aware); serialized; set via IMovementSetTranslationControllerType
		std::uint8_t  unk3C[4];                                    // 3C
	};
	static_assert(sizeof(MovementHandlerAgentTranslationController) == 0x40);
}

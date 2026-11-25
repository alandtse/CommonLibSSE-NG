#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/M/MovementControllerAI.h"

namespace RE
{
	class IMovementControllerRegisterInterface;

	// secondary bases (not declared in CLib): IMovementHandlerAgent, IMovementSetPlayerControls
	class MovementHandlerAgentPlayerControls : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgentPlayerControls;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerAgentPlayerControls;

		// members
		void*                                 vptr_IMovementHandlerAgent;       // 18
		void*                                 vptr_IMovementSetPlayerControls;  // 20
		IMovementControllerRegisterInterface* registerInterface;                // 28
		BSReadWriteLock                       lock;                             // 30 - ctor BSReadWriteLock(this+0x30)
		std::uint32_t                         controlMode;                      // 38 - 0 or 1; written by IMovementSetPlayerControls slot 2, serialized by SaveGame/LoadGame
		std::uint8_t                          unk3C[4];                         // 3C
		void*                                 buffer;                           // 40 - NiMemFree d in dtor
		float                                 dampenTime;                       // 48 - ctor init = fControllerDampenTime:Controls; serialized
		std::uint8_t                          freezeDirectionOnLargeDelta;      // 4C - ctor init = bFreezeDirectionOnLargeDelta:Controls; serialized
		std::uint8_t                          unk4D[3];                         // 4D
	};
	static_assert(sizeof(MovementHandlerAgentPlayerControls) == 0x50);
}

#pragma once

#include "RE/I/IMovementState.h"
#include "RE/M/MovementControllerAI.h"

namespace RE
{
	// Forwards IMovementState queries to the wrapped movementState through a frame matrix.
	class MovementStateTweener :
		public MovementAgent,  // 00
		public IMovementState  // 18
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementStateTweener;
		inline static constexpr auto VTABLE = VTABLE_MovementStateTweener;

		~MovementStateTweener() override;  // 00

		// members
		void* frameSource;  // 20
	};
	static_assert(sizeof(MovementStateTweener) == 0x28);
}

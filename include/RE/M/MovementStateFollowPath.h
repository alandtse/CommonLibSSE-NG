#pragma once

#include "RE/I/IMovementState.h"
#include "RE/M/MovementControllerAI.h"

namespace RE
{
	// Forwards IMovementState queries to the wrapped movementState through a frame matrix.
	class MovementStateFollowPath :
		public MovementAgent,  // 00
		public IMovementState  // 18
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementStateFollowPath;
		inline static constexpr auto VTABLE = VTABLE_MovementStateFollowPath;

		~MovementStateFollowPath() override;  // 00

		// members
		void* frameSource;  // 20
	};
	static_assert(sizeof(MovementStateFollowPath) == 0x28);
}

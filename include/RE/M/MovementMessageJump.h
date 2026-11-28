#pragma once

#include "RE/I/IPathFollowerAction.h"
#include "RE/M/MovementMessage.h"

namespace RE
{
	class MovementMessageJump :
		public MovementMessage,     // 00
		public IPathFollowerAction  // 10
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageJump;
		inline static constexpr auto VTABLE = VTABLE_MovementMessageJump;

		~MovementMessageJump() override;  // 00

		// members
		float jumpParam;  // 18
	};
	static_assert(sizeof(MovementMessageJump) == 0x20);
}

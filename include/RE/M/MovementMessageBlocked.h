#pragma once

#include "RE/M/MovementMessage.h"

namespace RE
{
	struct MovementMessageBlocked : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageBlocked;
		inline static constexpr auto VTABLE = VTABLE_MovementMessageBlocked;

		~MovementMessageBlocked() override;  // 00
	};
	static_assert(sizeof(MovementMessageBlocked) == 0x10);
}

#pragma once

#include "RE/M/MovementMessagePathEvent.h"

namespace RE
{
	class MovementMessageNewPath : public MovementMessagePathEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageNewPath;
		inline static constexpr auto VTABLE = VTABLE_MovementMessageNewPath;

		~MovementMessageNewPath() override;  // 00
	};
	static_assert(sizeof(MovementMessageNewPath) == 0x18);
}

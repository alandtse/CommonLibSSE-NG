#pragma once

#include "RE/M/MovementMessagePathEvent.h"

namespace RE
{
	struct BSPathingSolution;

	class MovementMessagePathFailed : public MovementMessagePathEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessagePathFailed;
		inline static constexpr auto VTABLE = VTABLE_MovementMessagePathFailed;

		~MovementMessagePathFailed() override;  // 00

		// members
		BSPathingSolution* solution;  // 18 - NiPointer
	};
	static_assert(sizeof(MovementMessagePathFailed) == 0x20);
}

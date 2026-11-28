#pragma once

#include "RE/M/MovementMessagePathEvent.h"

namespace RE
{
	struct BSPathingSolution;

	class MovementMessagePathComplete : public MovementMessagePathEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessagePathComplete;
		inline static constexpr auto VTABLE = VTABLE_MovementMessagePathComplete;

		~MovementMessagePathComplete() override;  // 00

		// members
		BSPathingSolution* solution;  // 18 - NiPointer
	};
	static_assert(sizeof(MovementMessagePathComplete) == 0x20);
}

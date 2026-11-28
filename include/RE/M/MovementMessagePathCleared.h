#pragma once

#include "RE/M/MovementMessagePathEvent.h"

namespace RE
{
	struct BSPathingSolution;

	class MovementMessagePathCleared : public MovementMessagePathEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessagePathCleared;
		inline static constexpr auto VTABLE = VTABLE_MovementMessagePathCleared;

		~MovementMessagePathCleared() override;  // 00

		// members
		BSPathingSolution* solution;  // 18 - NiPointer
	};
	static_assert(sizeof(MovementMessagePathCleared) == 0x20);
}

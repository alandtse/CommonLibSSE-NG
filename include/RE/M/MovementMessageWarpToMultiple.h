#pragma once

#include "RE/B/BSTArray.h"
#include "RE/M/MovementMessageWarpToLocation.h"

namespace RE
{
	class MovementMessageWarpToMultiple : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageWarpToMultiple;
		inline static constexpr auto VTABLE = VTABLE_MovementMessageWarpToMultiple;

		~MovementMessageWarpToMultiple() override;  // 00

		// members
		BSTArray<MovementMessageWarpToLocation> locations;  // 10
	};
	static_assert(sizeof(MovementMessageWarpToMultiple) == 0x28);
}

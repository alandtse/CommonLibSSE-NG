#pragma once

#include "RE/M/MovementMessageDoor.h"

namespace RE
{
	class MovementMessageApproachingDoor : public MovementMessageDoor
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageApproachingDoor;
		inline static constexpr auto VTABLE = VTABLE_MovementMessageApproachingDoor;

		~MovementMessageApproachingDoor() override;  // 00
	};
	static_assert(sizeof(MovementMessageApproachingDoor) == 0x18);
}

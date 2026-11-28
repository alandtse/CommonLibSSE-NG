#pragma once

#include "RE/I/IPathFollowerAction.h"
#include "RE/M/MovementMessageDoor.h"

namespace RE
{
	class MovementMessageActivateDoor :
		public MovementMessageDoor,  // 00
		public IPathFollowerAction   // 18
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageActivateDoor;
		inline static constexpr auto VTABLE = VTABLE_MovementMessageActivateDoor;

		~MovementMessageActivateDoor() override;  // 00
	};
	static_assert(sizeof(MovementMessageActivateDoor) == 0x20);
}

#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/M/MovementMessage.h"

namespace RE
{
	class BSPathingDoor;

	class MovementMessageDoor : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageDoor;
		inline static constexpr auto VTABLE = VTABLE_MovementMessageDoor;

		~MovementMessageDoor() override;                          // 00
		void SaveGame(PathingStreamSaveGame* a_stream) override;  // 02

		// members
		BSTSmartPointer<BSPathingDoor> door;  // 10
	};
	static_assert(sizeof(MovementMessageDoor) == 0x18);
}

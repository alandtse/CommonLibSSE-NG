#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/M/MovementMessage.h"

namespace RE
{
	class BSPathingRequest;

	class MovementMessagePathEvent : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessagePathEvent;
		inline static constexpr auto VTABLE = VTABLE_MovementMessagePathEvent;

		~MovementMessagePathEvent() override;  // 00

		// members
		BSPathingRequest* request;  // 10 - NiPointer
	};
	static_assert(sizeof(MovementMessagePathEvent) == 0x18);
}

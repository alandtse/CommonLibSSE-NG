#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/M/MovementMessage.h"
#include "RE/M/MovementPlayIdleData.h"

namespace RE
{
	struct IMovementPlayIdleResult;

	class MovementMessagePlayIdle : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessagePlayIdle;
		inline static constexpr auto VTABLE = VTABLE_MovementMessagePlayIdle;

		~MovementMessagePlayIdle() override;  // 00

		// members
		BSFixedString            idleName;  // 10
		MovementPlayIdleData     idleData;  // 18
		IMovementPlayIdleResult* result;    // A0 - NiPointer
	};
	static_assert(sizeof(MovementMessagePlayIdle) == 0xA8);
}

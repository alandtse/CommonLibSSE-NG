#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/M/MovementMessage.h"

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
		BSFixedString            idleName;        // 10
		std::uint8_t             idleData[0x88];  // 18
		IMovementPlayIdleResult* result;          // A0 - NiPointer
	};
	static_assert(sizeof(MovementMessagePlayIdle) == 0xA8);
}

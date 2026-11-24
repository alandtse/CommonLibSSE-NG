#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementSetState : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementSetState;
		inline static constexpr auto VTABLE = VTABLE_IMovementSetState;

		~IMovementSetState() override;  // 00

		// add
		virtual void SetState(void* a_state) = 0;         // 01
		virtual void SetStateForward(void* a_state) = 0;  // 02
	};
	static_assert(sizeof(IMovementSetState) == 0x8);
}

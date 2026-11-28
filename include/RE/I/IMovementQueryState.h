#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementQueryState : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementQueryState;
		inline static constexpr auto VTABLE = VTABLE_IMovementQueryState;

		~IMovementQueryState() override;  // 00

		// add
		virtual void Unk_01(void) = 0;  // 01
		virtual void Unk_02(void) = 0;  // 02
	};
	static_assert(sizeof(IMovementQueryState) == 0x8);
}

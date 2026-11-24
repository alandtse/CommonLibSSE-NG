#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementSetWarp : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementSetWarp;
		inline static constexpr auto VTABLE = VTABLE_IMovementSetWarp;

		~IMovementSetWarp() override;  // 00

		// add
		virtual void HandlePathingFailure(void* a_request, void* a_p2) = 0;  // 01
		virtual void AdvanceWarpState(void* a_request) = 0;                  // 02
		virtual void ResetWarpState(void* a_request) = 0;                    // 03
	};
	static_assert(sizeof(IMovementSetWarp) == 0x8);
}

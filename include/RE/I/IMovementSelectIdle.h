#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementSelectIdle : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementSelectIdle;
		inline static constexpr auto VTABLE = VTABLE_IMovementSelectIdle;

		~IMovementSelectIdle() override;  // 00

		// add
		virtual void Unk_01(void) = 0;                                                    // 01
		virtual void Unk_02(void) = 0;                                                    // 02
		virtual void QueuePlayIdle(void* a_idleName, void* a_idleData, void* a_arg) = 0;  // 03 - allocates a MovementMessagePlayIdle into pendingPlayIdle
		virtual void ReleaseIdle(void) = 0;                                               // 04
		virtual bool HasActiveIdleRequest() = 0;                                          // 05 - true while an idle load request is outstanding
	};
	static_assert(sizeof(IMovementSelectIdle) == 0x8);
}

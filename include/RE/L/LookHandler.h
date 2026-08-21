#pragma once

#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	struct LookHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_LookHandler;
		inline static constexpr auto VTABLE = VTABLE_LookHandler;

		~LookHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifndef SKYRIM_CROSS_VR
		void ProcessThumbstick(ThumbstickEvent* a_event, PlayerControlsData* a_data) override;  // 02
		void ProcessMouseMove(MouseMoveEvent* a_event, PlayerControlsData* a_data) override;    // 03
#endif

		// AE 1.7.99 gives LookHandler a real (non-stub) ProcessSixaxis override --
		// verified via live decompile: reads a SixaxisEvent orientation quaternion
		// and calls Actor::ModifyRotationZ for gyro-based look. It also reads its
		// own instance fields well past this struct's current declared size (up to
		// +0xb4), meaning the real AE 1.7.99 object is larger than 0x10 -- matching
		// PR #233's claimed 0x10->0xB8 growth. Field-level layout not yet
		// independently RE'd; PlayerInputHandler::ProcessSixaxis's RelocateVirtual
		// dispatch reaches this override correctly regardless (no C++-level
		// override needed here for that), so this is a follow-up, not a blocker.
	};
	STATIC_ASSERT_SIZE(LookHandler, 0x10, 0x10, 0x28, 0x10);
}

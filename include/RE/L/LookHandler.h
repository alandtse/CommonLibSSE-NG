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

		// AE 1.7.99's LookHandler has a real gyro-based ProcessSixaxis override and
		// grows past 0x10 (real fields up to +0xB4); field layout not yet RE'd.
		// PlayerInputHandler::ProcessSixaxis still dispatches correctly without a
		// declared override here. Follow-up.
	};
	STATIC_ASSERT_SIZE(LookHandler, 0x10, 0x10, 0x28, 0x10);
}

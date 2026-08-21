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

		// AE 1.7.99 gives this a real gyro ProcessSixaxis override and grows it
		// past 0x10; field layout not yet RE'd (dispatch works without one here).
	};
	STATIC_ASSERT_SIZE(LookHandler, 0x10, 0x10, 0x28, 0x10);
}

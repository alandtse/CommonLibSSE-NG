#pragma once

#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	struct AutoMoveHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_AutoMoveHandler;
		inline static constexpr auto VTABLE = VTABLE_AutoMoveHandler;

		~AutoMoveHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;                                  // 01
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 04
	};
	STATIC_ASSERT_SIZE(AutoMoveHandler, 0x10, 0x10, 0x28, 0x10);
}

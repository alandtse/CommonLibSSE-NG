#pragma once

#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	// menuDepth = 13
	// flags = kAllowSaving | kCustomRendering
	// context = kNone
	class CursorMenu :
#ifndef SKYRIM_CROSS_VR
		public IMenu,            // 00
		public MenuEventHandler  // 30
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_CursorMenu;
		inline static constexpr auto      VTABLE = VTABLE_CursorMenu;
		constexpr static std::string_view MENU_NAME = "Cursor Menu";

		~CursorMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04

		// override (MenuEventHandler) -- only inherited outside SKYRIM_CROSS_VR (see
		// the class declaration above); ProcessThumbstick/MouseMove are further
		// restricted to EXCLUSIVE_SKYRIM_VR since the base only keeps those as
		// real (overridable) virtuals there -- everywhere else they're
		// non-virtual RelocateVirtual wrappers (AE 1.7.99 shifts their vtable slot).
#ifndef SKYRIM_CROSS_VR
		bool CanProcess(InputEvent* a_event) override;  // 01
#endif
#ifdef EXCLUSIVE_SKYRIM_VR
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03
		bool ProcessMouseMove(MouseMoveEvent* a_event) override;    // 04
#endif

		RUNTIME_CAST_ACCESSOR(MenuEventHandler, AsMenuEventHandler, 0x30, 0x40);
	};
	STATIC_ASSERT_SIZE(CursorMenu, 0x40, 0x40, 0x50, 0x30);
}

#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"

namespace RE
{
	class ButtonEvent;
	class InputEvent;
	class KinectEvent;
	class MouseMoveEvent;
	class ThumbstickEvent;

	class MenuEventHandler : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_MenuEventHandler;
		inline static constexpr auto VTABLE = VTABLE_MenuEventHandler;

		MenuEventHandler() = default;
		virtual ~MenuEventHandler() = default;  // 00

		virtual bool CanProcess(InputEvent* a_event) = 0;  // 01
#if defined(EXCLUSIVE_SKYRIM_VR)
		// VR's MenuEventHandler vtable has three extra controller-input virtuals inserted
		// here, which shifts ProcessKinect/Thumbstick/MouseMove/Button down by +3 (to VR
		// slots 05-08). Declaring them in EXCLUSIVE_SKYRIM_VR makes the compiler place those
		// methods at the correct VR slots, so derived overrides bind correctly.
		// Per the MenuControls input dispatcher these route VR-only INPUT_EVENT_TYPE values
		// (type 7 -> Unk_02, type 6 -> Unk_03; Unk_04 is not routed by MenuControls). The
		// exact VR event classes are not yet identified, hence the Unk_ names.
		virtual bool Unk_02(void* a_event);  // VR 02 - { return false; }
		virtual bool Unk_03(void* a_event);  // VR 03 - { return false; }
		virtual bool Unk_04(void* a_event);  // VR 04 - { return false; }
#endif
		virtual bool ProcessKinect(KinectEvent* a_event);          // 02, VR 05 - { return false; }
		virtual bool ProcessThumbstick(ThumbstickEvent* a_event);  // 03, VR 06 - { return false; }
		virtual bool ProcessMouseMove(MouseMoveEvent* a_event);    // 04, VR 07 - { return false; }
		virtual bool ProcessButton(ButtonEvent* a_event);          // 05, VR 08 - { return false; }

		// members
		bool          registered;  // 0C
		std::uint8_t  unk0D;       // 0D
		std::uint16_t pad0E;       // 0E
	};
	static_assert(sizeof(MenuEventHandler) == 0x10);
}

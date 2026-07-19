#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "REL/Relocation.h"

namespace RE
{
	class ButtonEvent;
	class InputEvent;
	class KinectEvent;
	class MouseMoveEvent;
	class ThumbstickEvent;
	class VrWandTouchpadPositionEvent;
	class VrWandTouchpadSwipeEvent;

	class MenuEventHandler : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_MenuEventHandler;
		inline static constexpr auto VTABLE = VTABLE_MenuEventHandler;

		MenuEventHandler() = default;
		virtual ~MenuEventHandler() = default;  // 00

		virtual bool CanProcess(InputEvent* a_event) = 0;  // 01

		// VR's vtable inserts three wand-touchpad input virtuals after CanProcess, shifting
		// ProcessKinect/Thumbstick/MouseMove/Button from slots 02-05 down to 05-08. The
		// MenuControls dispatcher routes INPUT_EVENT_TYPE::kVrTouchpadSwipe (7) -> slot 02 and
		// kVrTouchpadPosition (6) -> slot 03; slot 04 is not routed by MenuControls.
		//
		// No SKYRIM_CROSS_VR accessor exists for these three (unlike the four below): RelocateVirtual
		// needs a slot in BOTH layouts to relocate between, and flat has none for touchpad input at
		// all (its vtable goes straight from CanProcess(01) to ProcessKinect(02)). A SKYRIM_CROSS_VR
		// derived class genuinely cannot receive VR wand-touchpad events today; that would need a new
		// mechanism, not a RelocateVirtual wrapper.
#if defined(EXCLUSIVE_SKYRIM_VR)
		virtual bool ProcessVrWandTouchpadSwipe(VrWandTouchpadSwipeEvent* a_event);        // VR 02 - { return false; }
		virtual bool ProcessVrWandTouchpadPosition(VrWandTouchpadPositionEvent* a_event);  // VR 03 - { return false; }
		virtual bool Unk_04(void* a_event);                                                // VR 04 - { return false; }
		virtual bool ProcessKinect(KinectEvent* a_event);                                  // VR 05 - { return false; }
		virtual bool ProcessThumbstick(ThumbstickEvent* a_event);                          // VR 06 - { return false; }
		virtual bool ProcessMouseMove(MouseMoveEvent* a_event);                            // VR 07 - { return false; }
		virtual bool ProcessButton(ButtonEvent* a_event);                                  // VR 08 - { return false; }
#elif !defined(SKYRIM_CROSS_VR)
		// EXCLUSIVE_SKYRIM_FLAT (SE/AE)
		virtual bool ProcessKinect(KinectEvent* a_event);          // 02 - { return false; }
		virtual bool ProcessThumbstick(ThumbstickEvent* a_event);  // 03 - { return false; }
		virtual bool ProcessMouseMove(MouseMoveEvent* a_event);    // 04 - { return false; }
		virtual bool ProcessButton(ButtonEvent* a_event);          // 05 - { return false; }
#else
		// SKYRIM_CROSS_VR (multi-runtime): non-virtual wrappers dispatch to the correct
		// per-runtime vtable slot, so a single binary works on both flat and VR.
		bool ProcessKinect(KinectEvent* a_event)
		{
			return REL::RelocateVirtual<decltype(&MenuEventHandler::ProcessKinect)>(0x02, 0x05, this, a_event);
		}
		bool ProcessThumbstick(ThumbstickEvent* a_event)
		{
			return REL::RelocateVirtual<decltype(&MenuEventHandler::ProcessThumbstick)>(0x03, 0x06, this, a_event);
		}
		bool ProcessMouseMove(MouseMoveEvent* a_event)
		{
			return REL::RelocateVirtual<decltype(&MenuEventHandler::ProcessMouseMove)>(0x04, 0x07, this, a_event);
		}
		bool ProcessButton(ButtonEvent* a_event)
		{
			return REL::RelocateVirtual<decltype(&MenuEventHandler::ProcessButton)>(0x05, 0x08, this, a_event);
		}
#endif

		// members
		bool          registered;  // 0C
		std::uint8_t  unk0D;       // 0D
		std::uint16_t pad0E;       // 0E
	};
	static_assert(sizeof(MenuEventHandler) == 0x10);
}

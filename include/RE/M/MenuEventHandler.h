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
		// The 3 VR-only slots have no flat-layout counterpart at all (flat's vtable goes straight
		// from CanProcess(01) to ProcessKinect(02)), so unlike the 4 shifting methods below they
		// can't be RelocateVirtual'd with a real SE/AE index. In SKYRIM_CROSS_VR they're exposed as
		// runtime-guarded accessors instead (IsVR() check first, matching GetVRTouchpadData() in
		// BSInputEventQueue.h and GetVRControllerRight() in BSInputDeviceManager.cpp) rather than a
		// RelocateVirtual wrapper -- same "check IsVR(), no-op on flat" idiom used throughout this
		// codebase for VR-exclusive data, just applied to a function instead of a member.
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

		// VR-only slots (no flat counterpart to relocate to): no-op on flat, dispatch to the real
		// VR vtable slot only when actually running as VR. The repeated index passed as the SE/AE
		// slot is a dead placeholder, not a real flat-layout value -- RelocateVirtual is unreachable
		// on flat because of the IsVR() guard above it.
		bool ProcessVrWandTouchpadSwipe(VrWandTouchpadSwipeEvent* a_event)
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return false;
			} else {
				return REL::RelocateVirtual<bool(MenuEventHandler*, VrWandTouchpadSwipeEvent*)>(0x02, 0x02, this, a_event);
			}
		}
		bool ProcessVrWandTouchpadPosition(VrWandTouchpadPositionEvent* a_event)
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return false;
			} else {
				return REL::RelocateVirtual<bool(MenuEventHandler*, VrWandTouchpadPositionEvent*)>(0x03, 0x03, this, a_event);
			}
		}
		bool Unk_04(void* a_event)
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return false;
			} else {
				return REL::RelocateVirtual<bool(MenuEventHandler*, void*)>(0x04, 0x04, this, a_event);
			}
		}
#endif

		// members
		bool          registered;  // 0C
		std::uint8_t  unk0D;       // 0D
		std::uint16_t pad0E;       // 0E
	};
	static_assert(sizeof(MenuEventHandler) == 0x10);
}

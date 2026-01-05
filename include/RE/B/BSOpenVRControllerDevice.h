#pragma once

#ifdef ENABLE_SKYRIM_VR

#	include "RE/B/BSTrackedControllerDevice.h"

namespace RE
{
	class BSOpenVRControllerDevice : public BSTrackedControllerDevice
	{
	public:
#	if defined(EXCLUSIVE_SKYRIM_VR)
		inline static constexpr auto RTTI = RTTI_BSOpenVRControllerDevice;
#	endif

		~BSOpenVRControllerDevice() override;

		struct Keys
		{
			enum Key : std::uint32_t  // Only tested with Oculus, keys are same for both controllers (L/R) are devices (6/5) respectively
			{
				kBY = 1,                // Y (left) / B (right) button
				kGrip = 2,              // Grip button (official OpenVR, but see kGripAlt)
				kXA = 7,                // X (left) / A (right) button
										// kJoystick = 11, // Joystick moving event
				kJoystickTrigger = 32,  // Joystick press (stick click)
				kTrigger = 33,          // Trigger button
				kGripAlt = 34,          // Grip button (Axis2, used by Oculus/Quest via OpenVR)
				kTouchpadClick = 35,    // Touchpad click (Vive/Index)
				kTouchpadAlt = 36,      // Touchpad alt (rare)
			};
		};
		using Key = Keys::Key;

		// override BSIInputDevice
		void               Initialize() override;                                                         // 01
		void               Poll(float a_timeDelta) override;                                              // 02
		void               Shutdown() override;                                                           // 03 - { return; }
		bool               GetButtonNameFromID(std::int32_t a_id, BSFixedString& a_buttonName) override;  // 04
		std::uint32_t      GetMappingKey(BSFixedString a_mapping) override;                               // 05
		bool               GetKeyCodeFromID(std::int32_t a_id, std::uint32_t& a_keyCode) override;        // 06
		[[nodiscard]] bool IsEnabled() const override;                                                    // 07 - { return true; }
		void               ClearInputState() override;                                                    // 08

		// Helper functions for VR button detection
		static inline bool IsGripButton(std::uint32_t keyCode)
		{
			// kGrip = 2 (official), kGripAlt = 34 (Axis2, Oculus/Quest)
			return keyCode == Keys::kGrip || keyCode == Keys::kGripAlt;
		}
		static inline bool IsTriggerButton(std::uint32_t keyCode)
		{
			return keyCode == Keys::kTrigger;
		}
		static inline bool IsStickClick(std::uint32_t keyCode)
		{
			return keyCode == Keys::kJoystickTrigger;
		}
		static inline bool IsAButton(std::uint32_t keyCode)
		{
			// Right A, left X (same code)
			return keyCode == Keys::kXA;
		}
		static inline bool IsBButton(std::uint32_t keyCode)
		{
			// Right B, left Y (same code)
			return keyCode == Keys::kBY;
		}
		static inline bool IsXButton(std::uint32_t keyCode)
		{
			// Left X, right A (same code)
			return keyCode == Keys::kXA;
		}
		static inline bool IsYButton(std::uint32_t keyCode)
		{
			// Left Y, right B (same code)
			return keyCode == Keys::kBY;
		}
		static inline bool IsTouchpadClick(std::uint32_t keyCode)
		{
			return keyCode == Keys::kTouchpadClick || keyCode == Keys::kTouchpadAlt;
		}

		// Returns true if Skyrim VR is in left-handed mode (swaps primary/secondary controllers)
		static inline bool IsLeftHandedMode()
		{
			static REL::Relocation<bool*> leftHandedMode{ REL::Offset(0x1e71778) };
			// Add null check for safety - defaults to false (right-handed) if pointer is invalid
			return leftHandedMode.get() != nullptr ? *leftHandedMode : false;
		}

		// New helpers for primary/secondary abstraction
		static inline bool IsPrimaryController(INPUT_DEVICE device)
		{
			// By convention, primary is VivePrimary, OculusPrimary, WMRPrimary
			bool isPhysPrimary = device == INPUT_DEVICE::kVivePrimary ||
			                     device == INPUT_DEVICE::kOculusPrimary ||
			                     device == INPUT_DEVICE::kWMRPrimary;
			return IsLeftHandedMode() ? !isPhysPrimary : isPhysPrimary;
		}
		static inline bool IsSecondaryController(INPUT_DEVICE device)
		{
			// By convention, secondary is ViveSecondary, OculusSecondary, WMRSecondary
			bool isPhysSecondary = device == INPUT_DEVICE::kViveSecondary ||
			                       device == INPUT_DEVICE::kOculusSecondary ||
			                       device == INPUT_DEVICE::kWMRSecondary;
			return IsLeftHandedMode() ? !isPhysSecondary : isPhysSecondary;
		}

	private:
#	if defined(EXCLUSIVE_SKYRIM_VR)
		std::uint64_t unk80[0x16];  // 080
		std::uint32_t unk130;       // 130
		std::uint32_t unk134;       // 134
		std::uint32_t unk138;       // 138
		std::uint32_t unk13C;       // 13C
		std::uint32_t unk140;       // 140
		std::uint32_t unk144;       // 144
		std::uint32_t unk148;       // 148
		std::uint32_t unk14C;       // 14C
#	endif
	};
#	if defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BSOpenVRControllerDevice) == 0x150);
#	endif

	// Returns a canonical string name for a given OpenVR controller key code
	inline const char* GetOpenVRButtonName(std::uint32_t keyCode)
	{
		using Keys = BSOpenVRControllerDevice::Keys;
		switch (keyCode) {
		case Keys::kTrigger:
			return "Trigger";
		case Keys::kGrip:
			return "Grip";
		case Keys::kGripAlt:
			return "Grip Alt";
		case Keys::kJoystickTrigger:
			return "Joystick Click";
		case Keys::kTouchpadClick:
			return "Touchpad Click";
		case Keys::kTouchpadAlt:
			return "Touchpad Alt";
		case Keys::kXA:
			return "A/X";
		case Keys::kBY:
			return "B/Y";
		// Add any other explicit codes here if needed
		default:
			break;
		}
		// Fallback to helper functions for extensibility
		if (BSOpenVRControllerDevice::IsTriggerButton(keyCode))
			return "Trigger";
		if (BSOpenVRControllerDevice::IsGripButton(keyCode))
			return "Grip";
		if (BSOpenVRControllerDevice::IsStickClick(keyCode))
			return "Joystick Click";
		if (BSOpenVRControllerDevice::IsTouchpadClick(keyCode))
			return "Touchpad Click";
		if (BSOpenVRControllerDevice::IsAButton(keyCode))
			return "A";
		if (BSOpenVRControllerDevice::IsBButton(keyCode))
			return "B";
		if (BSOpenVRControllerDevice::IsXButton(keyCode))
			return "X";
		if (BSOpenVRControllerDevice::IsYButton(keyCode))
			return "Y";
		return "?";
	}
}
#endif

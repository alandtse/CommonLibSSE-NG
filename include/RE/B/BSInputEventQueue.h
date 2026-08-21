#pragma once

#include "RE/B/BSTSingleton.h"
#include "RE/B/ButtonEvent.h"
#include "RE/C/CharEvent.h"
#include "RE/D/DeviceConnectEvent.h"
#include "RE/K/KinectEvent.h"
#include "RE/M/MouseMoveEvent.h"
#include "RE/T/ThumbstickEvent.h"
#include "RE/V/VrWandTouchpadPositionEvent.h"
#include "RE/V/VrWandTouchpadSwipeEvent.h"
#include "REL/RuntimeDataAccessors.h"
#include "SKSE/Version.h"

#ifdef ENABLE_SKYRIM_AE
#	include "RE/A/AmiiboEvent.h"
#	include "RE/M/MotionGestureEvent.h"
#	include "RE/S/SixaxisEvent.h"
#endif

namespace RE
{
	class BSInputEventQueue : public BSTSingletonSDM<BSInputEventQueue>
	{
	public:
		inline static constexpr std::uint8_t MAX_BUTTON_EVENTS = 10;
		inline static constexpr std::uint8_t MAX_CHAR_EVENTS = 5;
		inline static constexpr std::uint8_t MAX_MOUSE_EVENTS = 1;
		inline static constexpr std::uint8_t MAX_THUMBSTICK_EVENTS = 2;
		inline static constexpr std::uint8_t MAX_CONNECT_EVENTS = 1;
		inline static constexpr std::uint8_t MAX_KINECT_EVENTS = 1;
		inline static constexpr std::uint8_t MAX_VR_TOUCHPAD_POSITION_EVENTS = 3;
		inline static constexpr std::uint8_t MAX_VR_TOUCHPAD_SWIPE_EVENTS = 3;
#ifdef ENABLE_SKYRIM_AE
		// New in AE 1.7.99.
		inline static constexpr std::uint8_t MAX_SIXAXIS_EVENTS = 2;
		inline static constexpr std::uint8_t MAX_MOTION_GESTURE_EVENTS = 2;
		inline static constexpr std::uint8_t MAX_AMIIBO_EVENTS = 1;
#endif

		static BSInputEventQueue* GetSingleton();

		template <class... Args>
		void AddButtonEvent(Args&&... args)
		{
			AddEvent<ButtonEvent>(std::forward<Args>(args)...);
		}

		template <class... Args>
		void AddCharEvent(Args&&... args)
		{
			AddEvent<CharEvent>(std::forward<Args>(args)...);
		}

		template <class... Args>
		void AddMouseMoveEvent(Args&&... args)
		{
			AddEvent<MouseMoveEvent>(std::forward<Args>(args)...);
		}

		template <class... Args>
		void AddThumbstickEvent(Args&&... args)
		{
			AddEvent<ThumbstickEvent>(std::forward<Args>(args)...);
		}

		template <class... Args>
		void AddConnectEvent(Args&&... args)
		{
			AddEvent<DeviceConnectEvent>(std::forward<Args>(args)...);
		}

		template <class... Args>
		void AddKinectEvent(Args&&... args)
		{
			AddEvent<KinectEvent>(std::forward<Args>(args)...);
		}

// VR-specific overloads (forward to the template implementations)
#if defined(ENABLE_SKYRIM_VR)
		void AddButtonEvent(INPUT_DEVICE a_device, std::int32_t a_arg2, std::int32_t a_id, float a_value, float a_duration, const BSFixedString& a_userEvent = {});
		void AddThumbstickEvent(ThumbstickEvent::InputType a_id, INPUT_DEVICE a_device, float a_xValue, float a_yValue);
#endif

		void PushOntoInputQueue(InputEvent* a_event);
		void ClearInputQueue();

		struct VRTOUCHPAD_DATA
		{
#define VRTOUCHPAD_DATA_CONTENT                 \
	std::uint32_t vrTouchpadPositionEventCount; \
	std::uint32_t vrTouchpadSwipeEventCount;
			VRTOUCHPAD_DATA_CONTENT
		};
		static_assert(sizeof(VRTOUCHPAD_DATA) == 0x8);

		struct VRTOUCHPADEVENT_DATA
		{
#define VRTOUCHPADEVENT_DATA_CONTENT                                                       \
	VrWandTouchpadPositionEvent vrTouchpadPositionEvents[MAX_VR_TOUCHPAD_POSITION_EVENTS]; \
	VrWandTouchpadSwipeEvent    vrTouchpadSwipeEvents[MAX_VR_TOUCHPAD_SWIPE_EVENTS];
            VRTOUCHPADEVENT_DATA_CONTENT
		};
		static_assert(sizeof(VRTOUCHPADEVENT_DATA) == 0x198);

		// On AE, use GetQueueHead()/GetQueueTail(), not this struct's queueHead/queueTail.
		struct RUNTIME_DATA
		{
#if !defined(ENABLE_SKYRIM_VR)  // Non-VR
#	define RUNTIME_DATA_CONTENT                                             \
		ButtonEvent        buttonEvents[MAX_BUTTON_EVENTS];         /* 020*/ \
		CharEvent          charEvents[MAX_CHAR_EVENTS];             /* 200*/ \
		MouseMoveEvent     mouseEvents[MAX_MOUSE_EVENTS];           /* 2A0*/ \
		ThumbstickEvent    thumbstickEvents[MAX_THUMBSTICK_EVENTS]; /* 2D0*/ \
		DeviceConnectEvent connectEvents[MAX_CONNECT_EVENTS];       /* 330*/ \
		KinectEvent        kinectEvents[MAX_KINECT_EVENTS];         /* 350*/ \
		InputEvent*        queueHead;                               /* 380*/ \
		InputEvent*        queueTail;                               /* 388*/
#else
#	define RUNTIME_DATA_CONTENT                                             \
		VRTOUCHPAD_DATA_CONTENT;                                    /* 020*/ \
		ButtonEvent        buttonEvents[MAX_BUTTON_EVENTS];         /* 028*/ \
		CharEvent          charEvents[MAX_CHAR_EVENTS];             /* 208*/ \
		MouseMoveEvent     mouseEvents[MAX_MOUSE_EVENTS];           /* 2A8*/ \
		ThumbstickEvent    thumbstickEvents[MAX_THUMBSTICK_EVENTS]; /* 2D8*/ \
		DeviceConnectEvent connectEvents[MAX_CONNECT_EVENTS];       /* 338*/ \
		KinectEvent        kinectEvents[MAX_KINECT_EVENTS];         /* 358*/ \
		VRTOUCHPADEVENT_DATA_CONTENT;                               /* 380*/ \
		InputEvent* queueHead;                                      /* 518*/ \
		InputEvent* queueTail;                                      /* 520*/
#endif
			RUNTIME_DATA_CONTENT
		};

#ifdef ENABLE_SKYRIM_AE
		struct AE1799_EVENT_DATA
		{
			SixaxisEvent       sixaxisEvents[MAX_SIXAXIS_EVENTS];               // 000
			MotionGestureEvent motionGestureEvents[MAX_MOTION_GESTURE_EVENTS];  // 120
			AmiiboEvent        amiiboEvents[MAX_AMIIBO_EVENTS];                 // 190
		};
		static_assert(sizeof(AE1799_EVENT_DATA) == 0x1D0);
#endif

		// members
		std::uint8_t  pad001;                // 001
		std::uint16_t pad002;                // 002
		std::uint32_t buttonEventCount;      // 004
		std::uint32_t charEventCount;        // 008
		std::uint32_t mouseEventCount;       // 00C
		std::uint32_t thumbstickEventCount;  // 010
		std::uint32_t connectEventCount;     // 014
		std::uint32_t kinectEventCount;      // 018
		std::uint32_t pad01C;                // 01C
#if (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_VR))
		RUNTIME_DATA_CONTENT
#endif

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
#ifdef ENABLE_SKYRIM_AE
			const std::ptrdiff_t seAndAe =
				REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99) ?
					0x28 :
					0x20;
#else
			const std::ptrdiff_t seAndAe = 0x20;
#endif
			return REL::RelocateMember<RUNTIME_DATA>(this, seAndAe, 0x20);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return const_cast<BSInputEventQueue*>(this)->GetRuntimeData();
		}

#ifdef ENABLE_SKYRIM_AE
		RUNTIME_DATA_ACCESSOR_VERSIONED_OPTIONAL_EX(AE1799_EVENT_DATA, GetAe1799EventData, SKSE::RUNTIME_SSE_1_7_99, 0x388);
#endif

#if defined(EXCLUSIVE_SKYRIM_VR)
		[[nodiscard]] inline InputEvent*& GetQueueHead() noexcept
		{
			return GetRuntimeData().queueHead;
		}
		[[nodiscard]] inline InputEvent*& GetQueueTail() noexcept { return GetRuntimeData().queueTail; }
#elif defined(ENABLE_SKYRIM_VR)  // SKYRIM_CROSS_VR: either runtime is possible
		[[nodiscard]] inline InputEvent*& GetQueueHead() noexcept
		{
			if (REL::Module::IsVR()) {
				return GetRuntimeData().queueHead;
			}
			return REL::RelocateMemberIfNewer<InputEvent*>(SKSE::RUNTIME_SSE_1_7_99, this, 0x380, 0x558);
		}

		[[nodiscard]] inline InputEvent*& GetQueueTail() noexcept
		{
			if (REL::Module::IsVR()) {
				return GetRuntimeData().queueTail;
			}
			return REL::RelocateMemberIfNewer<InputEvent*>(SKSE::RUNTIME_SSE_1_7_99, this, 0x388, 0x560);
		}
#else                            // SE-only, AE-only, or flat -- no VR possible
		[[nodiscard]] inline InputEvent*& GetQueueHead() noexcept
		{
			return REL::RelocateMemberIfNewer<InputEvent*>(SKSE::RUNTIME_SSE_1_7_99, this, 0x380, 0x558);
		}

		[[nodiscard]] inline InputEvent*& GetQueueTail() noexcept
		{
			return REL::RelocateMemberIfNewer<InputEvent*>(SKSE::RUNTIME_SSE_1_7_99, this, 0x388, 0x560);
		}
#endif

		[[nodiscard]] VRTOUCHPAD_DATA* GetVRTouchpadData() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<VRTOUCHPAD_DATA>(this, 0, 0x20);
			}
		}

		[[nodiscard]] inline const VRTOUCHPAD_DATA* GetVRTouchpadData() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<VRTOUCHPAD_DATA>(this, 0, 0x20);
			}
		}

		[[nodiscard]] VRTOUCHPADEVENT_DATA* GetVRTouchpadEventData() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<VRTOUCHPADEVENT_DATA>(this, 0, 0x320);
			}
		}

		[[nodiscard]] inline const VRTOUCHPADEVENT_DATA* GetVRTouchpadEventData() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<VRTOUCHPADEVENT_DATA>(this, 0, 0x320);
			}
		}

	private:
		template <class T>
		T* GetCachedEvent();

		template <class T>
		void AdvanceCount();

		template <class T, class... Args>
		void AddEvent(Args&&... args)
		{
			if (auto cachedEvent = GetCachedEvent<T>()) {
				cachedEvent->Init(std::forward<Args>(args)...);
				PushOntoInputQueue(cachedEvent);
				AdvanceCount<T>();
			}
		}
	};
#if defined(EXCLUSIVE_SKYRIM_SE)
	static_assert(sizeof(BSInputEventQueue) == 0x390);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BSInputEventQueue) == 0x580);
#else
	static_assert(sizeof(BSInputEventQueue) == 0x20);
#endif
}
#undef RUNTIME_DATA_CONTENT
#undef VRTOUCHPAD_DATA_CONTENT
#undef VRTOUCHPADEVENT_DATA_CONTENT

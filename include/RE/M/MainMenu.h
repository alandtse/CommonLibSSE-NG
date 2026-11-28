#pragma once

#include "RE/B/BSScaleformExternalTexture.h"
#include "RE/B/BSTEvent.h"
#include "RE/G/GFxFunctionHandler.h"
#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSSaveDataEvent;
	class BSSystemEvent;
	struct BSGamerProfileEvent;
	struct MapMenuMarker;

	// menuDepth = 0
	// flags = kPausesGame | kDisablePauseMenu | kRequiresUpdate | kUpdateUsesCursor | kApplicationMenu
	// context = kMenuMode
	class MainMenu :
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		public IMenu,                          // 00
		public BSTEventSink<BSSystemEvent>,    // 30
		public BSTEventSink<BSSaveDataEvent>,  // 38
		public GFxFunctionHandler              // 40
#elif defined(EXCLUSIVE_SKYRIM_VR)
		public IMenu,                              // 00
		public BSTEventSink<BSSystemEvent>,        // 40
		public BSTEventSink<BSSaveDataEvent>,      // 48
		public BSTEventSink<BSGamerProfileEvent>,  // 50
		public MenuEventHandler                    // 58
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_MainMenu;
		inline static constexpr auto      VTABLE = VTABLE_MainMenu;
		constexpr static std::string_view MENU_NAME = "Main Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                              \
	BSScaleformExternalTexture gamerIconTexture; /* 00 */ \
	std::uint32_t              unk68;            /* 18 */ \
	std::uint8_t               unk6C;            /* 1C */ \
	std::uint8_t               unk6D;            /* 1D */ \
	std::uint8_t               unk6E;            /* 1E */ \
	std::uint8_t               pad6F;            /* 1F */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x20);

		~MainMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;                       // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05

#ifndef SKYRIM_CROSS_VR
		// override (BSTEventSink<BSSystemEvent>)
		BSEventNotifyControl ProcessEvent(const BSSystemEvent* a_event, BSTEventSource<BSSystemEvent>* a_eventSource) override;  // 01
		// override (BSTEventSink<BSSaveDataEvent>)
		BSEventNotifyControl ProcessEvent(const BSSaveDataEvent* a_event, BSTEventSource<BSSaveDataEvent>* a_eventSource) override;  // 01
#endif
#ifdef EXCLUSIVE_SKYRIM_FLAT
		// override (GFxFunctionHandler)
		void Call(Params& a_params) override;  // 01
#endif
#ifdef EXCLUSIVE_SKYRIM_VR
		// override (BSTEventSink<BSGamerProfileEvent>)
		BSEventNotifyControl ProcessEvent(const BSGamerProfileEvent* a_event, BSTEventSource<BSGamerProfileEvent>* a_eventSource) override;  // 01
		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#endif

#ifndef SKYRIM_CROSS_VR
		RUNTIME_CAST_ACCESSOR(BSTEventSink<BSSystemEvent>, AsBSSystemEventSink, 0x30, 0x40);
		RUNTIME_CAST_ACCESSOR(BSTEventSink<BSSaveDataEvent>, AsBSSaveDataEventSink, 0x38, 0x48);
#endif
		SE_ONLY_POINTER_ACCESSOR(GFxFunctionHandler, AsGFxFunctionHandler, 0x40);

		[[nodiscard]] BSTEventSink<BSGamerProfileEvent>* AsBSGamerProfileEventSink() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<BSTEventSink<BSGamerProfileEvent>>(this, 0, 0x50);
			}
		}

		[[nodiscard]] const BSTEventSink<BSGamerProfileEvent>* AsBSGamerProfileEventSink() const noexcept
		{
			return const_cast<MainMenu*>(this)->AsBSGamerProfileEventSink();
		}

		[[nodiscard]] const MenuEventHandler* AsMenuEventHandler() const noexcept
		{
			return const_cast<MainMenu*>(this)->AsMenuEventHandler();
		}

		[[nodiscard]] MenuEventHandler* AsMenuEventHandler() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<MenuEventHandler>(this, 0, 0x58);
			}
		}

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x50, 0x68);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 50, 68
#endif
	};
	STATIC_ASSERT_SIZE(MainMenu, 0x70, 0x70, 0x88, 0x30);
}
#undef RUNTIME_DATA_CONTENT

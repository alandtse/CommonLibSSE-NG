#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/I/IMenu.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/W/WorldSpaceMenu.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class MenuOpenCloseEvent;

	// menuDepth = 3
	// flags = kUpdateUsesCursor | kDontHideCursorWhenTopmost
	// context = kMenuMode
	class DialogueMenu :
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		public IMenu,                            // 00
		public BSTEventSink<MenuOpenCloseEvent>  // 30
#elif defined(EXCLUSIVE_SKYRIM_VR)
		public WorldSpaceMenu,                   // 00
		public BSTEventSink<MenuOpenCloseEvent>  // 58
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_DialogueMenu;
		inline static constexpr auto      VTABLE = VTABLE_DialogueMenu;
		constexpr static std::string_view MENU_NAME = "Dialogue Menu";

		struct Data
		{
			void*         unk00;  // 00
			std::uint64_t unk08;  // 08
		};
		static_assert(sizeof(Data) == 0x10);

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT BSTArray<Data> unk38; /* 00 */
			RUNTIME_DATA_CONTENT
		};

		~DialogueMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

#ifdef EXCLUSIVE_SKYRIM_VR
		// override (WorldSpaceMenu)
		void    SetupMenuNode() override;      // 0B
		NiNode* GetMenuParentNode() override;  // 0C
		void    SetTransform() override;       // 0D
#endif

#ifndef SKYRIM_CROSS_VR
		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;  // 01
#endif

		RUNTIME_CAST_ACCESSOR(BSTEventSink<MenuOpenCloseEvent>, AsMenuOpenCloseEventSink, 0x30, 0x58);

		VR_ONLY_POINTER_ACCESSOR(BSTEventSink<HudModeChangeEvent>, AsHudModeChangeEventSink, 0x40);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x38, 0x60);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 38, 60
#endif
#ifdef EXCLUSIVE_SKYRIM_VR
		NiPointer<NiNode> occlusionCheckNode;  // 78
#endif
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(DialogueMenu) == 0x50);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(DialogueMenu) == 0x80);
#else
	static_assert(sizeof(DialogueMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT

#pragma once

#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	struct BottomBar;
	struct ItemCard;
	struct MagicItemList;

	// menuDepth = 0
	// flags = kPausesGame | kUsesMenuContext | kDisablePauseMenu | kUpdateUsesCursor | kInventoryItemMenu | kCustomRendering
	// context = kItemMenu
	class MagicMenu :
#ifdef EXCLUSIVE_SKYRIM_VR
		public IMenu,            // 00
		public MenuEventHandler  // 40
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_MagicMenu;
		inline static constexpr auto      VTABLE = VTABLE_MagicMenu;
		constexpr static std::string_view MENU_NAME = "MagicMenu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                             \
	MagicItemList* itemList;        /* 00 */             \
	ItemCard*      itemCard;        /* 08 */             \
	BottomBar*     bottomBar;       /* 10 */             \
	GFxValue       root;            /* 18 - "Menu_mc" */ \
	bool           pcControlsReady; /* 30 */             \
	std::uint8_t   pad61;           /* 31 */             \
	std::uint16_t  pad62;           /* 32 */             \
	std::uint32_t  pad64;           /* 34 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x38);

		~MagicMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04
		void               PostDisplay() override;                           // 06

#ifdef EXCLUSIVE_SKYRIM_VR
		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;                                      // 01
		bool ProcessVrWandTouchpadPosition(VrWandTouchpadPositionEvent* a_event) override;  // 03
#endif

		VR_ONLY_POINTER_ACCESSOR(MenuEventHandler, AsMenuEventHandler, 0x40);
		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x30, 0x50);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 30, 50
#endif
	};
	STATIC_ASSERT_SIZE(MagicMenu, 0x68, 0x68, 0x88, 0x30);
}
#undef RUNTIME_DATA_CONTENT

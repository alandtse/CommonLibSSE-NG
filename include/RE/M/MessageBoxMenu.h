#pragma once

#include "RE/I/IMenu.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class MessageBoxData;

	// menuDepth = 10
	// flags = kPausesGame | kAlwaysOpen | kUsesCursor | kModal
	// context = kMenuMode
	class MessageBoxMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_MessageBoxMenu;
		inline static constexpr auto      VTABLE = VTABLE_MessageBoxMenu;
		constexpr static std::string_view MENU_NAME = "MessageBoxMenu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT            \
	bool          isPopulated; /* 00 */ \
	std::uint8_t  pad31;       /* 01 */ \
	std::uint16_t pad32;       /* 02 */ \
	std::uint32_t pad34;       /* 04 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x8);

		~MessageBoxMenu() override;  // 00

		// override (IMenu)
		void                   Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS     ProcessMessage(UIMessage& a_message) override;    // 04
		static MessageBoxMenu* GetCurrentMessageBoxMenu();                       // inlined in SE
		static std::uint32_t   GetQueueSize();
		static void            QueueMessage(MessageBoxData* a_data);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x30, 0x40);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 30, 40
#endif
	};
	STATIC_ASSERT_SIZE(MessageBoxMenu, 0x38, 0x38, 0x48, 0x30);
}
#undef RUNTIME_DATA_CONTENT

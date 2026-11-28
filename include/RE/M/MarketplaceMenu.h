#pragma once

#ifdef ENABLE_SKYRIM_AE

#	include "RE/G/GFxFunctionHandler.h"
#	include "RE/I/IMenu.h"
#	include "RE/M/MenuEventHandler.h"

namespace RE
{
	class MarketplaceDataProducer;

	class MarketplaceMenu :
		public IMenu,              // 00
		public GFxFunctionHandler  // 30
	{
	public:
		inline static constexpr auto      RTTI = RTTI_MarketplaceMenu;
		inline static constexpr auto      VTABLE = VTABLE_MarketplaceMenu;
		constexpr static std::string_view MENU_NAME = "Marketplace Menu";

		class InputHandler : public MenuEventHandler
		{
		public:
			inline static constexpr auto RTTI = RTTI_MarketplaceMenu__InputHandler;
			inline static constexpr auto VTABLE = VTABLE_MarketplaceMenu__InputHandler;

			~InputHandler() override;  // 00

			// override (MenuEventHandler)
			bool CanProcess(InputEvent* a_event) override;  // 01

			// members
			MarketplaceMenu* owner;                   // 10
			std::int8_t      lastCharacter;           // 18 - -1 after a release
			std::uint32_t*   heldButtonsBegin;        // 20
			std::uint32_t*   heldButtonsEnd;          // 28
			std::uint32_t*   heldButtonsCapacityEnd;  // 30
		};
		static_assert(sizeof(InputHandler) == 0x38);

		~MarketplaceMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05
		void               PostDisplay() override;                                                // 06

		// override (GFxFunctionHandler)
		void Call(Params& a_params) override;  // 01

		// members
		InputHandler*            inputHandler;  // 40
		bool                     unk48;         // 48
		bool                     unk49;         // 49
		MarketplaceDataProducer* dataProducer;  // 50
	};
	static_assert(sizeof(MarketplaceMenu) == 0x58);
}

#endif

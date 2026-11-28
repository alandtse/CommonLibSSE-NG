#pragma once

#ifdef ENABLE_SKYRIM_AE

#	include "RE/G/GFxFunctionHandler.h"
#	include "RE/I/IMenu.h"

namespace RE
{
	namespace LoginMenu
	{
		class loginMenu :
			public IMenu,              // 00
			public GFxFunctionHandler  // 30
		{
		public:
			inline static constexpr auto      RTTI = RTTI_LoginMenu__loginMenu;
			inline static constexpr auto      VTABLE = VTABLE_LoginMenu__loginMenu;
			constexpr static std::string_view MENU_NAME = "Login Menu";

			~loginMenu() override;  // 00

			// override (IMenu)
			void AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05

			// override (GFxFunctionHandler)
			void Call(Params& a_params) override;  // 01

			// members
			float         unk40;  // 40
			std::uint32_t pad44;  // 44
		};
		static_assert(sizeof(loginMenu) == 0x48);
	}
}

#endif

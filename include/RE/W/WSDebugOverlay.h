#pragma once

#ifdef ENABLE_SKYRIM_VR

#	include "RE/W/WorldSpaceMenu.h"

namespace RE
{
	class WSDebugOverlay :
		public WorldSpaceMenu  // 00
	{
	public:
		inline static constexpr auto      RTTI = RTTI_WSDebugOverlay;
		inline static constexpr auto      VTABLE = VTABLE_WSDebugOverlay;
		constexpr static std::string_view MENU_NAME = "WSDebugOverlay";

		~WSDebugOverlay() override;  // 00

		// override
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04
		NiNode*            GetMenuParentNode() override;                   // 0C
		void               SetTransform() override;                        // 0D
	};
#	ifdef EXCLUSIVE_SKYRIM_VR
	static_assert(sizeof(WSDebugOverlay) == 0x58);
#	endif
}

#endif

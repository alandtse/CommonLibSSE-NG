#pragma once

#ifdef ENABLE_SKYRIM_VR

#	include "RE/W/WorldSpaceMenu.h"

namespace RE
{
	class StatsMenuExtension :
		public WorldSpaceMenu  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_StatsMenuExtension;
		inline static constexpr auto VTABLE = VTABLE_StatsMenuExtension;

		~StatsMenuExtension() override;  // 00

		// override
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04
		NiNode*            GetMenuParentNode() override;                   // 0C
		void               SetTransform() override;                        // 0D
	};
#	ifdef EXCLUSIVE_SKYRIM_VR
	static_assert(sizeof(StatsMenuExtension) == 0x58);
#	endif
}

#endif

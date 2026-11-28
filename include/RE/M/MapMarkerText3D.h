#pragma once

#ifdef ENABLE_SKYRIM_VR

#	include "RE/G/GFxValue.h"
#	include "RE/W/WorldSpaceMenu.h"
#	include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class MapMarkerText3D :
		public WorldSpaceMenu  // 00
	{
	public:
		inline static constexpr auto      RTTI = RTTI_MapMarkerText3D;
		inline static constexpr auto      VTABLE = VTABLE_MapMarkerText3D;
		constexpr static std::string_view MENU_NAME = "MapMarkerText3D";

		struct RUNTIME_DATA
		{
#	define RUNTIME_DATA_CONTENT    \
		GFxValue worldMap; /* 58 */ \
		void*    unk70;    /* 70 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x20);

		~MapMarkerText3D() override;  // 00

		// override
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04
		void               SetupMenuNode() override;                       // 0B
		NiNode*            GetMenuParentNode() override;                   // 0C
		void               SetTransform() override;                        // 0D

		VR_ONLY_POINTER_ACCESSOR(RUNTIME_DATA, GetRuntimeData, 0x58);
		// members
#	ifdef EXCLUSIVE_SKYRIM_VR
		RUNTIME_DATA_CONTENT;  // 58
#	endif
	};
#	ifdef EXCLUSIVE_SKYRIM_VR
	static_assert(sizeof(MapMarkerText3D) == 0x78);
#	endif
}
#	undef RUNTIME_DATA_CONTENT

#endif

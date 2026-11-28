#pragma once

#ifdef ENABLE_SKYRIM_VR

#	include "RE/S/StatsMenuExtension.h"

namespace RE
{
	class StatsMenuPerks :
		public StatsMenuExtension  // 00
	{
	public:
		inline static constexpr auto      RTTI = RTTI_StatsMenuPerks;
		inline static constexpr auto      VTABLE = VTABLE_StatsMenuPerks;
		constexpr static std::string_view MENU_NAME = "StatsMenuPerks";

		~StatsMenuPerks() override;  // 00

		// override
		void SetupMenuNode() override;  // 0B
	};
#	ifdef EXCLUSIVE_SKYRIM_VR
	static_assert(sizeof(StatsMenuPerks) == 0x58);
#	endif
}

#endif

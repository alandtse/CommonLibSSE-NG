#pragma once

#ifdef ENABLE_SKYRIM_VR

#	include "RE/S/StatsMenuExtension.h"

namespace RE
{
	class StatsMenuSkillRing :
		public StatsMenuExtension  // 00
	{
	public:
		inline static constexpr auto      RTTI = RTTI_StatsMenuSkillRing;
		inline static constexpr auto      VTABLE = VTABLE_StatsMenuSkillRing;
		constexpr static std::string_view MENU_NAME = "StatsMenuSkillRing";

		~StatsMenuSkillRing() override;  // 00

		// override
		void SetupMenuNode() override;  // 0B
	};
#	ifdef EXCLUSIVE_SKYRIM_VR
	static_assert(sizeof(StatsMenuSkillRing) == 0x58);
#	endif
}

#endif

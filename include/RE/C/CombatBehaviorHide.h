#pragma once

#include "RE/A/AITimer.h"

namespace RE
{
	class CombatBehaviorHide
	{
	public:
		// members
		AITimer       timer00;  // 00
		AITimer       timer08;  // 08
		std::uint32_t unk10;    // 10
	};
	static_assert(sizeof(CombatBehaviorHide) == 0x14);
}

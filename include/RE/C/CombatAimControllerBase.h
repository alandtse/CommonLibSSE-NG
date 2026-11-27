#pragma once

#include "RE/C/CombatObject.h"

namespace RE
{
	class CombatAimControllerBase : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatAimControllerBase;
		inline static constexpr auto VTABLE = VTABLE_CombatAimControllerBase;

		~CombatAimControllerBase() override;  // 00
	};
}

#pragma once

#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorFaceAngle
	{
	public:
		// members
		NiPointer<CombatObject> object00;    // 00
		float                   angle;       // 08
		std::byte               unk0C[0x4];  // 0C
	};
	static_assert(sizeof(CombatBehaviorFaceAngle) == 0x10);
}

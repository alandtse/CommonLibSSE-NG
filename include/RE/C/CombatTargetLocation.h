#pragma once

#include "RE/B/BSCoreTypes.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class CombatTargetLocation : public CombatObject
	{
	public:
		struct AngleRange
		{
			float angle;     // 00
			float width;     // 04
			float minAngle;  // 08
			float maxAngle;  // 0C
		};
		static_assert(sizeof(AngleRange) == 0x10);

		TES_HEAP_REDEFINE_NEW();

		// members
		ActorHandle   actor;         // 10
		FormID        targetFormID;  // 14
		AngleRange    angle;         // 18
		NiPoint3      offset;        // 28
		std::uint32_t pad34;         // 34
	};
	static_assert(sizeof(CombatTargetLocation) == 0x38);
}

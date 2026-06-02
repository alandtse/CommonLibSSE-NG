#pragma once

#include "RE/H/hkStepInfo.h"
#include "RE/H/hkpCollisionAgentConfig.h"
#include "RE/H/hkpCollisionInput.h"
#include "RE/H/hkpCollisionQualityInfo.h"

namespace RE
{
	struct hkpAgent1nSector;

	struct hkpProcessCollisionInput : public hkpCollisionInput
	{
	public:
		// members
		hkStepInfo               stepInfo;                       // 60
		hkpCollisionQualityInfo* collisionQualityInfo;           // 70
		hkpAgent1nSector*        spareAgentSector;               // 78
		void*                    dynamicsInfo;                   // 80
		bool                     enableDeprecatedWelding;        // 88
		bool                     allowToSkipConfirmedCallbacks;  // 89
		std::uint16_t            pad8A;                          // 8A
		std::uint32_t            pad8C;                          // 8C
		hkpCollisionAgentConfig* config;                         // 90
	};
	static_assert(sizeof(hkpProcessCollisionInput) == 0x98);
}

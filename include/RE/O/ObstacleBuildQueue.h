#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"

namespace RE
{
	struct ObstacleBuildRequest;

	// Global queue drained by Job_Bounds_manager; instance pointer is gObstacleBuildQueue.
	struct ObstacleBuildQueue
	{
	public:
		// members
		std::uint32_t                   unk00;     // 00
		std::uint8_t                    mutex[8];  // 04 - thread id at 04, lock count at 08
		std::uint8_t                    pad0C[4];  // 0C
		BSTArray<ObstacleBuildRequest*> requests;  // 10
	};
	static_assert(sizeof(ObstacleBuildQueue) == 0x28);
}

#pragma once

#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	class BSPathingLockData;

	class BSPathingActorAttributes
	{
	public:
		float                              radius;    // 00
		float                              height;    // 04
		BSTSmartPointer<BSPathingLockData> lockData;  // 08
		std::uint32_t                      data;      // 10
	};
	static_assert(sizeof(BSPathingActorAttributes) == 0x18);
}

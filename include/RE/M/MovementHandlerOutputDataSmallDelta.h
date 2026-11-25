#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	// size inferred from the ctor's four 16-byte vectors
	struct MovementHandlerOutputDataSmallDelta
	{
	public:
		// members
		NiPoint3     rotation;     // 00
		float        speed;        // 0C
		NiPoint3     unk10;        // 10
		std::uint8_t unk1C[0x24];  // 1C
	};
	static_assert(sizeof(MovementHandlerOutputDataSmallDelta) == 0x40);
}

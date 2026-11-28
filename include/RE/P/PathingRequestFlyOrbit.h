#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/P/PathingRequestFly.h"

namespace RE
{
	class PathingRequestFlyOrbit : public PathingRequestFly
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestFlyOrbit;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestFlyOrbit;

		~PathingRequestFlyOrbit() override;  // 00

		// members
		float         radius;     // 128
		std::uint32_t unk12C;     // 12C
		NiPoint3      center;     // 130
		std::uint8_t  pad13C[4];  // 13C
	};
	static_assert(sizeof(PathingRequestFlyOrbit) == 0x140);
}

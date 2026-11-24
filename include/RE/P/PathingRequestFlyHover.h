#pragma once

#include "RE/P/PathingRequestFly.h"

namespace RE
{
	class PathingRequestFlyHover : public PathingRequestFly
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestFlyHover;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestFlyHover;

		~PathingRequestFlyHover() override;  // 00

		// members
		NiPoint3     hoverPoint;    // 128
		std::uint8_t unk134[0x1C];  // 134
	};
	static_assert(sizeof(PathingRequestFlyHover) == 0x150);
}

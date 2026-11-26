#pragma once

#include "RE/P/PathingRequestFly.h"

namespace RE
{
	class PathingRequestFlyTakeOff : public PathingRequestFly
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestFlyTakeOff;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestFlyTakeOff;

		~PathingRequestFlyTakeOff() override;  // 00
	};
	static_assert(sizeof(PathingRequestFlyTakeOff) == 0x128);
}

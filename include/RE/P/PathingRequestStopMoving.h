#pragma once

#include "RE/P/PathingRequest.h"

namespace RE
{
	class PathingRequestStopMoving : public PathingRequest
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestStopMoving;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestStopMoving;

		~PathingRequestStopMoving() override;  // 00
	};
	static_assert(sizeof(PathingRequestStopMoving) == 0x100);
}

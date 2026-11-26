#pragma once

#include "RE/B/BSPathingLocation.h"
#include "RE/P/PathingRequest.h"

namespace RE
{
	class PathingRequestHide : public PathingRequest
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestHide;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestHide;

		~PathingRequestHide() override;  // 00

		// members
		BSPathingLocation hideFromLocation;  // 100
		float             searchRadius;      // 130
		std::uint8_t      pad134[4];         // 134
	};
	static_assert(sizeof(PathingRequestHide) == 0x138);
}

#pragma once

#include "RE/P/PathingRequest.h"

namespace RE
{
	class PathingRequestOptimalLocation : public PathingRequest
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestOptimalLocation;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestOptimalLocation;

		~PathingRequestOptimalLocation() override;  // 00

		// members
		float minDistance;  // 100
		float maxDistance;  // 104
		float unk108;       // 108
		float unk10C;       // 10C
	};
	static_assert(sizeof(PathingRequestOptimalLocation) == 0x110);
}

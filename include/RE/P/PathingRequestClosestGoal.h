#pragma once

#include "RE/B/BSTArray.h"
#include "RE/P/PathingRequest.h"

namespace RE
{
	class PathingRequestClosestGoal : public PathingRequest
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestClosestGoal;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestClosestGoal;

		~PathingRequestClosestGoal() override;  // 00

		// members
		BSTArray<BSPathingLocation> locations;  // 100
		std::uint32_t               unk118;     // 118
		std::uint32_t               pad11C;     // 11C
	};
	static_assert(sizeof(PathingRequestClosestGoal) == 0x120);
}

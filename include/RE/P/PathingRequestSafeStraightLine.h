#pragma once

#include "RE/P/PathingRequestClosePoint.h"

namespace RE
{
	class PathingRequestSafeStraightLine : public PathingRequestClosePoint
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestSafeStraightLine;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestSafeStraightLine;

		~PathingRequestSafeStraightLine() override;  // 00

		// members
		std::uint64_t unk140;  // 140
	};
	static_assert(sizeof(PathingRequestSafeStraightLine) == 0x148);
}

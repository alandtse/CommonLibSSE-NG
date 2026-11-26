#pragma once

#include "RE/P/PathingRequest.h"

namespace RE
{
	class PathingRequestRotate : public PathingRequest
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestRotate;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestRotate;

		~PathingRequestRotate() override;  // 00
	};
	static_assert(sizeof(PathingRequestRotate) == 0x100);
}

#pragma once

#include "RE/B/BSPathingRequest.h"

namespace RE
{
	class PathingRequest : public BSPathingRequest
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequest;
		inline static constexpr auto VTABLE = VTABLE_PathingRequest;

		~PathingRequest() override;  // 00
	};
	static_assert(sizeof(PathingRequest) == 0x100);
}

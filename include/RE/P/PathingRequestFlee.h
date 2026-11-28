#pragma once

#include "RE/P/PathingRequest.h"

namespace RE
{
	class PathingRequestFlee : public PathingRequest
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestFlee;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestFlee;

		~PathingRequestFlee() override;  // 00

		// members
		float        fleeDistance;  // 100
		std::uint8_t pad104[4];     // 104
	};
	static_assert(sizeof(PathingRequestFlee) == 0x108);
}

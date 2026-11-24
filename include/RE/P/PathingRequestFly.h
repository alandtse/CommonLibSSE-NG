#pragma once

#include "RE/B/BSPathingRequest.h"

namespace RE
{
	// Members past BSPathingRequest are unresolved.
	class PathingRequestFly : public BSPathingRequest
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestFly;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestFly;

		~PathingRequestFly() override;  // 00

		// members
		std::uint8_t unk100[0x28];  // 100
	};
	static_assert(sizeof(PathingRequestFly) == 0x128);
}

#pragma once

#include "RE/B/BSPathingRequest.h"

namespace RE
{
	// Members past BSPathingRequest are unresolved.
	class PathingRequestClosePoint : public BSPathingRequest
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestClosePoint;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestClosePoint;

		~PathingRequestClosePoint() override;  // 00

		// members
		std::uint8_t unk100[0x40];  // 100
	};
	static_assert(sizeof(PathingRequestClosePoint) == 0x140);
}

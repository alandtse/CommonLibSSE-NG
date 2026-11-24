#pragma once

#include "RE/B/BSPathingRequest.h"

namespace RE
{
	class PathingRequestClosePoint : public BSPathingRequest
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestClosePoint;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestClosePoint;

		~PathingRequestClosePoint() override;  // 00

		// members
		BSPathingLocation closeLocation;  // 100
		float             scaledRadius;   // 130
		float             closeRadius;    // 134
		std::uint8_t      unk138;         // 138
		std::uint8_t      unk139;         // 139
		std::uint8_t      unk13A;         // 13A
		std::uint8_t      pad13B[5];      // 13B
	};
	static_assert(sizeof(PathingRequestClosePoint) == 0x140);
}

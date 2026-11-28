#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/P/PathingRequestFly.h"

namespace RE
{
	class PathingRequestFlyLand : public PathingRequestFly
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestFlyLand;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestFlyLand;

		~PathingRequestFlyLand() override;  // 00

		// members
		std::uint32_t landTargetHandle;  // 128 - ObjectRefHandle
		NiPoint3      landPoint;         // 12C
		std::uint32_t unk138;            // 138
		float         unk13C;            // 13C
		std::uint8_t  unk140;            // 140
		std::uint8_t  pad141[7];         // 141
	};
	static_assert(sizeof(PathingRequestFlyLand) == 0x148);
}

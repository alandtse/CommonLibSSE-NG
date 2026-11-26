#pragma once

#include "RE/B/BSTArray.h"
#include "RE/P/PathingRequest.h"

namespace RE
{
	class PathingRequestLOS : public PathingRequest
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestLOS;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestLOS;

		~PathingRequestLOS() override;  // 00

		// members
		void*              unk100;  // 100 - ref-counted pointer, type unconfirmed
		BSTArray<NiPoint3> points;  // 108
		float              unk120;  // 120
		float              unk124;  // 124
		float              unk128;  // 128
		float              unk12C;  // 12C
		std::uint32_t      unk130;  // 130
		std::uint32_t      pad134;  // 134
	};
	static_assert(sizeof(PathingRequestLOS) == 0x138);
}

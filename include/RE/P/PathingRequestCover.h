#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/P/PathingRequest.h"

namespace RE
{
	class PathingRequestCover : public PathingRequest
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestCover;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestCover;

		~PathingRequestCover() override;  // 00

		// members
		NiPoint3      unk100;     // 100
		float         unk10C;     // 10C
		float         unk110;     // 110
		float         unk114;     // 114
		std::int32_t  unk118;     // 118
		std::uint8_t  unk11C;     // 11C
		std::uint8_t  unk11D[5];  // 11D
		std::uint8_t  pad122[2];  // 122
		NiPoint3      unk124;     // 124
		NiPoint3      unk130;     // 130
		std::uint32_t pad13C;     // 13C
	};
	static_assert(sizeof(PathingRequestCover) == 0x140);
}

#pragma once

#include "RE/P/PathingRequest.h"

namespace RE
{
	class PathingRequestFly : public PathingRequest
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestFly;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestFly;

		~PathingRequestFly() override;  // 00

		// members
		std::uint32_t targetHandle;  // 100
		std::uint32_t pad104;        // 104
		void*         unk108;        // 108
		std::uint32_t unk110;        // 110
		std::uint8_t  unk114;        // 114
		std::uint8_t  pad115[3];     // 115
		void*         unk118;        // 118
		std::uint8_t  unk120;        // 120
		std::uint8_t  pad121[7];     // 121
	};
	static_assert(sizeof(PathingRequestFly) == 0x128);
}

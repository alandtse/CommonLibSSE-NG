#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/P/PathingRequestFly.h"

namespace RE
{
	class PathingRequestFlyAction : public PathingRequestFly
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestFlyAction;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestFlyAction;

		~PathingRequestFlyAction() override;  // 00

		// members
		std::uint32_t unk128;        // 128
		std::uint32_t targetHandle;  // 12C - ObjectRefHandle
		NiPoint3      unk130;        // 130
		std::uint32_t pad13C;        // 13C
		void*         unk140;        // 140
		void*         unk148;        // 148
		void*         unk150;        // 150
		std::uint8_t  unk158;        // 158
		std::uint8_t  pad159[3];     // 159
		std::uint32_t unk15C;        // 15C
	};
	static_assert(sizeof(PathingRequestFlyAction) == 0x160);
}

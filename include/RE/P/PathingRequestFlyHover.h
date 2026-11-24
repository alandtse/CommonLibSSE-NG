#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiPoint3.h"
#include "RE/P/PathingRequestFly.h"

namespace RE
{
	class PathingRequestFlyHover : public PathingRequestFly
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingRequestFlyHover;
		inline static constexpr auto VTABLE = VTABLE_PathingRequestFlyHover;

		~PathingRequestFlyHover() override;  // 00

		PathingRequestFlyHover* Ctor()
		{
			using func_t = PathingRequestFlyHover*(PathingRequestFlyHover*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(30465, 31305) };
			return func(this);
		}

		// members
		NiPoint3        hoverPoint;  // 128
		std::uint32_t   pad134;      // 134
		BSTArray<void*> unk138;      // 138
	};
	static_assert(sizeof(PathingRequestFlyHover) == 0x150);
}

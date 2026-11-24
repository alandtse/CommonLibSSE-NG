#pragma once

#include "RE/B/BSPathingStreamRead.h"

namespace RE
{
	class BGSLoadGameBuffer;

	class PathingStreamLoadGame : public BSPathingStreamRead
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingStreamLoadGame;
		inline static constexpr auto VTABLE = VTABLE_PathingStreamLoadGame;

		// members
		BGSLoadGameBuffer* buffer;  // 08
	};
	static_assert(sizeof(PathingStreamLoadGame) == 0x10);
}

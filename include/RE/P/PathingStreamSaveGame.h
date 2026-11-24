#pragma once

#include "RE/B/BSPathingStreamWrite.h"

namespace RE
{
	class BGSSaveGameBuffer;

	class PathingStreamSaveGame : public BSPathingStreamWrite
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingStreamSaveGame;
		inline static constexpr auto VTABLE = VTABLE_PathingStreamSaveGame;

		// members
		BGSSaveGameBuffer* buffer;  // 08
	};
	static_assert(sizeof(PathingStreamSaveGame) == 0x10);
}

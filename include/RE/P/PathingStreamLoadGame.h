#pragma once

#include "RE/B/BSPathingStreamRead.h"

namespace RE
{
	class BGSLoadGameBuffer;
	class MovementMessage;

	class PathingStreamLoadGame : public BSPathingStreamRead
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingStreamLoadGame;
		inline static constexpr auto VTABLE = VTABLE_PathingStreamLoadGame;

		bool ReadMovementMessage(MovementMessage** a_message)
		{
			using func_t = bool(PathingStreamLoadGame*, MovementMessage**);
			static REL::Relocation<func_t> func{ RELOCATION_ID(40812, 41825) };
			return func(this, a_message);
		}

		// members
		BGSLoadGameBuffer* buffer;  // 08
	};
	static_assert(sizeof(PathingStreamLoadGame) == 0x10);
}

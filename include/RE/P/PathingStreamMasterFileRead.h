#pragma once

#include "RE/B/BSPathingStreamRead.h"

namespace RE
{
	class TESFile;

	class PathingStreamMasterFileRead : public BSPathingStreamRead
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingStreamMasterFileRead;
		inline static constexpr auto VTABLE = VTABLE_PathingStreamMasterFileRead;

		// members
		std::uint8_t* bufferBase;  // 08
		std::uint8_t* cursor;      // 10
		TESFile*      file;        // 18
	};
	static_assert(sizeof(PathingStreamMasterFileRead) == 0x20);
}

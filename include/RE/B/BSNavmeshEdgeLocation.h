#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSNavmesh;

	struct BSNavmeshEdgeLocation
	{
	public:
		// members
		BSNavmesh*    navmesh;   // 00
		std::uint16_t triangle;  // 08
		std::uint16_t pad0A;     // 0A
		std::uint32_t pad0C;     // 0C
		std::uint32_t edge;      // 10 - 0xFFFFFFFF means none
		std::uint32_t pad14;     // 14
		NiPoint3      location;  // 18
		std::uint32_t pad24;     // 24
	};
	static_assert(sizeof(BSNavmeshEdgeLocation) == 0x28);
}

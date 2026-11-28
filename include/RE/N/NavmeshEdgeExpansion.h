#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSNavmesh;

	// Stack struct built by BSNavmeshSearch::ExpandNode for each candidate edge.
	struct NavmeshEdgeExpansion
	{
	public:
		// members
		NiPoint3      fromCenter;    // 00
		NiPoint3      toCenter;      // 0C
		BSNavmesh*    fromNavmesh;   // 18
		std::uint16_t fromTriIndex;  // 20
		std::uint16_t pad22;         // 22
		std::uint32_t pad24;         // 24
		std::int32_t  edgeIndex;     // 28
		std::uint32_t pad2C;         // 2C
		BSNavmesh*    toNavmesh;     // 30
		std::uint16_t toTriIndex;    // 38
		std::uint16_t pad3A;         // 3A
		std::uint32_t pad3C;         // 3C
		void*         fromTriangle;  // 40
		void*         toTriangle;    // 48
		float         parentCost;    // 50
		std::uint32_t pad54;         // 54
	};
	static_assert(sizeof(NavmeshEdgeExpansion) == 0x58);
}

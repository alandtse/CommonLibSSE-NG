#pragma once

#include "RE/N/NavmeshCostFilterSet.h"
#include "RE/N/NavmeshEdgeExpansion.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSNavmeshSearchFilters
	{
	public:
		virtual ~BSNavmeshSearchFilters();                                           // 00
		virtual bool FilterEdge(const NavmeshEdgeExpansion* a_edge, float* a_cost);  // 01 - a_cost is in/out

		// members
		void*                request;                // 08 - BSPathingRequest*
		std::uint8_t         refArray[0x118];        // 10 - small array of ref-counted pointers: capacity word, 32 inline entries, size
		void*                actorAttributes;        // 128 - BSPathingActorAttributes*
		float                radiusSq;               // 130
		std::uint32_t        pad134;                 // 134
		void*                refCounted138;          // 138
		bool                 flag140;                // 140
		std::uint8_t         pad141[7];              // 141
		void*                userData;               // 148
		float                badTriangleMultiplier;  // 150
		std::uint32_t        pad154;                 // 154
		NavmeshCostFilterSet costFilters;            // 158
		void*                refCounted1B0;          // 1B0
		float                maxEdgeLength;          // 1B8
		std::uint32_t        pad1BC;                 // 1BC
	};
	static_assert(sizeof(BSNavmeshSearchFilters) == 0x1C0);
}

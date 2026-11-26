#pragma once

#include "RE/N/NavmeshCostFilterSet.h"

namespace RE
{
	class BSNavmeshSearchFilters
	{
	public:
		virtual ~BSNavmeshSearchFilters();  // 00
		virtual void Unk_01(void);          // 01 - FilterEdge

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

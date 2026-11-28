#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiPoint3.h"

namespace RE::VelocityObstacle
{
	// Open polyline obstacle outline built for movement avoidance.
	struct ObstaclePolygon
	{
	public:
		// members
		NiPoint3      boundsMin;          // 00
		NiPoint3      boundsMax;          // 0C
		std::uint32_t pointsCapacity;     // 18 - small array word: capacity, bit 31 = inline storage
		std::uint8_t  pad1C[4];           // 1C
		NiPoint3      pointsStorage[10];  // 20 - inline points
		std::uint32_t pointCount;         // 98
		std::uint8_t  pad9C[4];           // 9C
		std::uint32_t isOpenChain;        // A0 - ctor sets 1; closing edge is only tested when 0
		std::uint8_t  padA4[4];           // A4
	};
	static_assert(sizeof(ObstaclePolygon) == 0xA8);
}

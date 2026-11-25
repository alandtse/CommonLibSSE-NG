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
		NiPoint3                    boundsMin;    // 00
		NiPoint3                    boundsMax;    // 0C
		BSTSmallArray<NiPoint3, 10> points;       // 18
		std::uint8_t                pad9C[4];     // 9C
		std::uint32_t               isOpenChain;  // A0 - ctor sets 1; closing edge is only tested when 0
		std::uint8_t                padA4[4];     // A4
	};
	static_assert(sizeof(ObstaclePolygon) == 0xA8);
}

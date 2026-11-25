#pragma once

#include "RE/B/BSPathingLocation.h"
#include "RE/B/BSTArray.h"
#include "RE/V/VelocityObstacle.h"

namespace RE
{
	// Refcounted request queued for ObstacleBuildQueue::Process by MovementPlannerAgentNavmeshBounds.
	struct ObstacleBuildRequest
	{
	public:
		// members
		std::int32_t                                        refCount;    // 000
		std::uint8_t                                        pad04[4];    // 004
		BSTSmallArray<VelocityObstacle::ObstaclePolygon, 4> obstacles;   // 008
		std::uint8_t                                        pad2B4[4];   // 2B4
		std::int32_t                                        buildState;  // 2B8 - -1 submitted, 0 once built
		std::uint8_t                                        pad2BC[4];   // 2BC
		BSPathingLocation                                   location;    // 2C0
		float                                               unk2F0;      // 2F0
		float                                               radius;      // 2F4 - actor radius * 0.5 * fNavmeshBoundsActorRadiusMultiplier:Pathfinding
	};
	static_assert(sizeof(ObstacleBuildRequest) == 0x2F8);
}

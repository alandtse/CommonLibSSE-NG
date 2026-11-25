#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/M/MovementControllerAI.h"
#include "RE/O/ObstacleBuildRequest.h"
#include "RE/V/VelocityObstacle.h"

namespace RE
{
	struct BSPathingSolution;
	class IMovementControllerRegisterInterface;

	// secondary bases (not declared in CLib): IMovementPlannerAgent, IMovementPathManagerAgent
	class MovementPlannerAgentNavmeshBounds : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPlannerAgentNavmeshBounds;
		inline static constexpr auto VTABLE = VTABLE_MovementPlannerAgentNavmeshBounds;

		// members
		void*                                 vptr_IMovementPlannerAgent;      // 18
		void*                                 vptr_IMovementPathManagerAgent;  // 20
		std::uint32_t                         ownerHandle;                     // 28 - Activate stores result of owner-handle slot call
		std::uint8_t                          unk2C[4];                        // 2C
		IMovementControllerRegisterInterface* registerInterface;               // 30 - RegisterWithController stores it; Unregister/dtor null it
		BSReadWriteLock                       lock;                            // 38 - PollPathEvent write-locks agent+0x38
		std::int32_t                          obstacleState;                   // 40 - -1 rebuild needed / 0 request in flight / 1 obstacles valid; LoadGame maps 0->-1
		float                                 normalizedDeceleration;          // 44 - SetPathingData from request actor attributes; NormalizedToAcceleration in PollPathEvent
		float                                 timeSinceObstacleBuild;          // 48 - FLT_MAX at SetPathingData, += deltaTime, 0 after build submission
		std::uint8_t                          unk4C[4];                        // 4C
		ObstacleBuildRequest*                 obstacleBuildRequest;            // 50 - intrusive-refcounted object holding a BSPathingLocation (dtor decrements, BSPathingLocation::dtor)
		std::uint32_t                         obstacleCapacity;                // 58 - small array word: capacity, bit 31 = inline storage
		std::uint8_t                          pad5C[4];                        // 5C
		VelocityObstacle::ObstaclePolygon     obstacleStorage[4];              // 60 - inline polygons
		std::uint32_t                         obstacleCount;                   // 300
		std::uint8_t                          pad304[4];                       // 304
		BSPathingSolution*                    solution;                        // 308 - intrusive-refcounted; SaveGame/LoadGame stream slot 0x68/0x70; dtor BSPathingSolution::dtor
		float                                 normalizedSpeed;                 // 310 - SetPathingData from request; NormalizedToSpeed in PollPathEvent; LoadGame stores 2.0
		std::uint8_t                          unk314[4];                       // 314
	};
	static_assert(sizeof(MovementPlannerAgentNavmeshBounds) == 0x318);
}

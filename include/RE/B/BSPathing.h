#pragma once

#include "RE/B/BSPathingLocation.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTSingleton.h"
#include "RE/F/FindTriangleForLocationFilterCheckDeltaZ.h"

namespace RE
{
	class BSPathingDoor;
	class BSPathingLockData;
	class BSPathingStreamRead;
	class BSPathingStreamWrite;
	class IDebugText;
	class IMovementParameters;
	class NiAVObject;
	class MovementMessage;
	class PathingCell;

	struct BSVirtualPathingNode
	{
		BSPathingLocation                location;      // 00
		BSTSmartPointer<MovementMessage> actionAtNode;  // 30

		bool HasActivateDoorAction()
		{
			using func_t = bool(BSVirtualPathingNode*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89210, 91682) };
			return func(this);
		}
	};
	static_assert(sizeof(BSVirtualPathingNode) == 0x38);

	struct BSPathingNode
	{
		BSPathingLocation                location;      // 00
		BSTSmartPointer<MovementMessage> actionAtNode;  // 30;
		NiPoint3                         tangent;       // 38

		bool HasActivateDoorAction()
		{
			using func_t = bool(BSPathingNode*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89222, 91695) };
			return func(this);
		}
		bool GetActionAtNode(MovementMessage** a_out)
		{
			using func_t = bool(BSPathingNode*, MovementMessage**);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89224, 91697) };
			return func(this, a_out);
		}
	};
	static_assert(sizeof(BSPathingNode) == 0x48);

	struct BSPathingSolution : BSIntrusiveRefCounted
	{
	public:
		bool FindClosestPointOnVirtualPath(const BSPathingLocation& a_position, BSPathingLocation& a_locationOut, float& a_pathPositionOut) const
		{
			using func_t = bool(const BSPathingSolution*, const BSPathingLocation&, BSPathingLocation&, float&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88551, 90987) };
			return func(this, a_position, a_locationOut, a_pathPositionOut);
		}

		bool GetVirtualLocationAtPathPosition(float a_pathPosition, BSPathingLocation& a_locationOut) const
		{
			using func_t = bool(const BSPathingSolution*, float, BSPathingLocation&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88555, 90991) };
			return func(this, a_pathPosition, a_locationOut);
		}

		bool FindVirtualPathPositionAtDistance(float a_pathPosition, float a_distance, bool a_forward, float& a_pathPositionOut, BSPathingLocation& a_locationOut) const
		{
			using func_t = bool(const BSPathingSolution*, float, float, bool, float&, BSPathingLocation&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88556, 90992) };
			return func(this, a_pathPosition, a_distance, a_forward, a_pathPositionOut, a_locationOut);
		}

		BSTSmallArray<BSVirtualPathingNode, 2> virtualPathingNodes;          // 08
		std::int32_t                           firstLoadedVirtualNodeIndex;  // 88
		std::int32_t                           lastLoadedVirtualNodeIndex;   // 8C
		BSTArray<BSPathingNode>                currentPathingNodes;          // 90
		bool                                   bIncompletePath;              // A8
		bool                                   bRequestGoalUnused;           // A9
	};
	static_assert(sizeof(BSPathingSolution) == 0xB0);

	struct BSPathingStart
	{
		BSPathingLocation location;  // 00
		float             tangent;   // 30
	};
	static_assert(sizeof(BSPathingStart) == 0x38);

	struct BSPathingGoal
	{
		NiPoint3          targetPoint;           // 00
		float             targetAngleTolerance;  // 0C
		BSPathingLocation location;              // 10
		float             zDelta;                // 40
		float             goalRadius;            // 44
		float             normalizeSpeedAtGoal;  // 48
	};
	static_assert(sizeof(BSPathingGoal) == 0x50);

	class BSPathingAvoidNode;

	struct BSPathingRestrictions
	{
		struct BSPathingSearchAreaRestrictions
		{
			NiPoint3 center;  // 00
			float    radius;  // 08
		};

		NiPointer<BSTArray<BSPathingAvoidNode>> avoidNodeArray;    // 00
		BSPathingSearchAreaRestrictions         areaRestrictions;  // 08
	};
	static_assert(sizeof(BSPathingRestrictions) == 0x18);

	class BSPathingSearchParameters;
	class BSPathingActorAttributes;
	class MovementActorAvoidanceParameters;
	class BSPathingRequest;

	class BSPathing : public BSTSingletonExplicit<BSPathing>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathing;
		inline static constexpr auto VTABLE = VTABLE_BSPathing;

		virtual ~BSPathing();  // 00

		// add
		virtual BSTArray<BSNavmeshInfo*> GetPotentialNavMeshInfoForLocation(PathingCell* a_cell) = 0;                                             // 01
		virtual bool                     GetAllLoadedNavmeshes1(BSTScrapHashMap<std::uint32_t, BSTSmartPointer<BSNavmesh>>& a_retNavMeshes) = 0;  // 02
		virtual bool                     GetAllLoadedNavmeshes2(BSScrapArray<BSNavmeshInfo*>& a_retNavMeshes) = 0;                                // 03
		virtual bool                     GetAllLoadedNavmeshes3(BSTArray<BSNavmeshInfo*>& a_retNavMeshes) = 0;                                    // 04
		virtual bool                     GetAllLoadedNavmeshes4(BSScrapArray<BSTSmartPointer<BSNavmesh>>& a_retNavMeshes) = 0;                    // 05
		virtual bool                     GetAllLoadedNavmeshes5(BSTArray<BSTSmartPointer<BSNavmesh>>& a_retNavMeshes) = 0;                        // 06
		virtual FormID                   GetSelectedDebugRef() = 0;                                                                               // 07
		virtual bool                     GetPathingDoorFromCollision(NiAVObject* a_object, BSTSmartPointer<BSPathingDoor>& a_retDoor) = 0;        // 08

		// members
		FindTriangleForLocationFilterCheckDeltaZ defaultTriangleFilter;  // 08
	};
	static_assert(sizeof(BSPathing) == 0x18);
}

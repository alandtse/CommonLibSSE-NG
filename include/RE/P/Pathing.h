#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTTuple.h"
#include "RE/P/PathingCell.h"

namespace RE
{
	class BSNavmesh;
	class BSPathingDoor;
	class BSPathingLocation;
	class BSPathingLockData;
	class PathingRequestSafeStraightLine;
	class TESObjectCELL;
	class TESObjectREFR;
	class TESWorldSpace;
	struct BSPathingSolution;
	struct CellAttachDetachEvent;
	struct IMovementPlayIdleResult;
	struct MovementArbitrationVectorAdd;
	struct MovementArbitrationAverageFloat;
	struct MovementArbitrationMaxWeightPoint;
	struct MovementArbitrationMaxWeightParameters;
	struct MovementMessageBlocked;

	class BSPathingCellManager : public BSTSingletonExplicit<BSPathingCellManager>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathingCellManager;
		inline static constexpr auto VTABLE = VTABLE_BSPathingCellManager;

		// add
		virtual float GetExteriorCellWidth() const = 0;                                                                                                                                                // 00
		virtual bool  GetPathingCell(const NiPoint3& a_location, const BSTSmartPointer<BSPathingCell>& a_hintCell, BSTSmartPointer<BSPathingCell>& a_cellOut) = 0;                                     // 01
		virtual bool  IsCloseTo(const NiPoint3& a_loc1, const BSTSmartPointer<BSPathingCell>& a_cell1, const NiPoint3& a_loc2, const BSTSmartPointer<BSPathingCell>& a_cell2, float a_tolerance) = 0;  // 02
		virtual void  FindPotentialNavmeshesForLocation1(BSPathingLocation& a_location, float a_radius, BSScrapArray<BSTSmartPointer<BSNavmesh>>& a_navMeshesOut) = 0;                                 // 03
		virtual void  FindPotentialNavmeshesForLocation2(BSPathingLocation& a_location, float a_radius, BSTArray<BSTSmartPointer<BSNavmesh>>& a_navMeshesOut) = 0;                                     // 04
		virtual void  FindConnectedNavmeshesForLocation3(BSPathingLocation& a_location, float a_radius, BSScrapArray<const BSNavmeshInfo*>& a_navMeshesOut) = 0;                                       // 05
		virtual void  FindConnectedNavmeshesForLocation4(BSPathingLocation& a_location, float a_radius, BSTArray<const BSNavmeshInfo*>& a_navMeshesOut) = 0;                                           // 06
		virtual void  FindConnectedNavmeshesForLocation5(BSPathingLocation& a_location, float a_radius, BSScrapArray<BSTSmartPointer<BSNavmesh>>& a_navMeshesOut) = 0;                                 // 07
		virtual void  FindConnectedNavmeshesForLocation6(BSPathingLocation& a_location, float a_radius, BSTArray<BSTSmartPointer<BSNavmesh>>& a_navMeshesOut) = 0;                                     // 08
		virtual float GetWaterHeight(const BSPathingLocation* a_location) const = 0;                                                                                                                   // 09

		virtual ~BSPathingCellManager();  // 0A
	};
	static_assert(sizeof(BSPathingCellManager) == 0x08);

	class MovementManager : public BSTSingletonExplicit<MovementManager>
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementManager;

		// members
		BSTSmartPointer<MovementArbitrationVectorAdd>           vectorAdd;               // 00
		BSTSmartPointer<MovementArbitrationAverageFloat>        floatAverage;            // 08
		BSTSmartPointer<MovementArbitrationMaxWeightPoint>      vectorMaxWeight;         // 10
		BSTSmartPointer<MovementArbitrationMaxWeightParameters> parametersMaxWeight;     // 18
		BSTSmartPointer<MovementMessageBlocked>                 movementBlockedMessage;  // 20
		BSTSmartPointer<IMovementPlayIdleResult>                nullPlayIdleResult;      // 28
		BSTSmartPointer<BSPathingSolution>                      emptySolution;           // 30
	};
	static_assert(sizeof(MovementManager) == 0x38);

	class Pathing :
		public BSPathing,                            // 00
		public BSPathingCellManager,                 // 18
		public BSTEventSink<CellAttachDetachEvent>,  // 20
		public BSTSingletonSDM<Pathing>,             // 28
		public MovementManager                       // 30
	{
	public:
		inline static constexpr auto RTTI = RTTI_Pathing;
		inline static constexpr auto VTABLE = VTABLE_Pathing;

		static Pathing* GetSingleton()
		{
			static REL::Relocation<Pathing**> singleton{ RELOCATION_ID(514893, 401037) };
			return *singleton;
		}

		bool GetPathingCell(const NiPoint3& a_location, TESObjectCELL* a_cell, TESWorldSpace* a_worldSpace, BSTSmartPointer<BSPathingCell>& a_cellOut)
		{
			using func_t = decltype(&Pathing::GetPathingCell);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29866, 30682) };
			return func(this, a_location, a_cell, a_worldSpace, a_cellOut);
		}

		bool FindClosestPointOnNavmesh(const BSTSmartPointer<BSPathingCell>& a_cell, const NiPoint3& a_location, NiPoint3& a_pointOut)
		{
			return FindClosestPointOnNavmesh(a_cell, a_location, defaultTriangleFilter, a_pointOut);
		}

		bool FindClosestPointOnNavmesh(const BSTSmartPointer<BSPathingCell>& a_cell, const NiPoint3& a_location, FindTriangleForLocationFilter& a_filter, NiPoint3& a_pointOut)
		{
			using func_t = bool (*)(Pathing*, const BSTSmartPointer<BSPathingCell>&, const NiPoint3&, FindTriangleForLocationFilter&, NiPoint3&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29832, 30648) };
			return func(this, a_cell, a_location, a_filter, a_pointOut);
		}

		BSPathingLocation* MakeLocationFromRef(BSPathingLocation* a_out, NiPoint3* a_pos, TESObjectREFR* a_ref)
		{
			using func_t = BSPathingLocation*(Pathing*, BSPathingLocation*, NiPoint3*, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29822, 30638) };
			return func(this, a_out, a_pos, a_ref);
		}

		BSPathingLocation* MakeLocation(BSPathingLocation* a_out, NiPoint3* a_pos, TESObjectCELL* a_cell, TESWorldSpace* a_worldSpace)
		{
			using func_t = BSPathingLocation*(Pathing*, BSPathingLocation*, NiPoint3*, TESObjectCELL*, TESWorldSpace*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29824, 30640) };
			return func(this, a_out, a_pos, a_cell, a_worldSpace);
		}

		bool FindNearestNavmeshPoint(TESWorldSpace* a_worldSpace, TESObjectCELL* a_cell, NiPoint3* a_pos, float a_radius, NiPoint3* a_outPos)
		{
			using func_t = bool(Pathing*, TESWorldSpace*, TESObjectCELL*, NiPoint3*, float, NiPoint3*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29833, 30649) };
			return func(this, a_worldSpace, a_cell, a_pos, a_radius, a_outPos);
		}

		bool RunSafeStraightLineSearch(PathingRequestSafeStraightLine** a_request)
		{
			using func_t = bool(Pathing*, PathingRequestSafeStraightLine**);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29836, 30652) };
			return func(this, a_request);
		}

		bool HasSafeStraightLine(TESObjectREFR* a_from, TESObjectREFR* a_to, float a_extraRange)
		{
			using func_t = bool(Pathing*, TESObjectREFR*, TESObjectREFR*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29837, 30653) };
			return func(this, a_from, a_to, a_extraRange);
		}

		BSPathingLocation* FindClosestReachableLocation(BSPathingLocation* a_out, BSPathingLocation* a_start, BSPathingLocation* a_goal, float a_maxCost)
		{
			using func_t = BSPathingLocation*(Pathing*, BSPathingLocation*, BSPathingLocation*, BSPathingLocation*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29838, 30654) };
			return func(this, a_out, a_start, a_goal, a_maxCost);
		}

		bool FindDoorsOnPath(BSPathingLocation* a_start, BSPathingLocation* a_goal, void* a_pathOut, BSPathingLockData* a_lockData, std::int32_t a_lockedDoorMode, bool a_allowTeleportFallback)
		{
			using func_t = bool(Pathing*, BSPathingLocation*, BSPathingLocation*, void*, BSPathingLockData*, std::int32_t, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29842, 30658) };
			return func(this, a_start, a_goal, a_pathOut, a_lockData, a_lockedDoorMode, a_allowTeleportFallback);
		}

		bool FindTeleportDoorBetweenRefs(TESObjectREFR* a_from, TESObjectREFR* a_to, BSPathingLockData* a_lockData, std::uint32_t* a_doorHandleOut, std::int32_t a_lockedDoorMode, float* a_lengthOut)
		{
			using func_t = bool(Pathing*, TESObjectREFR*, TESObjectREFR*, BSPathingLockData*, std::uint32_t*, std::int32_t, float*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29843, 30659) };
			return func(this, a_from, a_to, a_lockData, a_doorHandleOut, a_lockedDoorMode, a_lengthOut);
		}

		bool GetPathLengthWithDoors(BSPathingLocation* a_start, BSPathingLocation* a_goal, float* a_lengthOut)
		{
			using func_t = bool(Pathing*, BSPathingLocation*, BSPathingLocation*, float*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29845, 30661) };
			return func(this, a_start, a_goal, a_lengthOut);
		}

		bool CanCreatePathImpl(void* a_arg1, BSPathingLocation* a_start, BSPathingLocation* a_goal, void* a_arg4, void** a_out)
		{
			using func_t = bool(Pathing*, void*, BSPathingLocation*, BSPathingLocation*, void*, void**);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88020, 90408) };
			return func(this, a_arg1, a_start, a_goal, a_arg4, a_out);
		}

		bool FitPathTangentsImpl(void* a_ctx)
		{
			using func_t = bool(Pathing*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88139, 90528) };
			return func(this, a_ctx);
		}

		bool FitPathTangentsByHandleImpl(void* a_ctx)
		{
			using func_t = bool(Pathing*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88140, 90529) };
			return func(this, a_ctx);
		}

		bool ResolvePathNodeNavInfo(void* a_ctx, void* a_out)
		{
			using func_t = bool(Pathing*, void*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88130, 90518) };
			return func(this, a_ctx, a_out);
		}

		bool GetTriangleNormalAtLocation(BSPathingLocation* a_location, NiPoint3* a_outNormal, void* a_arg3)
		{
			using func_t = bool(Pathing*, BSPathingLocation*, NiPoint3*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88029, 90417) };
			return func(this, a_location, a_outNormal, a_arg3);
		}

		bool RayCastWithVerification(BSPathingLocation* a_start, const NiPoint3* a_target, void* a_arg4, BSPathingLocation* a_outHit, void* a_arg6, void* a_arg7)
		{
			using func_t = bool(Pathing*, BSPathingLocation*, const NiPoint3*, void*, BSPathingLocation*, void*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88025, 90413) };
			return func(this, a_start, a_target, a_arg4, a_outHit, a_arg6, a_arg7);
		}

		bool IsLocationNearEdgeVerified(BSPathingLocation* a_location, float a_radius)
		{
			using func_t = bool(Pathing*, BSPathingLocation*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88031, 90419) };
			return func(this, a_location, a_radius);
		}

		// members
		BSSpinLock                                                      cellCacheLock;  // 68
		BSTHashMap<PathingCellInfo, BSTSmartPointer<PathingCell>>       loadedCells;    // 70
		BSTArray<BSTTuple<std::uint64_t, BSTSmartPointer<PathingCell>>> recentCells;    // A0
#ifdef EXCLUSIVE_SKYRIM_VR
		std::uint8_t unkVrB8[0x20];
#endif
	};
	STATIC_ASSERT_SIZE(Pathing, 0xB8, 0xD8);
}

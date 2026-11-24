#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTSingleton.h"
#include "RE/O/ObstacleTaskData.h"

namespace RE
{
	class BSNavmeshObstacleData;
	class BSTaskletGroupData;
	class TESObjectREFR;

	struct NavmeshTriangleRef
	{
	public:
		// members
		BSNavmeshInfo* info;      // 00
		std::uint16_t  triangle;  // 08
		std::uint16_t  pad0A;     // 0A
		std::uint32_t  pad0C;     // 0C
	};
	static_assert(sizeof(NavmeshTriangleRef) == 0x10);

	struct ObstacleTaskMapEntry
	{
	public:
		// members
		std::uint32_t         navMeshID;  // 00
		std::uint32_t         pad04;      // 04
		ObstacleTaskData*     task;       // 08
		ObstacleTaskMapEntry* next;       // 10
	};
	static_assert(sizeof(ObstacleTaskMapEntry) == 0x18);

	// Owns the per-navmesh ObstacleTaskData tasks that apply dynamic obstacles (doors, placed objects) on the pathing job thread.
	// Members not listed (0x10-0x6F, 0xC0-0x1A0 except where named, 0x1B0-0x1CF) are known to exist but their layout is unresolved.
	class NavMeshObstacleManager : public BSTSingletonSDM<NavMeshObstacleManager>
	{
	public:
		inline static constexpr auto RTTI = RTTI_NavMeshObstacleManager;
		inline static constexpr auto VTABLE = VTABLE_NavMeshObstacleManager;

		virtual ~NavMeshObstacleManager();  // 00

		void Flush()
		{
			using func_t = void(NavMeshObstacleManager*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29619, 30451) };
			func(this);
		}
		void QueueActivatedEntity(void* a_entity)
		{
			using func_t = void(NavMeshObstacleManager*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29621, 30453) };
			func(this, a_entity);
		}
		void AddCompletedTask(ObstacleTaskData* a_task)
		{
			using func_t = void(NavMeshObstacleManager*, ObstacleTaskData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29624, 30456) };
			func(this, a_task);
		}
		void AddObstaclesForPendingRefs()
		{
			using func_t = void(NavMeshObstacleManager*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29627, 30459) };
			func(this);
		}
		void RemoveObstaclesForRemovedRefs()
		{
			using func_t = void(NavMeshObstacleManager*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29628, 30460) };
			func(this);
		}
		void TrackActivatedObstacles()
		{
			using func_t = void(NavMeshObstacleManager*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29629, 30461) };
			func(this);
		}
		void FinishDeactivatedObstacles()
		{
			using func_t = void(NavMeshObstacleManager*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29630, 30462) };
			func(this);
		}
		void UpdateAllObstacles()
		{
			using func_t = void(NavMeshObstacleManager*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29631, 30463) };
			func(this);
		}
		void UpdateMovedObstacles()
		{
			using func_t = void(NavMeshObstacleManager*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29632, 30465) };
			func(this);
		}
		void DispatchTasks()
		{
			using func_t = void(NavMeshObstacleManager*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29633, 30466) };
			func(this);
		}
		bool CommitTasks()
		{
			using func_t = bool(NavMeshObstacleManager*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29634, 30467) };
			return func(this);
		}
		void CompactCompletedTaskNavmeshes()
		{
			using func_t = void(NavMeshObstacleManager*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29636, 30469) };
			func(this);
		}
		void DestroyTasks()
		{
			using func_t = void(NavMeshObstacleManager*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29637, 30470) };
			func(this);
		}
		void ProcessDoorCloseRequests()
		{
			using func_t = void(NavMeshObstacleManager*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29639, 30472) };
			func(this);
		}
		void UpdateObstacle(BSNavmeshObstacleData** a_obstacle)
		{
			using func_t = void(NavMeshObstacleManager*, BSNavmeshObstacleData**);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29643, 30476) };
			func(this, a_obstacle);
		}
		void ReplaceObstaclesForRef(std::uint32_t a_formID, TESObjectREFR* a_ref)
		{
			using func_t = void(NavMeshObstacleManager*, std::uint32_t, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29644, 30477) };
			func(this, a_formID, a_ref);
		}
		bool AttachTaskToTaskletManager(ObstacleTaskData* a_task)
		{
			using func_t = bool(NavMeshObstacleManager*, ObstacleTaskData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29646, 30479) };
			return func(this, a_task);
		}
		void AddObstaclesForRef(TESObjectREFR* a_ref)
		{
			using func_t = void(NavMeshObstacleManager*, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29647, 30480) };
			func(this, a_ref);
		}
		void RemoveObstaclesForRef(std::uint32_t a_formID)
		{
			using func_t = void(NavMeshObstacleManager*, std::uint32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29648, 30481) };
			func(this, a_formID);
		}

		// members
		bool                             refreshAllPending;       // 09
		std::uint8_t                     pad0A[0x66];             // 0A - unresolved maps and sets
		BSTArray<BSNavmeshObstacleData*> movingObstacles;         // 70
		BSTArray<void*>                  activatedEntityQueue;    // 88
		BSTArray<void*>                  deactivatedEntityQueue;  // A0
		std::uint8_t                     padB8[0xE8];             // B8
		BSTaskletGroupData*              taskGroup;               // 1A0
		std::uint8_t                     pad1A8[0xC];             // 1A8
		std::uint32_t                    taskMapCapacity;         // 1B4
		std::uint32_t                    taskMapFreeCount;        // 1B8
		std::uint32_t                    taskMapFreeIdx;          // 1BC
		std::uint8_t                     pad1C0[0x10];            // 1C0
		ObstacleTaskMapEntry*            taskMapEntries;          // 1D0
		BSTArray<ObstacleTaskData*>      queuedTasks;             // 1D8
		BSTArray<ObstacleTaskData*>      completedTasks;          // 1F0
		std::uint64_t                    taskMutex;               // 208
		BSTArray<NavmeshEdgeRef>         danglingEdges;           // 210
		BSTArray<NavmeshTriangleRef>     relinkInputs;            // 228
		std::uint32_t                    state;                   // 240
		float                            timer;                   // 244
		std::uint8_t                     pad248[8];               // 248
	};
	static_assert(sizeof(NavMeshObstacleManager) == 0x250);
}

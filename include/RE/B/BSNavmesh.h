#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/M/MemoryManager.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSNavmeshObstacleData;
	class BSNavmeshObstacleUndoData;
	class BSPathingCell;
	class BSPathingDoor;

	enum class EDGE_EXTRA_INFO_TYPE
	{
		kInvalid = static_cast<std::underlying_type_t<EDGE_EXTRA_INFO_TYPE>>(-1),
		kPortal = 0,
		kLedgeUp = 1,
		kLedgeDown = 2,
		kEnableDisablePortal = 3
	};

	struct BSNavmeshVertex
	{
	public:
		// members
		NiPoint3 location;  // 0
	};
	static_assert(sizeof(BSNavmeshVertex) == 0xC);

	struct BSNavmeshTriangle
	{
	public:
		// reference:
		// edge 0-1 = 0
		// edge 1-2 = 1
		// edge 2-0 = 2
		enum class TriangleFlag
		{
			kNone = 0,
			kEdge0_Link = 1 << 0,
			kEdge1_Link = 1 << 1,
			kEdge2_Link = 1 << 2,
			kDeleted = 1 << 3,
			kNoLargeCreatures = 1 << 4,
			kOverlapping = 1 << 5,
			kPreferred = 1 << 6,
			kWater = 1 << 9,
		};

		// reference:
		// quarter = 1/4
		// half = 2/4
		// tri = 3/4
		// full = 4/4
		enum class TraversalFlag
		{
			kNone = 0,
			kEdge0_CoverValueQuarter = 1 << 0,
			kEdge0_CoverValueHalf = 1 << 1,
			kEdge0_CoverValueTri = 1 << 2,
			kEdge0_CoverValueFull = 1 << 3,
			kEdge0_Left = 1 << 4,
			kEdge0_Right = 1 << 5,
			kEdge1_CoverValueQuarter = 1 << 6,
			kEdge1_CoverValueHalf = 1 << 7,
			kEdge1_CoverValueTri = 1 << 8,
			kEdge1_CoverValueFull = 1 << 9,
			kEdge1_Left = 1 << 10,
			kEdge1_Right = 1 << 11
		};

		// members
		std::uint16_t                              vertices[3];     // 00
		std::uint16_t                              triangles[3];    // 06 - 0xFF == NONE
		REX::EnumSet<TriangleFlag, std::uint16_t>  triangleFlags;   // 0C
		REX::EnumSet<TraversalFlag, std::uint16_t> traversalFlags;  // 0E
	};
	static_assert(sizeof(BSNavmeshTriangle) == 0x10);

	struct BSNavmeshTriangleEdgePortal
	{
	public:
		// members
		FormID        otherMeshID;  // 0
		std::uint16_t triangle;     // 4
		std::int8_t   edgeIndex;    // 6
		std::uint8_t  pad7;         // 7
	};
	static_assert(sizeof(BSNavmeshTriangleEdgePortal) == 0x8);

	struct BSNavmeshEdgeExtraInfo
	{
	public:
		// members
		REX::EnumSet<EDGE_EXTRA_INFO_TYPE, std::uint32_t> type;    // 0
		BSNavmeshTriangleEdgePortal                       portal;  // 4
	};
	static_assert(sizeof(BSNavmeshEdgeExtraInfo) == 0xC);

	struct BSNavmeshTriangleDoorPortal
	{
	public:
		// members
		BSTSmartPointer<BSPathingDoor> door;                 // 00
		std::uint16_t                  owningTriangleIndex;  // 08
		std::uint16_t                  pad0A;                // 0A
		std::uint32_t                  pad0C;                // 0C
	};
	static_assert(sizeof(BSNavmeshTriangleDoorPortal) == 0x10);

	struct BSNavmeshClosedDoorInfo
	{
	public:
		// members
		BSTSmartPointer<BSPathingDoor> door;           // 00
		std::uint16_t                  triangleIndex;  // 08
		std::uint16_t                  pad0A;          // 0A
		std::uint32_t                  pad0C;          // 0C
	};
	static_assert(sizeof(BSNavmeshClosedDoorInfo) == 0x10);

	struct BSNavmeshCoverEdge
	{
	public:
		// members
		std::uint16_t vertices[2];  // 00
		std::uint32_t data;         // 08
	};
	static_assert(sizeof(BSNavmeshCoverEdge) == 0x8);

	struct BSNavmeshGrid
	{
	public:
		void CollectCellsNearPoint(const float* a_point, BSTArray<void*>* a_outCells)
		{
			using func_t = void(BSNavmeshGrid*, const float*, BSTArray<void*>*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88612, 91043) };
			func(this, a_point, a_outCells);
		}

		void CollectTrianglesInBounds(const float* a_min, const float* a_max, BSTArray<std::uint16_t>* a_outTriangleIndices)
		{
			using func_t = void(BSNavmeshGrid*, const float*, const float*, BSTArray<std::uint16_t>*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88622, 91052) };
			func(this, a_min, a_max, a_outTriangleIndices);
		}

		// members
		std::uint32_t                        gridSize;          // 00
		float                                columnSectionLen;  // 04
		float                                rowSectionLen;     // 08
		NiPoint3                             gridBoundsMin;     // 0C
		NiPoint3                             gridBoundsMax;     // 18
		std::uint32_t                        pad24;             // 24
		SimpleArray<BSTArray<std::uint16_t>> gridData;          // 28
	};
	static_assert(sizeof(BSNavmeshGrid) == 0x30);

	class BSNavmesh : public BSIntrusiveRefCounted  // NVNM
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSNavmesh;
		inline static constexpr auto VTABLE = VTABLE_BSNavmesh;

		virtual ~BSNavmesh();  // 00

		// add
		virtual std::uint32_t QNavmeshID() = 0;  // 01

		NiPoint3 GetNormal(std::uint16_t a_tri) const
		{
			NiPoint3 result;

			using func_t = NiPoint3*(const BSNavmesh*, NiPoint3&, std::uint16_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88674, 91114) };
			func(this, result, a_tri);

			return result;
		}

		bool GetEdgePoints(std::uint16_t a_triangle, std::uint32_t a_edge, NiPoint3* a_outStart, NiPoint3* a_outEnd)
		{
			using func_t = bool(BSNavmesh*, std::uint16_t, std::uint32_t, NiPoint3*, NiPoint3*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88645, 91075) };
			return func(this, a_triangle, a_edge, a_outStart, a_outEnd);
		}

		bool GetEdgeVertexIndices(std::uint16_t a_triangle, std::uint32_t a_edge, std::uint16_t* a_outStart, std::uint16_t* a_outEnd)
		{
			using func_t = bool(BSNavmesh*, std::uint16_t, std::uint32_t, std::uint16_t*, std::uint16_t*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88642, 91072) };
			return func(this, a_triangle, a_edge, a_outStart, a_outEnd);
		}

		bool FindClosestBoundaryEdge(NiPoint3* a_pos, float a_radius, std::uint16_t* a_outTriangle, std::int32_t* a_outEdge, bool a_flip)
		{
			using func_t = bool(BSNavmesh*, NiPoint3*, float, std::uint16_t*, std::int32_t*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88683, 91123) };
			return func(this, a_pos, a_radius, a_outTriangle, a_outEdge, a_flip);
		}

		bool GetTriangleHeightAtPoint(std::uint16_t a_triangle, NiPoint3* a_pos, float* a_outZ)
		{
			using func_t = bool(BSNavmesh*, std::uint16_t, NiPoint3*, float*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88688, 91132) };
			return func(this, a_triangle, a_pos, a_outZ);
		}

		BSNavmeshTriangleDoorPortal* GetDoorPortalAt(std::uint16_t a_index)
		{
			using func_t = BSNavmeshTriangleDoorPortal*(BSNavmesh*, std::uint16_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88657, 91091) };
			return func(this, a_index);
		}

		void FixupNumericIDs(void* a_context)
		{
			using func_t = void(BSNavmesh*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88663, 91100) };
			func(this, a_context);
		}

		bool HasLinkToNavmesh(void* a_target)
		{
			using func_t = bool(BSNavmesh*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88665, 91102) };
			return func(this, a_target);
		}

		bool RemoveObstacleAt(std::uint32_t a_index, void* a_outEdges)
		{
			using func_t = bool(BSNavmesh*, std::uint32_t, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88708, 91152) };
			return func(this, a_index, a_outEdges);
		}

		bool FindRandomPointNearRetry(const NiPoint3* a_center, float a_radius, void* a_out)
		{
			using func_t = bool(BSNavmesh*, const NiPoint3*, float, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88692, 91136) };
			return func(this, a_center, a_radius, a_out);
		}

		void GetEdgeLine2D(std::uint16_t a_triangle, std::uint32_t a_edge, float* a_outA, float* a_outB)
		{
			using func_t = void(BSNavmesh*, std::uint16_t, std::uint32_t, float*, float*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88705, 91149) };
			func(this, a_triangle, a_edge, a_outA, a_outB);
		}

		void BuildMeshGrid(void* a_arg0, void* a_arg1)
		{
			using func_t = void(BSNavmesh*, void*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88670, 91108) };
			func(this, a_arg0, a_arg1);
		}

		void FindSegmentCrossingTriangleEdge(void* a_out, std::uint16_t a_triangle, std::int32_t a_skipEdge, const NiPoint3* a_segStart, const NiPoint3* a_segEnd)
		{
			using func_t = void(BSNavmesh*, void*, std::uint16_t, std::int32_t, const NiPoint3*, const NiPoint3*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88701, 91145) };
			func(this, a_out, a_triangle, a_skipEdge, a_segStart, a_segEnd);
		}

		bool FindTriangleAtPointAccepted(const NiPoint3* a_point, void* a_visitor, float* a_outZ)
		{
			using func_t = bool(BSNavmesh*, const NiPoint3*, void*, float*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88690, 91134) };
			return func(this, a_point, a_visitor, a_outZ);
		}

		bool AddTrianglesToMeshGrid(std::uint16_t a_first, std::uint16_t a_last)
		{
			using func_t = bool(BSNavmesh*, std::uint16_t, std::uint16_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88671, 91110) };
			return func(this, a_first, a_last);
		}

		bool RemoveTrianglesFromMeshGrid(std::uint16_t a_first, std::uint16_t a_last)
		{
			using func_t = bool(BSNavmesh*, std::uint16_t, std::uint16_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88672, 91112) };
			return func(this, a_first, a_last);
		}

		BSNavmeshEdgeExtraInfo* GetOrCreateEdgeExtraInfo(std::uint16_t a_triangle, std::uint32_t a_edge)
		{
			using func_t = BSNavmeshEdgeExtraInfo*(BSNavmesh*, std::uint16_t, std::uint32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88696, 91140) };
			return func(this, a_triangle, a_edge);
		}

		std::uint32_t CollectTriangleGridCells(std::uint16_t a_triangle, void* a_outCells)
		{
			using func_t = std::uint32_t(BSNavmesh*, std::uint16_t, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88722, 91173) };
			return func(this, a_triangle, a_outCells);
		}

		// members
		std::uint32_t                                                pad00C;                 // 00C
		BSTArray<BSNavmeshVertex>                                    vertices;               // 010
		BSTArray<BSNavmeshTriangle>                                  triangles;              // 028
		BSTArray<BSNavmeshEdgeExtraInfo>                             extraEdgeInfo;          // 040
		BSTArray<BSNavmeshTriangleDoorPortal>                        doorPortals;            // 058
		BSTArray<BSNavmeshClosedDoorInfo>                            closedDoors;            // 070
		BSTArray<std::uint16_t>                                      coverTriangles;         // 088 - triangle indices of cover triangles
		BSNavmeshGrid                                                meshGrid;               // 0A0
		BSTArray<NiPointer<BSNavmeshObstacleUndoData>>               obstacles;              // 0D0
		BSTHashMap<std::uint16_t, NiPointer<BSNavmeshObstacleData>>* triangleToObstacleMap;  // 0E8
		BSTArray<void*>                                              unk0F0;                 // 0F0 - obstaclePOVs/disabledLinks?
		BSTSmartPointer<BSPathingCell>                               parentCell;             // 108
		void*                                                        unk110;                 // 110 - navmeshInfo?
	};
	static_assert(sizeof(BSNavmesh) == 0x118);
}

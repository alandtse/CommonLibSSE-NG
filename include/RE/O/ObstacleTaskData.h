#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSWin32TaskletData.h"

namespace RE
{
	class BSNavmesh;
	class BSNavmeshObstacleData;
	struct BSNavmeshInfo;

	struct ObstacleTaskOperation
	{
	public:
		// members
		BSNavmeshObstacleData* target;  // 00 - ref-counted
		std::uint32_t          type;    // 08 - 0x10/0x11 add, 0x20/0x21 remove, 0x30 close door, 0x40 open door
		std::uint32_t          result;  // 0C
		BSNavmesh*             ref;     // 10 - ref-counted
	};
	static_assert(sizeof(ObstacleTaskOperation) == 0x18);

	struct NavmeshEdgeRef
	{
	public:
		// members
		BSNavmeshInfo* info;      // 00
		std::uint16_t  triangle;  // 08
		std::uint16_t  pad0A;     // 0A
		std::uint32_t  pad0C;     // 0C
		std::int32_t   edge;      // 10
		std::uint32_t  pad14;     // 14
	};
	static_assert(sizeof(NavmeshEdgeRef) == 0x18);

	class ObstacleTaskData : public BSWin32TaskletData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ObstacleTaskData;
		inline static constexpr auto VTABLE = VTABLE_ObstacleTaskData;

		// override (BSWin32TaskletData)
		~ObstacleTaskData() override;  // 00

		bool Commit()
		{
			using func_t = bool(ObstacleTaskData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29796, 30613) };
			return func(this);
		}

		// members
		BSNavmeshInfo*                  navmeshInfo;      // 28
		BSNavmesh*                      originalNavmesh;  // 30
		BSNavmesh*                      workingNavmesh;   // 38 - clone made by Process; null when the navmesh was not loaded
		BSTArray<ObstacleTaskOperation> operations;       // 40
		BSTArray<NavmeshEdgeRef>        cloneEdges;       // 58
		BSTArray<NavmeshEdgeRef>        originalEdges;    // 70
		bool                            dirty;            // 88
		std::uint8_t                    pad89[7];         // 89
	};
	static_assert(sizeof(ObstacleTaskData) == 0x90);
}

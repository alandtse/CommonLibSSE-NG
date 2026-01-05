#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTArray.h"

namespace RE
{
	class NiAVObject;

	class NiPick
	{
	public:
		class Record
		{
		public:
			NiPointer<NiAVObject> object;     // 00
			NiPoint3              intersect;  // 08
			NiPoint3              normal;     // 14
			float                 distance;   // 20
			std::uint32_t         pad24;      // 24
		};
		static_assert(sizeof(Record) == 0x28);

		enum class PickType
		{
			FIND_ALL = 0,
			FIND_FIRST = 1,
		};

		enum class SortType
		{
			SORT = 0,
			NO_SORT = 1,
		};

		enum class IntersectType
		{
			BOUND_INTERSECT = 0,
			TRIANGLE_INTERSECT = 1,
		};

		enum class CoordinateType
		{
			MODEL_COORDINATES = 0,
			WORLD_COORDINATES = 1,
		};

		REX::EnumSet<PickType, std::uint32_t>       pickType;            // 00
		REX::EnumSet<SortType, std::uint32_t>       sortType;            // 04
		REX::EnumSet<IntersectType, std::uint32_t>  intersectType;       // 08
		REX::EnumSet<CoordinateType, std::uint32_t> coordinateType;      // 0C
		bool                                        frontOnly;           // 10
		bool                                        observeAppCullFlag;  // 11
		std::uint8_t                                pad12[6];            // 12
		NiPointer<NiAVObject>                       root;                // 18
		NiTScrapArray<Record*>                      pickResults;         // 20
		std::uint64_t                               unk38;               // 38
		std::uint64_t                               unk40;               // 40
		std::uint8_t                                unk48;               // 48
		bool                                        returnNormal;        // 49
		std::uint8_t                                pad4A[6];            // 4A
	};
	static_assert(sizeof(NiPick) == 0x50);  // It isn't clear whether this is the actual size
}

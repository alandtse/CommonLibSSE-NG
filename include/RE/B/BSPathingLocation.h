#pragma once

#include "RE/B/BSPathingCell.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	struct BSNavmeshInfo;

	class BSPathingLocation
	{
	public:
		// members
		NiPoint3                       location;          // 00
		BSNavmeshInfo*                 navMeshInfo;       // 10
		BSTArray<BSNavmeshInfo*>*      navMeshInfoArray;  // 18
		BSTSmartPointer<BSPathingCell> pathingCell;       // 20
		std::uint16_t                  triangle;          // 28
		std::uint8_t                   flags;             // 2A
		std::uint8_t                   clientData;        // 2B
	};
	static_assert(sizeof(BSPathingLocation) == 0x30);
}

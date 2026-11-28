#pragma once

namespace RE
{
	// Page pool of AStarNode: 0xC008-byte pages of 0x200 nodes with the next page pointer at +0xC000.
	struct AStarNodePool
	{
	public:
		// members
		void*         firstPage;       // 00
		void*         tailLink;        // 08
		void*         curPage;         // 10
		void*         freePages;       // 18
		void*         cursor;          // 20
		void*         firstPageSaved;  // 28
		std::uint32_t nodeCount;       // 30
		std::uint8_t  pad34[12];       // 34
	};
	static_assert(sizeof(AStarNodePool) == 0x40);
}

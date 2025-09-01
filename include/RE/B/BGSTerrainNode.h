#pragma once

#include "RE/B/BGSDistantTreeBlock.h"
#include "RE/B/BGSTerrainBlock.h"

namespace RE
{
	class BGSTerrainManager;
	class BGSObjectBlock;

	class BGSTerrainNode
	{
	public:
		template <class T>
		struct Layer
		{
			Layer*   parent;  // 00
			uint32_t unk08;   // 08
			uint32_t flags;   // 0C
			uint64_t unk10;   // 10
			uint64_t unk18;   // 18
			uint64_t unk20;   // 20
			T*       block;   // 28
		};

		enum class Flag
		{
			kInActiveGrid = 0x4000,
			kInLargeRefGrid = 0x8000,
			kLODLevel4 = 0x80000,
			kLODLevel8 = 0x100000,
			kLODLevel16 = 0x200000,
			kLODLevel32 = 0x400000,
			kLODLevel64 = 0x800000,
			kLODLevel128 = 0x1000000,
			kLODLevel256 = 0x2000000,
			kLODLevel512 = 0x4000000
		};

		// members
		BGSTerrainManager*          manager;      // 00
		Layer<BGSTerrainBlock>*     terrain;      // 08
		Layer<BGSObjectBlock>*      objects;      // 10
		Layer<BGSDistantTreeBlock>* trees;        // 18
		Layer<BGSTerrainBlock>*     mapTerrain;   // 20
		Layer<BGSObjectBlock>*      mapObjects;   // 28
		BGSTerrainNode* (*children)[4];           // 30
		int64_t                           unk38;  // 38
		REX::EnumSet<Flag, std::uint32_t> flags;  // 40
		int32_t                           unk44;  // 44 - more flags
		int16_t                           x;      // 48
		int16_t                           y;      // 4A
		int32_t                           unk4C;  // 4C

		int32_t GetLODLevel() const { return flags.underlying() >> 21 & 0x3FC; }

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSTerrainNode) == 0x50);
}

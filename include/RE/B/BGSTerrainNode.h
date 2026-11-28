#pragma once

#include "RE/B/BGSDistantTreeBlock.h"
#include "RE/B/BGSTerrainBlock.h"

namespace RE
{
	class TESObjectCELL;
	class NiPoint3;
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
			kLandHgtAltered = 0x1,
			kLandClrAltered = 0x2,
			kLandTexAltered = 0x4,
			kLandLoaded = 0x8,
			kShaderLandTextureCount = 0x8,
			kLandGoodNormals = 0x10,
			kBlocksize = 0x10,
			kLandHiresHeightfield = 0x20,
			kLandSize = 0x21,
			kLandDataAltered = 0x27,
			kTilesPerBlock = 0x100,
			kTrisPerBlock = 0x200,
			kTriStripIndexCount = 0x3FD,  // TRISTRIPINDEXCOUNT
			kLandRemapped = 0x400,
			kLandArea = 0x441,
			kHalfLand = 0x800,
			kFullLand = 0x1000,
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

		std::uint32_t GetLODLevel() const { return (nodeState.underlying() >> 21) & 0x3FC; }

		bool ContainsPoint(const NiPoint3& a_position) const
		{
			using func_t = bool(const BGSTerrainNode*, const NiPoint3&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(31055, 31842) };
			return func(this, a_position);
		}

		void UpdateGridFlags()
		{
			using func_t = void(BGSTerrainNode*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(31054, 31841) };
			func(this);
		}

		float GetSquaredDistanceToPoint(const NiPoint3& a_position) const
		{
			using func_t = float(const BGSTerrainNode*, const NiPoint3&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(31080, 31871) };
			return func(this, a_position);
		}

		void UpdateRecurse(const NiPoint3& a_viewPos, TESObjectCELL* a_cell, std::uint32_t a_flags)
		{
			using func_t = void(BGSTerrainNode*, const NiPoint3&, TESObjectCELL*, std::uint32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(31048, 31835) };
			func(this, a_viewPos, a_cell, a_flags);
		}

		bool UpdateTerrainLayer(const NiPoint3& a_viewPos, bool a_arg2, bool a_arg3)
		{
			using func_t = bool(BGSTerrainNode*, const NiPoint3&, bool, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(31049, 31836) };
			return func(this, a_viewPos, a_arg2, a_arg3);
		}

		bool UpdateObjectLayer(const NiPoint3& a_viewPos, bool a_arg2, bool a_arg3, bool a_arg4, bool a_arg5)
		{
			using func_t = bool(BGSTerrainNode*, const NiPoint3&, bool, bool, bool, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(31050, 31837) };
			return func(this, a_viewPos, a_arg2, a_arg3, a_arg4, a_arg5);
		}

		bool UpdateTreeLayer(const NiPoint3& a_viewPos, bool a_arg2, bool a_arg3)
		{
			using func_t = bool(BGSTerrainNode*, const NiPoint3&, bool, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(31051, 31838) };
			return func(this, a_viewPos, a_arg2, a_arg3);
		}

		void UnloadLayers(std::uint32_t a_layerMask)
		{
			using func_t = void(BGSTerrainNode*, std::uint32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(31052, 31839) };
			func(this, a_layerMask);
		}

		void SwitchToMapLayersRecurse()
		{
			using func_t = void(BGSTerrainNode*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(31062, 31853) };
			func(this);
		}

		void SwitchFromMapLayersRecurse()
		{
			using func_t = void(BGSTerrainNode*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(31063, 31854) };
			func(this);
		}

		void LoadMapLayersRecurse()
		{
			using func_t = void(BGSTerrainNode*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(31064, 31855) };
			func(this);
		}

		void SetVisibleRecurse(bool a_visible)
		{
			using func_t = void(BGSTerrainNode*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(31065, 31857) };
			func(this, a_visible);
		}

		void CreateChildren(std::uint32_t a_level)
		{
			using func_t = void(BGSTerrainNode*, std::uint32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(31068, 31860) };
			func(this, a_level);
		}

		bool ShouldSplitForTerrain(const NiPoint3& a_viewPos)
		{
			using func_t = bool(BGSTerrainNode*, const NiPoint3&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(31069, 31861) };
			return func(this, a_viewPos);
		}

		bool ShouldSplitForObjects(const NiPoint3& a_viewPos)
		{
			using func_t = bool(BGSTerrainNode*, const NiPoint3&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(31070, 31862) };
			return func(this, a_viewPos);
		}

		bool IsVisibleFromCell(TESObjectCELL* a_cell, bool a_centerCellOnly)
		{
			using func_t = bool(BGSTerrainNode*, TESObjectCELL*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(31073, 31865) };
			return func(this, a_cell, a_centerCellOnly);
		}

		// members
		BGSTerrainManager*          manager;           // 00
		Layer<BGSTerrainBlock>*     terrain;           // 08
		Layer<BGSObjectBlock>*      objects;           // 10
		Layer<BGSDistantTreeBlock>* trees;             // 18
		Layer<BGSTerrainBlock>*     mapTerrain;        // 20
		Layer<BGSObjectBlock>*      mapObjects;        // 28
		BGSTerrainNode* (*children)[4];                // 30
		BGSTerrainNode*                   parent;      // 38
		REX::EnumSet<Flag, std::uint32_t> nodeState;   // 40
		std::uint32_t                     nodeNumber;  // 44
		std::int16_t                      baseCellX;   // 48
		std::int16_t                      baseCellY;   // 4A
		std::uint32_t                     pad4C;       // 4C
	};
	static_assert(sizeof(BGSTerrainNode) == 0x50);
}

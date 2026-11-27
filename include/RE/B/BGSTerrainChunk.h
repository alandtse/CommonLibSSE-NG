#pragma once

#include "RE/B/BSGeometry.h"
#include "RE/B/BSMultiBoundNode.h"
#include "RE/B/BSStream.h"

namespace RE
{
	class BGSTerrainNode;

	class BGSTerrainChunk
	{
	public:
		BGSTerrainChunk(BGSTerrainNode* a_node, BSStream& a_stream, std::int32_t a_cellX, std::int32_t a_cellY);
		~BGSTerrainChunk();

		static void           AttachWater(bool a_attach);
		static std::uint32_t& GetChunkCount();  // increased in ctor, decreased in dtor

		void Attach();
		void Detach();
		void Prepare();

		void Hide()
		{
			using func_t = void(BGSTerrainChunk*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(30942, 31745) };
			func(this);
		}

		void Show()
		{
			using func_t = void(BGSTerrainChunk*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(30943, 31746) };
			func(this);
		}

		static std::int32_t QueueLoad(void*& a_handle, BGSTerrainNode* a_node, std::uint32_t a_level, std::int16_t a_x, std::int16_t a_y)
		{
			using func_t = std::int32_t(void*&, BGSTerrainNode*, std::uint32_t, std::int16_t, std::int16_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(30930, 31733) };
			return func(a_handle, a_node, a_level, a_x, a_y);
		}

		static std::int32_t Load(void*& a_handle, BGSTerrainNode* a_node, std::uint32_t a_level, std::int16_t a_x, std::int16_t a_y)
		{
			using func_t = std::int32_t(void*&, BGSTerrainNode*, std::uint32_t, std::int16_t, std::int16_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(30931, 31734) };
			return func(a_handle, a_node, a_level, a_x, a_y);
		}

		static void SetAllMenuScreenFlag(bool a_set)
		{
			using func_t = void(bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(30940, 31743) };
			func(a_set);
		}

		static void LoadNoiseTexture()
		{
			using func_t = void();
			static REL::Relocation<func_t> func{ RELOCATION_ID(30944, 31747) };
			func();
		}

		static void ReleaseNoiseTexture(bool a_release)
		{
			using func_t = void(bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(30945, 31748) };
			func(a_release);
		}

		// members
		BGSTerrainNode*             terrainNode;    // 00
		NiPointer<BSGeometry>       landMesh;       // 08
		NiPointer<BSMultiBoundNode> waterNode;      // 10
		NiPointer<BSMultiBoundNode> chunk;          // 18
		bool                        doneLoading;    // 20
		bool                        attached;       // 21
		bool                        waterAttached;  // 22
		bool                        prepared;       // 23
		std::uint32_t               pad24;          // 24

	private:
		BGSTerrainChunk* Ctor(BGSTerrainNode* a_node, BSStream& a_stream, std::int32_t a_cellX, std::int32_t a_cellY);
		void             Dtor();
	};
	static_assert(sizeof(BGSTerrainChunk) == 0x28);
}

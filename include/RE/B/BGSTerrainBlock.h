#pragma once

#include "RE/B/BSTriShape.h"

namespace RE
{
	class BGSTerrainNode;

	class BGSTerrainBlock
	{
	public:
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

		void Detach()
		{
			using func_t = void(BGSTerrainBlock*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(30936, 31739) };
			func(this);
		}

		static void SetAllMenuScreenFlag(bool a_set)
		{
			using func_t = void(bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(30940, 31743) };
			func(a_set);
		}

		void Hide()
		{
			using func_t = void(BGSTerrainBlock*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(30942, 31745) };
			func(this);
		}

		void Show()
		{
			using func_t = void(BGSTerrainBlock*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(30943, 31746) };
			func(this);
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
		BGSTerrainNode*   node;           // 00
		BSTriShape*       land;           // 08
		BSMultiBoundNode* water;          // 10
		BSMultiBoundNode* chunk;          // 18
		bool              loaded;         // 20
		bool              attached;       // 21
		bool              waterAttached;  // 22
		bool              unk23;          // 23
		uint32_t          unk24;          // 24
		uint32_t          unk28;          // 28
		uint32_t          unk2C;          // 2C
		uint64_t          unk30;          // 30
		uint64_t          unk38;          // 38
		uint64_t          unk40;          // 40
		uint64_t          unk48;          // 48
		uint64_t          unk50;          // 50
		uint64_t          unk58;          // 58
		uint64_t          unk60;          // 60
		uint64_t          unk68;          // 68
		uint64_t          unk70;          // 70
		uint64_t          unk78;          // 78
		bool              unk80;          // 80
		bool              unk81;          // 81
		bool              unk82;          // 82
		bool              unk83;          // 83
	};
}

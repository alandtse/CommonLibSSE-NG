#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BeamProjectile.h"
#include "RE/E/Explosion.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BGSProjectile;

	// Explosion is truncated in multi-runtime builds, so the sink and members are only reachable through the accessors there.
	class ChainExplosion :
#if defined(EXCLUSIVE_SKYRIM_SE) || defined(EXCLUSIVE_SKYRIM_VR) || defined(EXCLUSIVE_SKYRIM_AE)
		public Explosion,                               // 00
		public BSTEventSink<BeamProjectileImpactEvent>  // 140
#else
		public Explosion  // 00
#endif
	{
	public:
		inline static constexpr auto RTTI = RTTI_ChainExplosion;
		inline static constexpr auto VTABLE = VTABLE_ChainExplosion;

		~ChainExplosion() override;  // 00

		// override (TESObjectREFR)
		void SaveGame(BGSSaveFormBuffer* a_buf) override;        // 0E
		void LoadGame(BGSLoadFormBuffer* a_buf) override;        // 0F
		void InitLoadGame(BGSLoadFormBuffer* a_buf) override;    // 10
		void FinishLoadGame(BGSLoadFormBuffer* a_buf) override;  // 11
		void Revert(BGSLoadFormBuffer* a_buf) override;          // 12

#ifndef SKYRIM_CROSS_VR
		// override (Explosion)
		void Initialize() override;           // A2
		void Update(float a_delta) override;  // A3
		void FindTargets() override;          // A4 - { return; }
#endif

#if defined(EXCLUSIVE_SKYRIM_SE) || defined(EXCLUSIVE_SKYRIM_VR) || defined(EXCLUSIVE_SKYRIM_AE)
		// override (BSTEventSink<BeamProjectileImpactEvent>)
		BSEventNotifyControl ProcessEvent(const BeamProjectileImpactEvent* a_event, BSTEventSource<BeamProjectileImpactEvent>* a_eventSource) override;  // 01
#endif

		RUNTIME_CAST_ACCESSOR_VERSIONED(BSTEventSink<BeamProjectileImpactEvent>, AsImpactEventSink, SKSE::RUNTIME_SSE_1_6_629, 0x140, 0x148);

		struct CHAIN_EXPLOSION_RUNTIME_DATA
		{
#define CHAIN_EXPLOSION_RUNTIME_DATA_CONTENT                 \
	NiPoint3              nextOrigin;     /* 148 */          \
	BSTArray<ActorHandle> pastTargets;    /* 158 */          \
	ActorHandle           currentTarget;  /* 170 */          \
	std::uint32_t         unk174;         /* 174 - handle */ \
	BGSProjectile*        projectileBase; /* 178 */          \
	std::uint64_t         unk180;         /* 180 */          \
	std::uint32_t         unk188;         /* 188 */          \
	float                 timer;          /* 18C */          \
	float                 effectiveness;  /* 190 */          \
	float                 unk194;         /* 194 */          \
	bool                  waiting;        /* 198 */          \
	std::uint8_t          pad199[7];      /* 199 */

			CHAIN_EXPLOSION_RUNTIME_DATA_CONTENT
		};

		RUNTIME_DATA_ACCESSOR_VERSIONED_EX(CHAIN_EXPLOSION_RUNTIME_DATA, GetChainExplosionRuntimeData, SKSE::RUNTIME_SSE_1_6_629, 0x148, 0x150);
		// members
#if defined(EXCLUSIVE_SKYRIM_SE) || defined(EXCLUSIVE_SKYRIM_VR) || defined(EXCLUSIVE_SKYRIM_AE)
		CHAIN_EXPLOSION_RUNTIME_DATA_CONTENT;  // 148 (SE/VR), 150 (AE)
#endif

	private:
		TES_HEAP_REDEFINE_NEW();
	};
	STATIC_ASSERT_SIZE(ChainExplosion, 0x1A0, 0x1A8, 0x1A0);
}
#undef CHAIN_EXPLOSION_RUNTIME_DATA_CONTENT

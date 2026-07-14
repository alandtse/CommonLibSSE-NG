#pragma once

#include "RE/N/NiNode.h"

namespace RE
{
	class BSMasterParticleSystem;

	class BSParticleSystemManager : public NiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSParticleSystemManager;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSParticleSystemManager;
		inline static constexpr auto VTABLE = VTABLE_BSParticleSystemManager;

		~BSParticleSystemManager() override;  // 00

		// override (NiNode)
		NiObject* CreateClone(NiCloningProcess& a_cloning) override;  // 17
#ifndef SKYRIM_CROSS_VR
		void AttachChild(NiAVObject* a_child, bool a_firstAvail = false) override;             // 35
		void DetachChild1(NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut) override;    // 37
		void DetachChild2(NiAVObject* a_child) override;                                       // 38
		void DetachChildAt1(std::uint32_t a_idx, NiPointer<NiAVObject>& a_childOut) override;  // 39
		void DetachChildAt2(std::uint32_t a_idx) override;                                     // 3A
		void SetAt2(std::uint32_t a_idx, NiAVObject* a_child) override;                        // 3C
#endif

		// add

		// Thread-safe (mutex-guarded) registry of BSMasterParticleSystem entries.
		bool                    IsValidMasterParticleSystem(std::uint32_t a_index);
		BSMasterParticleSystem* GetMasterParticleSystemAt(std::uint32_t a_index);

	private:
		BSMasterParticleSystem** masterParticleSystems;          // 128 / 150 - BSTArray<BSMasterParticleSystem*> data
		std::uint32_t            masterParticleSystemsCapacity;  // 130 / 158
		std::uint32_t            unk134;                         // 134 / 15C - pad
		std::uint32_t            masterParticleSystemsCount;     // 138 / 160
		std::uint32_t            unk13C;                         // 13C / 164 - pad
		void*                    unk140;                         // 140 / 168 - not yet reverse engineered
	};
	STATIC_ASSERT_SIZE(BSParticleSystemManager, 0x148, 0x148, 0x170, SIZE_UNDEFINED, 0x148);
}

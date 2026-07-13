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
	};
#if !defined(SKYRIM_CROSS_VR) || !defined(ENABLE_SKYRIM_VR)
	static_assert(sizeof(BSParticleSystemManager) == 0x148);
#endif
}

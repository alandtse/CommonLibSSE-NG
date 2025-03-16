#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiNode.h"

namespace RE
{
	class BSLight;
	class BSPortal;

	class BSPortalSharedNode : public NiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPortalSharedNode;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSPortalSharedNode;
		inline static constexpr auto VTABLE = VTABLE_BSPortalSharedNode;

		~BSPortalSharedNode() override;  // 00

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
#ifndef SKYRIM_CROSS_VR
		// The following are virtual functions past the point where VR compatibility breaks.
		void OnVisible(NiCullingProcess& a_process) override;  // 34
#endif
		// members
		BSTArray<BSLight*> lights;  // 128, VR 150
		BSPortal*          portal;  // 140, VR 168
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BSPortalSharedNode) == 0x148);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BSPortalSharedNode) == 0x170);
#else
	static_assert(sizeof(BSPortalSharedNode) == 0x130);
#endif
}

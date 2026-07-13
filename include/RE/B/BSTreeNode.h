#pragma once

#include "RE/B/BSLeafAnimNode.h"

namespace RE
{
	class BSTreeNode : public BSLeafAnimNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSTreeNode;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSTreeNode;
		inline static constexpr auto VTABLE = VTABLE_BSTreeNode;

		~BSTreeNode() override;  // 00

		// override (BSLeafAnimNode)
		NiObject* CreateClone(NiCloningProcess& a_cloning) override;   // 17
		void      LoadBinary(NiStream& a_stream) override;             // 18
		void      LinkObject(NiStream& a_stream) override;             // 19
		void      SaveBinary(NiStream& a_stream) override;             // 1B
		void      ProcessClone(NiCloningProcess& a_cloning) override;  // 1D
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		void OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex) override;  // 34
#elif defined(EXCLUSIVE_SKYRIM_VR)
		// VR has different vtable layout - this function doesn't exist as a virtual here.
#else
		void OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex);  // 34 - Multi-runtime (non-virtual)
#endif

		// add

		// Computes an index-based LOD blend ratio for tree canopy rendering.
		float ComputeTreeLODBlend();
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BSTreeNode) == 0x1B8);
#endif
}

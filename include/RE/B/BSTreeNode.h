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
		void OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex) override;  // SE/AE 34
#elif defined(EXCLUSIVE_SKYRIM_VR)
		void OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex) override;  // VR 35
#else
		// VR inserts an extra vtable entry (NiAVObject::ApplyLocalTransformToWorld) ahead of this
		// slot, so a single compile-time ordinal can't address both runtimes; resolve the real
		// per-runtime slot via RelocateVirtual instead.
		void OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex);  // SE/AE 34, VR 35
#endif

		// add

		// Computes an index-based LOD blend ratio for tree canopy rendering.
		float ComputeTreeLODBlend();

	private:
		std::byte unk170[0x48];  // 170 - not yet reverse engineered
	};
	STATIC_ASSERT_SIZE(BSTreeNode, 0x1B8, 0x1B8, 0x1E0, SIZE_UNDEFINED, 0x1B8);
}

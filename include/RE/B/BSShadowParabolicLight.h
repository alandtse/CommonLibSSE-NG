#pragma once

#include "RE/B/BSShadowLight.h"

namespace RE
{
	class BSShadowParabolicLight : public BSShadowLight
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSShadowParabolicLight;
		inline static constexpr auto VTABLE = VTABLE_BSShadowParabolicLight;

		~BSShadowParabolicLight() override;  // 00

		// override (BSShadowLight)
		bool IsParabolicLight() override;                                                                                      // 07 GetIsParabolicLight
		bool IsOmnidirectionalLight() override;                                                                                // 08 GetIsOmniLight
		void Cull(uint32_t& globalShadowLightCount, uint32_t shadowMaskChannel, NiPointer<NiAVObject> cullingScene) override;  // 09 Accumulate
		void RenderShadowmaps() override;                                                                                      // 0A Render
		void Reset() override;                                                                                                 // 0C ClearShadowMapData
		void Unk_0D() override;                                                                                                // 0D
		bool Unk_0E() override;                                                                                                // 0E
		bool SetFrameCamera(const NiCamera& frameCamera) override;                                                             // 10 UpdateCamera

	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BSShadowParabolicLight) == 0x560);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BSShadowParabolicLight) == 0x5C0);
#else
	static_assert(sizeof(BSShadowParabolicLight) == 0x148);
#endif
}

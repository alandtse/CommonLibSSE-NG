#pragma once

#include "RE/B/BSShadowLight.h"

namespace RE
{
	class BSShadowFrustumLight : public BSShadowLight
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSShadowFrustumLight;
		inline static constexpr auto VTABLE = VTABLE_BSShadowFrustumLight;

		~BSShadowFrustumLight() override;  // 00

		// override (BSShadowLight)
		bool AreFocusShadowsSupported() override;                                                                              // 04
		bool IsSpotLight() override;                                                                                           // 05 GetIsFrustumLight
		void Cull(uint32_t& globalShadowLightCount, uint32_t shadowMaskChannel, NiPointer<NiAVObject> cullingScene) override;  // 09 Accumulate
		void RenderShadowmaps() override;                                                                                      // 0A Render
		bool SetFrameCamera(const NiCamera& frameCamera) override;                                                             // 10 UpdateCamera

		// members
		float semiWidth;     // 560 xFOV
		float semiHeight;    // 564 yFOV
		float falloff;       // 568
		float nearDistance;  // 56C
		float farDistance;   // 570
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BSShadowFrustumLight) == 0x578);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BSShadowFrustumLight) == 0x5D8);
#else
	static_assert(sizeof(BSShadowFrustumLight) == 0x160);
#endif

}

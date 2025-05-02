#pragma once

#include "RE/B/BSShadowLight.h"

namespace RE
{
	class BSShadowDirectionalLight : public BSShadowLight
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSShadowDirectionalLight;
		inline static constexpr auto VTABLE = VTABLE_BSShadowDirectionalLight;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                            \
	NiPoint3                              lightDirection;             /* 560, VR 5C0 */ \
	NiPoint3                              previousLightDirection;     /* 56C, VR 5CC */ \
	NiPointer<NiCamera>                   cullingCamera;              /* 578, VR 5D8 */ \
	BSTArray<NiPointer<BSCullingProcess>> cullingProcesses;           /* 580, VR 5E0 */ \
	float                                 startSplitDistances[3];     /* 598, VR 5F8 */ \
	float                                 endSplitDistances[3];       /* 5A4, VR 604 */ \
	float                                 lightDirectionUpdateTimer;  /* 5B0, VR 610 */ \
	bool                                  cameraShifted;              /* 5B4, VR 614 */
			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x58);

		~BSShadowDirectionalLight() override;  // 00

		// override (BSShadowLight)
		bool AreFocusShadowsSupported() override;                                                                              // 04
		bool IsDirectionalLight() override;                                                                                    // 06
		void Cull(uint32_t& globalShadowLightCount, uint32_t shadowMaskChannel, NiPointer<NiAVObject> cullingScene) override;  // 09
		void RenderShadowmaps() override;                                                                                      // 0A
		void Reset() override;                                                                                                 // 0C
		void Unk_0D() override;                                                                                                // 0D
		bool Unk_0E() override;                                                                                                // 0E
		void Unk_0F() override;                                                                                                // 0F
		bool SetFrameCamera(const NiCamera& frameCamera) override;                                                             // 10

		[[nodiscard]] inline RUNTIME_DATA& GetShadowDirectionalLightRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x560, 0x5C0);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetShadowDirectionalLightRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x560, 0x5C0);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT; // 560, VR 5C0
#endif 
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BSShadowDirectionalLight) == 0x5B8);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BSShadowDirectionalLight) == 0x618);
#else
	static_assert(sizeof(BSShadowDirectionalLight) == 0x148);
#endif
}
#undef RUNTIME_DATA_CONTENT

#pragma once

#include "RE/B/BSLight.h"
#include "RE/B/BSShaderRenderTargets.h"
#include "RE/N/NiFrustumPlanes.h"
#include "RE/N/NiRect.h"

#include "REX/W32/D3D.h"

namespace RE
{
	class BSShaderAccumulator;
	class NiCamera;

	class BSShadowLight : public BSLight
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSShadowLight;
		inline static constexpr auto VTABLE = VTABLE_BSShadowLight;

		struct ShadowmapDescriptor
		{
#define SHADOWMAPDESCRIPTOR_CONTENT                                                         \
	REX::W32::XMFLOAT4X4           lightTransform;    /* 00 */                              \
	NiPointer<NiCamera>            camera;            /* 40 */                              \
	NiPointer<BSShaderAccumulator> shaderAccumulator; /* 48, VR 50 */                       \
	uint32_t                       unk50;             /* 50, VR 60 = -1 */                  \
	RENDER_TARGET_DEPTHSTENCIL     renderTarget;      /* 54, VR 64 */                       \
	uint32_t                       shadowmapIndex;    /* 58, VR D0 - guess */               \
	NiFrustumPlanes                clipPlanes;        /* 5C, VR 70 was NiPlane planes[6] */ \
	std::uint32_t                  unitsPerTexel;     /* CC */                              \
	NiRect<int32_t>                port;              /* D0, VR E8 shadowMapRect */         \
	BSCullingProcess*              cullingProcess;    /* E0, VR F8 */                       \
	bool                           clearRenderTarget; /* E8, VR 100 was uint16_t flags */
            SHADOWMAPDESCRIPTOR_CONTENT;
		};
		static_assert(sizeof(ShadowmapDescriptor) == 0xF0);
		static_assert(offsetof(ShadowmapDescriptor, shaderAccumulator) == 0x48);
		static_assert(offsetof(ShadowmapDescriptor, renderTarget) == 0x54);
		static_assert(offsetof(ShadowmapDescriptor, clipPlanes) == 0x5C);
		static_assert(offsetof(ShadowmapDescriptor, shadowmapIndex) == 0x58);
		static_assert(offsetof(ShadowmapDescriptor, port) == 0xD0);
		static_assert(offsetof(ShadowmapDescriptor, cullingProcess) == 0xE0);
		static_assert(offsetof(ShadowmapDescriptor, clearRenderTarget) == 0xE8);

		struct ShadowmapDescriptorVR
		{
#define SHADOWMAPDESCRIPTOR_CONTENT_VR                                              \
	REX::W32::XMFLOAT4X4           lightTransform;    /* 00 */                      \
	NiPointer<NiCamera>            camera;            /* 40 */                      \
	uint64_t                       unkVR48;           /* VR 48 */                   \
	NiPointer<BSShaderAccumulator> shaderAccumulator; /* 48, VR 50 */               \
	uint64_t                       unkVR58;           /* VR 58 */                   \
	uint32_t                       unk50;             /* 50, VR 60 = -1 */          \
	RENDER_TARGET_DEPTHSTENCIL     renderTarget;      /* 54, VR 64 */               \
	uint64_t                       unkVR68;           /* VR 68 = -1 */              \
	NiFrustumPlanes                clipPlanes;        /* 5C, VR 70 */               \
	uint32_t                       shadowmapIndex;    /* C8, VR E0 - guess*/        \
	std::uint32_t                  unitsPerTexel;     /* CC */                      \
	NiRect<int32_t>                port;              /* D0, VR E8 shadowMapRect */ \
	BSCullingProcess*              cullingProcess;    /* E0, VR F8 */               \
	bool                           clearRenderTarget; /* E8, VR 100 was uint16_t flags */
            SHADOWMAPDESCRIPTOR_CONTENT_VR;
		};
		static_assert(sizeof(ShadowmapDescriptorVR) == 0x108);
		static_assert(offsetof(ShadowmapDescriptorVR, shaderAccumulator) == 0x50);
		static_assert(offsetof(ShadowmapDescriptorVR, unkVR58) == 0x58);
		static_assert(offsetof(ShadowmapDescriptorVR, unk50) == 0x60);
		static_assert(offsetof(ShadowmapDescriptorVR, renderTarget) == 0x64);
		static_assert(offsetof(ShadowmapDescriptorVR, clipPlanes) == 0x70);
		static_assert(offsetof(ShadowmapDescriptorVR, shadowmapIndex) == 0xE0);
		static_assert(offsetof(ShadowmapDescriptorVR, port) == 0xE8);
		static_assert(offsetof(ShadowmapDescriptorVR, cullingProcess) == 0xF8);
		static_assert(offsetof(ShadowmapDescriptorVR, clearRenderTarget) == 0x100);

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                             \
	BSTArray<ShadowmapDescriptor>   shadowmapDescriptors;         /* 148 shadowMapDataList */            \
	ShadowmapDescriptor             focusShadowmapDescriptors[4]; /* 160 shadowMapData */                \
	uint32_t                        shadowLightIndex;             /* 520, VR 580 maskIndex */            \
	uint32_t                        accumulatedIndex;             /* 524, VR 584 */                      \
	BSTArray<NiPointer<NiAVObject>> cullingObjects;               /* 528, VR 588 sceneAccumArray */      \
	float                           shadowBiasScale;              /* 540, VR 5A0 */                      \
	NiRect<int32_t>                 port;                         /* 544, VR 5A4 projectedBoundingBox */ \
	uint32_t                        shadowSceneNodeIndex;         /* 554, VR 5B4 sceneGraphIndex*/       \
	bool                            drawFocusShadows;             /* 558, VR 5B8  */
            RUNTIME_DATA_CONTENT
		};

		struct RUNTIME_DATA_VR
		{
#define RUNTIME_DATA_CONTENT_VR                                                               \
	BSTArray<ShadowmapDescriptorVR> shadowmapDescriptors;         /* 148 shadowMapDataList */ \
	ShadowmapDescriptorVR           focusShadowmapDescriptors[4]; /* 160  shadowMapData*/     \
	uint32_t                        shadowLightIndex;             /* 520, VR 580 */           \
	uint32_t                        accumulatedIndex;             /* 524, VR 584 */           \
	BSTArray<NiPointer<NiAVObject>> cullingObjects;               /* 528, VR 588 */           \
	float                           shadowBiasScale;              /* 540, VR 5A0 */           \
	NiRect<int32_t>                 port;                         /* 544, VR 5A4 */           \
	uint32_t                        shadowSceneNodeIndex;         /* 554, VR 5B4 */           \
	bool                            drawFocusShadows;             /* 558, VR 5B8  */
            RUNTIME_DATA_CONTENT_VR
		};

		~BSShadowLight() override;  // 00

		// add
		virtual bool AreFocusShadowsSupported();                                                                                  // 04
		virtual bool IsSpotLight();                                                                                               // 05 GetIsFrustumLight in po3
		virtual bool IsDirectionalLight();                                                                                        // 06 GetIsDirectionalLight
		virtual bool IsParabolicLight();                                                                                          // 07 GetIsParabolicLight
		virtual bool IsOmnidirectionalLight();                                                                                    // 08 GetIsOmniLight
		virtual void Cull(uint32_t& globalShadowLightCount, uint32_t shadowMaskChannel, NiPointer<NiAVObject> cullingScene) = 0;  // 09 Accumulate
		virtual void RenderShadowmaps() = 0;                                                                                      // 0A Render
		virtual void SetShadowmapCount(uint32_t shadowmapCount);                                                                  // 0B SetShadowMapCount
		virtual void Reset();                                                                                                     // 0C ClearShadowMapData
		virtual void Unk_0D();                                                                                                    // 0D
		virtual bool Unk_0E();                                                                                                    // 0E
		virtual void Unk_0F();                                                                                                    // 0F
		virtual bool SetFrameCamera(const NiCamera& frameCamera) = 0;                                                             // 10 UpdateCamera

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x148, 0x148);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x148, 0x148);
		}

		[[nodiscard]] inline RUNTIME_DATA_VR& GetVRRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA_VR>(this, 0x148, 0x148);
		}

		[[nodiscard]] inline const RUNTIME_DATA_VR& GetVRRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA_VR>(this, 0x148, 0x148);
		}

		// members
		uint32_t shadowMapCount;  // 140 shadowMapIndex
		uint32_t unk144;          // 144
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		RUNTIME_DATA_CONTENT;  // 148, VR 148
#elif defined(EXCLUSIVE_SKYRIM_VR)
		RUNTIME_DATA_CONTENT_VR;  // 148, VR 148
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BSShadowLight) == 0x560);
	static_assert(offsetof(BSShadowLight, shadowLightIndex) == 0x520);
	static_assert(offsetof(BSShadowLight, accumulatedIndex) == 0x524);
	static_assert(offsetof(BSShadowLight, cullingObjects) == 0x528);
	static_assert(offsetof(BSShadowLight, shadowBiasScale) == 0x540);
	static_assert(offsetof(BSShadowLight, port) == 0x544);
	static_assert(offsetof(BSShadowLight, shadowSceneNodeIndex) == 0x554);
	static_assert(offsetof(BSShadowLight, drawFocusShadows) == 0x558);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BSShadowLight) == 0x5C0);
	static_assert(offsetof(BSShadowLight, shadowLightIndex) == 0x580);
	static_assert(offsetof(BSShadowLight, accumulatedIndex) == 0x584);
	static_assert(offsetof(BSShadowLight, cullingObjects) == 0x588);
	static_assert(offsetof(BSShadowLight, shadowBiasScale) == 0x5A0);
	static_assert(offsetof(BSShadowLight, port) == 0x5A4);
	static_assert(offsetof(BSShadowLight, shadowSceneNodeIndex) == 0x5B4);
	static_assert(offsetof(BSShadowLight, drawFocusShadows) == 0x5B8);
#else
	static_assert(sizeof(BSShadowLight) == 0x148);
#endif
}
#undef SHADOWMAPDESCRIPTOR_CONTENT
#undef SHADOWMAPDESCRIPTOR_CONTENT_VR
#undef RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA_CONTENT_VR

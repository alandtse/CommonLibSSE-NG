#pragma once

#include "RE/B/BSLight.h"
#include "RE/B/BSShaderRenderTargets.h"
#include "RE/N/NiFrustumPlanes.h"
#include "RE/N/NiRect.h"

#include "REL/RuntimeDataAccessors.h"
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
	bool                           clearRenderTarget; /* E8, VR 100 was uint16_t flags */   \
	bool                           unkE9;             /* E9 */
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
#define SHADOWMAPDESCRIPTOR_CONTENT_VR                                                    \
	REX::W32::XMFLOAT4X4           lightTransform;    /* 00 */                            \
	NiPointer<NiCamera>            camera;            /* 40 */                            \
	uint64_t                       unkVR48;           /* VR 48 */                         \
	NiPointer<BSShaderAccumulator> shaderAccumulator; /* 48, VR 50 */                     \
	uint64_t                       unkVR58;           /* VR 58 */                         \
	uint32_t                       unk50;             /* 50, VR 60 = -1 */                \
	RENDER_TARGET_DEPTHSTENCIL     renderTarget;      /* 54, VR 64 */                     \
	uint64_t                       unkVR68;           /* VR 68 = -1 */                    \
	NiFrustumPlanes                clipPlanes;        /* 5C, VR 70 */                     \
	uint32_t                       shadowmapIndex;    /* C8, VR E0 - guess*/              \
	std::uint32_t                  unitsPerTexel;     /* CC */                            \
	NiRect<int32_t>                port;              /* D0, VR E8 shadowMapRect */       \
	BSCullingProcess*              cullingProcess;    /* E0, VR F8 */                     \
	bool                           clearRenderTarget; /* E8, VR 100 was uint16_t flags */ \
	bool                           unkE9;             /* E9 */
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
#define RUNTIME_DATA_CONTENT                                                                     \
	BSTArray<ShadowmapDescriptor>   shadowmapDescriptors;         /* 148 shadowMapDataList */    \
	ShadowmapDescriptor             focusShadowmapDescriptors[4]; /* 160 shadowMapData */        \
	std::uint32_t                   maskIndex;                    /* 520 */                      \
	std::uint32_t                   accumulatedIndex;             /* 524 */                      \
	BSTArray<NiPointer<NiAVObject>> sceneAccumArray;              /* 528 sceneAccumArray */      \
	float                           shadowBiasScale;              /* 540 */                      \
	NiRect<std::uint32_t>           projectedBoundingBox;         /* 544 projectedBoundingBox */ \
	std::uint32_t                   sceneGraphIndex;              /* 554 */                      \
	bool                            drawFocusShadows;             /* 558 */                      \
	std::uint8_t                    pad559;                       /* 559 */                      \
	std::uint8_t                    pad55A;                       /* 55A */                      \
	std::uint32_t                   pad55B;                       /* 55B */
            RUNTIME_DATA_CONTENT
		};

		struct RUNTIME_DATA_VR
		{
#define RUNTIME_DATA_CONTENT_VR                                                                    \
	BSTArray<ShadowmapDescriptorVR> shadowmapDescriptors;         /* 148 shadowMapDataList (VR) */ \
	ShadowmapDescriptorVR           focusShadowmapDescriptors[4]; /* 160 shadowMapData (VR) */     \
	std::uint32_t                   maskIndex;                    /* 580 */                        \
	std::uint32_t                   accumulatedIndex;             /* 584 */                        \
	BSTArray<NiPointer<NiAVObject>> sceneAccumArray;              /* 588 */                        \
	float                           shadowBiasScale;              /* 5A0 */                        \
	NiRect<std::uint32_t>           projectedBoundingBox;         /* 5A4 */                        \
	std::uint32_t                   sceneGraphIndex;              /* 5B4 */                        \
	bool                            drawFocusShadows;             /* 5B8 */                        \
	std::uint8_t                    pad559;                       /* 5B9 */                        \
	std::uint8_t                    pad55A;                       /* 5BA */                        \
	std::uint32_t                   pad55B;                       /* 5BB */
            RUNTIME_DATA_CONTENT_VR
		};

		~BSShadowLight() override;  // 00

		// add
		virtual bool          GetIsFrustumOrDirectionalLight() = 0;                                                                                                      // 04
		virtual bool          GetIsFrustumLight();                                                                                                                       // 05
		virtual void          GetIsDirectionalLight();                                                                                                                   // 06
		virtual bool          GetIsParabolicLight();                                                                                                                     // 07
		virtual bool          GetIsOmniLight();                                                                                                                          // 08
		virtual void          Accumulate(std::uint32_t& a_globalShadowLightCount, std::uint32_t& a_shadowMaskChannel, const NiPointer<NiAVObject>& a_cullingScene) = 0;  // 09
		virtual void          Render() = 0;                                                                                                                              // 0A
		virtual void          SetShadowMapCount(std::uint32_t a_count);                                                                                                  // 0B
		virtual void          ClearShadowMapData();                                                                                                                      // 0C
		virtual std::uint32_t GetPassExtraParam(std::uint32_t a_accumFlag);                                                                                              // 0D
		virtual bool          GetNeedsClipPlanes();                                                                                                                      // 0E
		virtual void          UpdateClipPlanes(void* a_unk1, void* a_unk2);                                                                                              // 0F
		virtual bool          UpdateCamera(const NiCamera* a_viewCamera) = 0;                                                                                            // 10

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x148, 0x148);
		RUNTIME_DATA_ACCESSOR_EX(RUNTIME_DATA_VR, GetVRRuntimeData, 0x148, 0x148);
		// members
		std::uint32_t shadowMapCount;  // 140
		std::uint32_t unk144;          // 144
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		RUNTIME_DATA_CONTENT;  // 148, VR 148
#elif defined(EXCLUSIVE_SKYRIM_VR)
		RUNTIME_DATA_CONTENT_VR;  // 148, VR 148
#endif
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BSShadowLight) == 0x560);
	static_assert(offsetof(BSShadowLight, maskIndex) == 0x520);
	static_assert(offsetof(BSShadowLight, accumulatedIndex) == 0x524);
	static_assert(offsetof(BSShadowLight, sceneAccumArray) == 0x528);
	static_assert(offsetof(BSShadowLight, shadowBiasScale) == 0x540);
	static_assert(offsetof(BSShadowLight, projectedBoundingBox) == 0x544);
	static_assert(offsetof(BSShadowLight, sceneGraphIndex) == 0x554);
	static_assert(offsetof(BSShadowLight, drawFocusShadows) == 0x558);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BSShadowLight) == 0x5C0);
	static_assert(offsetof(BSShadowLight, maskIndex) == 0x580);
	static_assert(offsetof(BSShadowLight, accumulatedIndex) == 0x584);
	static_assert(offsetof(BSShadowLight, sceneAccumArray) == 0x588);
	static_assert(offsetof(BSShadowLight, shadowBiasScale) == 0x5A0);
	static_assert(offsetof(BSShadowLight, projectedBoundingBox) == 0x5A4);
	static_assert(offsetof(BSShadowLight, sceneGraphIndex) == 0x5B4);
	static_assert(offsetof(BSShadowLight, drawFocusShadows) == 0x5B8);
#else
	static_assert(sizeof(BSShadowLight) == 0x148);
#endif
}
#undef SHADOWMAPDESCRIPTOR_CONTENT
#undef SHADOWMAPDESCRIPTOR_CONTENT_VR
#undef RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA_CONTENT_VR

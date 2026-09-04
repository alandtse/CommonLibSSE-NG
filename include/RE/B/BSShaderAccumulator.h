#pragma once

#include "RE/N/NiAlphaAccumulator.h"
#include "RE/N/NiColor.h"
#include "REL/RuntimeDataAccessors.h"
#include "REX/REX/EnumSet.h"

namespace RE
{
	class BSBatchRenderer;
	class ShadowSceneNode;

	class BSShaderAccumulator : public NiAlphaAccumulator
	{
	public:
		enum class RENDER_MODE : std::uint32_t
		{
			kNormal = 0x00,
			kShadowMask = 0x0C,
			kShadowMapPlain = 0x0D,
			kShadowMapClamped = 0x0E,
			kShadowMapPb = 0x0F,
			kShadowMapCube = 0x11,
			kLocalMap = 0x12,
			kLodLandscapePass = 0x14,
			kWaterReflectionPass = 0x15,
			kBloodDecalPass = 0x16,
			kAlphaTransparencyShadowPass = 0x17,  // no-op on SE/AE/VR (verified: bare `return`)
			// Slot 0x18 dispatches unrelated code per runtime, so it's aliased below rather than
			// given one shared name.
			kSEEndFirstPersonView = 0x18,
			kAEResetQueuedShadowPassList = 0x18,
			kVRWorldSpaceUIPass = 0x18,
			kVolumetricLightingPass = 0x19,    // SE/AE; shared with kOcclusion's handler
			kVREndFirstPersonView = 0x19,      // VR: kSEEndFirstPersonView's behavior sits here instead
			kOcclusion = 0x1A,                 // SE/AE; VR shares this slot with 0x1B under a different handler
			kPrecipitationOcclusionMap = 0x1C  // SE/AE only -- VR has no handler at this slot
		};

		class SunOcclusionTest
		{
		public:
			void*         occlusionQuery;   // 00 BSGraphics::OcclusionQuery
			float         percentOccluded;  // 08
			std::uint32_t pixelCount;       // 0C
			std::uint32_t frameCount;       // 10
			bool          waiting;          // 14
		};
		static_assert(sizeof(SunOcclusionTest) == 0x18);

		inline static constexpr auto RTTI = RTTI_BSShaderAccumulator;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSShaderAccumulator;
		inline static constexpr auto VTABLE = VTABLE_BSShaderAccumulator;

		[[nodiscard]] static BSShaderAccumulator* GetCurrentAccumulator()
		{
			using func_t = decltype(&GetCurrentAccumulator);
			static REL::Relocation<func_t> func{ REL::RelocationID(98997, 105651) };
			return func();
		}

		~BSShaderAccumulator() override = default;  // 00

		// override (NiObject)
		[[nodiscard]] const NiRTTI* GetRTTI() const override;  // 02

		// override (NiAccumulator)
		void                            StartAccumulating(NiCamera* a_camera) override;                        // 25
		void                            FinishAccumulating() override;                                         // 26
		BSBatchRenderer::GeometryGroup* StartGroupingAlphas(NiBound* a_bound) override;                        // 28
		void                            StopGroupingAlphas(BSBatchRenderer::GeometryGroup* a_group) override;  // 29

		// add
		// Dispatches to one of ~30 renderMode-indexed handlers via the finishModeTable --
		// see BSShaderAccumulator::InitFinishModeTable and RENDER_MODE above.
		virtual void FinishAccumulatingDispatch(std::uint32_t RenderFlags);    // 2A
		virtual void FinishAccumulatingPostResolveDepth(std::uint32_t flags);  // 2B
		// No-op on SE/AE/VR (verified: bare `return`) -- not pure virtual, the class is
		// instantiated directly (real objects, not a base for further derivation).
		virtual void FinishAccumulatingSunGlint();  // 2C

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                             \
	std::uint8_t     unk58[0x4];               /* 58 */  \
	bool             unk5C;                    /* 5C */  \
	std::uint32_t    sunPixelCount;            /* 60 */  \
	bool             waitingForSunQuery;       /* 64 */  \
	float            percentSunOccludedStored; /* 68 */  \
	std::uint8_t     pad6C[0x4];               /* 6C */  \
	SunOcclusionTest sunOcclusionTests[3];     /* 70 */  \
	bool             unkB8;                    /* B8 */  \
	bool             unkB9;                    /* B9 */  \
	bool             unkBA;                    /* BA */  \
	std::uint8_t     padBB[0x5];               /* BB */  \
	std::uint8_t     unkC0[0x10];              /* C0 */  \
	std::uint8_t     fadeNodeMap[0x20];        /* D0 */  \
	std::uint8_t     unkF0[0x10];              /* F0 */  \
	void*            unk100;                   /* 100 */ \
	void*            unk108;                   /* 108 */ \
	std::uint32_t    unk110;                   /* 110 */ \
	bool             unk114;                   /* 114 */ \
	NiColorA         silhouetteColor;          /* 118 */ \
	bool             firstPerson;              /* 128 */ \
	bool             unk129;                   /* 129 */ \
	bool             unk12A;                   /* 12A */ \
	bool             unk12B;                   /* 12B */ \
	bool             drawDecals;               /* 12C */ \
	bool             unk12D;                   /* 12D */ \
	bool             unk12E;                   /* 12E */ \
	BSBatchRenderer* batchRenderer;            /* 130 */ \
	std::uint32_t    currentPass;              /* 138 */ \
	std::uint32_t    currentBucket;            /* 13C */ \
	bool             currentActive;            /* 140 */ \
	std::uint8_t     pad141[0x7];              /* 141 */ \
	ShadowSceneNode* activeShadowSceneNode;    /* 148 */ \
	RENDER_MODE      renderMode;               /* 150 */ \
	std::uint8_t     pad154[0x4];              /* 154 */ \
	void*            unk158;                   /* 158 */ \
	void*            unk160;                   /* 160 */ \
	std::uint32_t    unk168;                   /* 168 */ \
	NiPoint3         eyePosition;              /* 16C */ \
	std::uint8_t     unk178[0x8];              /* 178 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x128);

		// Fields through unk12E match RUNTIME_DATA exactly (unshifted on VR); the
		// insertion below is VR-only and still-unidentified, not verified content.
		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT                                   \
	std::uint8_t     unk58[0x4];               /* 58 */           \
	bool             unk5C;                    /* 5C */           \
	std::uint32_t    sunPixelCount;            /* 60 */           \
	bool             waitingForSunQuery;       /* 64 */           \
	float            percentSunOccludedStored; /* 68 */           \
	std::uint8_t     pad6C[0x4];               /* 6C */           \
	SunOcclusionTest sunOcclusionTests[3];     /* 70 */           \
	bool             unkB8;                    /* B8 */           \
	bool             unkB9;                    /* B9 */           \
	bool             unkBA;                    /* BA */           \
	std::uint8_t     padBB[0x5];               /* BB */           \
	std::uint8_t     unkC0[0x10];              /* C0 */           \
	std::uint8_t     fadeNodeMap[0x20];        /* D0 */           \
	std::uint8_t     unkF0[0x10];              /* F0 */           \
	void*            unk100;                   /* 100 */          \
	void*            unk108;                   /* 108 */          \
	std::uint32_t    unk110;                   /* 110 */          \
	bool             unk114;                   /* 114 */          \
	NiColorA         silhouetteColor;          /* 118 */          \
	bool             firstPerson;              /* 128 */          \
	bool             unk129;                   /* 129 */          \
	bool             unk12A;                   /* 12A */          \
	bool             unk12B;                   /* 12B */          \
	bool             drawDecals;               /* 12C */          \
	bool             unk12D;                   /* 12D */          \
	bool             unk12E;                   /* 12E */          \
	std::uint8_t     unk12F[0x158 - 0x12F];    /* 12F, VR only */ \
	BSBatchRenderer* batchRenderer;            /* 158 */          \
	std::uint32_t    currentPass;              /* 160 */          \
	std::uint32_t    currentBucket;            /* 164 */          \
	bool             currentActive;            /* 168 */          \
	std::uint8_t     pad169[0x7];              /* 169 */          \
	ShadowSceneNode* activeShadowSceneNode;    /* 170 */          \
	RENDER_MODE      renderMode;               /* 178 */          \
	std::uint8_t     pad17c[0x4];              /* 17C */          \
	void*            unk180;                   /* 180 */          \
	void*            unk188;                   /* 188 */          \
	std::uint32_t    unk190;                   /* 190 */          \
	NiPoint3         eyePosition;              /* 194 */          \
	std::uint8_t     unk1A0[0x10];             /* 1A0 */

			VR_RUNTIME_DATA_CONTENT
		};
		// 0x158, matching the previously-established total object size (0x1B0 below) --
		// not re-derived from this session's field mapping alone.
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x158);
		static_assert(offsetof(VR_RUNTIME_DATA, sunOcclusionTests) == 0x70 - 0x58);
		static_assert(offsetof(VR_RUNTIME_DATA, silhouetteColor) == 0x118 - 0x58);
		static_assert(offsetof(VR_RUNTIME_DATA, firstPerson) == 0x128 - 0x58);
		static_assert(offsetof(VR_RUNTIME_DATA, drawDecals) == 0x12C - 0x58);
		static_assert(offsetof(VR_RUNTIME_DATA, batchRenderer) == 0x158 - 0x58);
		static_assert(offsetof(VR_RUNTIME_DATA, renderMode) == 0x178 - 0x58);
		static_assert(offsetof(VR_RUNTIME_DATA, eyePosition) == 0x194 - 0x58);

		[[nodiscard]] inline RUNTIME_DATA* GetRuntimeData() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return &REL::RelocateMember<RUNTIME_DATA>(this, 0x58, 0);
			}
			return nullptr;
		}

		[[nodiscard]] inline const RUNTIME_DATA* GetRuntimeData() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return &REL::RelocateMember<RUNTIME_DATA>(this, 0x58, 0);
			}
			return nullptr;
		}

		[[nodiscard]] inline VR_RUNTIME_DATA* GetVRRuntimeData() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
				return &REL::RelocateMember<VR_RUNTIME_DATA>(this, 0, 0x58);
			}
			return nullptr;
		}

		[[nodiscard]] inline const VR_RUNTIME_DATA* GetVRRuntimeData() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
				return &REL::RelocateMember<VR_RUNTIME_DATA>(this, 0, 0x58);
			}
			return nullptr;
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 58
#elif !defined(ENABLE_SKYRIM_VR)
		RUNTIME_DATA_CONTENT;  // 58
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		VR_RUNTIME_DATA_CONTENT;  // 58
#endif
	};
#if !defined(SKYRIM_CROSS_VR)
	static_assert(sizeof(BSShaderAccumulator) == 0x180);
#elif !defined(ENABLE_SKYRIM_VR)
	static_assert(sizeof(BSShaderAccumulator) == 0x180);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(BSShaderAccumulator) == 0x1B0);
#else
	static_assert(sizeof(BSShaderAccumulator) == 0x58);
#endif
#undef RUNTIME_DATA_CONTENT

	namespace BSGraphics
	{
		// Same native class as RE::BSShaderAccumulator; kept only for its
		// runtime-agnostic GetRuntimeData() (no IsVR() branch needed at the call site).
		// see https://github.com/Nukem9/SkyrimSETest/blob/master/skyrim64_test/src/patches/TES/BSShader/BSShaderAccumulator.h
		class BSShaderAccumulator : public RE::BSShaderAccumulator
		{
		public:
			struct RUNTIME_DATA
			{
#define RUNTIME_DATA_CONTENT                                    \
	BSBatchRenderer*                     batchRenderer;         \
	std::uint32_t                        currentPass;           \
	std::uint32_t                        currentBucket;         \
	bool                                 currentActive;         \
	std::uint8_t                         pad0[0x7];             \
	ShadowSceneNode*                     activeShadowSceneNode; \
	RE::BSShaderAccumulator::RENDER_MODE renderMode;            \
	std::uint8_t                         pad1[0x18];            \
	NiPoint3                             eyePosition;           \
	std::uint8_t                         pad2[0x8];

				RUNTIME_DATA_CONTENT
			};
			static_assert(sizeof(RUNTIME_DATA) == 0x50);
			static_assert(offsetof(RUNTIME_DATA, batchRenderer) == 0);
			static_assert(offsetof(RUNTIME_DATA, activeShadowSceneNode) == 0x18);

			RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x130, 0x158);

			// members -- only declarable as raw fields in a single-runtime build (a
			// cross-VR binary can't statically pick one offset for the tail, hence
			// RUNTIME_DATA_ACCESSOR above); use that accessor in cross-VR code instead.
			std::uint8_t pad1[0xD0];
			bool         firstPerson;  // 128
			std::uint8_t pad0[0x3];
			bool         drawDecals;  // 12C
#if defined(EXCLUSIVE_SKYRIM_FLAT)
			RUNTIME_DATA_CONTENT;  // 130
#elif defined(EXCLUSIVE_SKYRIM_VR)
			std::uint64_t unk000[(0x158 - 0x130) >> 3];  // 130
			RUNTIME_DATA_CONTENT;                        // 158
#endif
		};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		static_assert(sizeof(BSShaderAccumulator) == 0x180);
		static_assert(offsetof(BSShaderAccumulator, batchRenderer) == 0x130);
		static_assert(offsetof(BSShaderAccumulator, currentPass) == 0x138);
		static_assert(offsetof(BSShaderAccumulator, currentBucket) == 0x13C);
		static_assert(offsetof(BSShaderAccumulator, currentActive) == 0x140);
		static_assert(offsetof(BSShaderAccumulator, activeShadowSceneNode) == 0x148);
		static_assert(offsetof(BSShaderAccumulator, renderMode) == 0x150);
		static_assert(offsetof(BSShaderAccumulator, eyePosition) == 0x16C);
#elif defined(EXCLUSIVE_SKYRIM_VR)
		static_assert(offsetof(BSShaderAccumulator, batchRenderer) == 0x158);
		static_assert(offsetof(BSShaderAccumulator, currentPass) == 0x160);
		static_assert(offsetof(BSShaderAccumulator, currentBucket) == 0x164);
		static_assert(offsetof(BSShaderAccumulator, currentActive) == 0x168);
		static_assert(offsetof(BSShaderAccumulator, activeShadowSceneNode) == 0x170);
		static_assert(offsetof(BSShaderAccumulator, renderMode) == 0x178);
		static_assert(offsetof(BSShaderAccumulator, eyePosition) == 0x194);
#else
		static_assert(sizeof(BSShaderAccumulator) == 0x130);
		static_assert(offsetof(BSShaderAccumulator, firstPerson) == 0x128);
		static_assert(offsetof(BSShaderAccumulator, drawDecals) == 0x12C);
#endif
#undef RUNTIME_DATA_CONTENT
	}
}

#undef VR_RUNTIME_DATA_CONTENT

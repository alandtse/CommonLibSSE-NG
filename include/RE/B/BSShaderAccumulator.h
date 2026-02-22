#pragma once

#include "RE/N/NiAlphaAccumulator.h"
#include "RE/N/NiColor.h"

namespace RE
{
	class BSBatchRenderer;
	class ShadowSceneNode;

	class BSShaderAccumulator : public NiAlphaAccumulator
	{
	public:
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

		~BSShaderAccumulator() override = default;  // 00

		// override (NiObject)
		[[nodiscard]] const NiRTTI* GetRTTI() const override;  // 02

		// override (NiAccumulator)
		void                            StartAccumulating(NiCamera* a_camera) override;                        // 25
		void                            FinishAccumulating() override;                                         // 26
		BSBatchRenderer::GeometryGroup* StartGroupingAlphas(NiBound* a_bound) override;                        // 28
		void                            StopGroupingAlphas(BSBatchRenderer::GeometryGroup* a_group) override;  // 29

		// add
		virtual void FinishAccumulatingPreResolveDepth(std::uint32_t flags);   // 2A
		virtual void FinishAccumulatingPostResolveDepth(std::uint32_t flags);  // 2B
		virtual void Unk_2C() = 0;                                             // 2C

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
	std::uint32_t    renderMode;               /* 150 */ \
	std::uint8_t     pad154[0x4];              /* 154 */ \
	void*            unk158;                   /* 158 */ \
	void*            unk160;                   /* 160 */ \
	std::uint32_t    unk168;                   /* 168 */ \
	NiPoint3         eyePosition;              /* 16C */ \
	std::uint8_t     unk178[0x8];              /* 178 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x128);

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT \
	std::uint64_t unk58[0x2B];  // 58

			VR_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x158);

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
}

#undef RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT

#pragma once

#include "RE/B/BSShaderAccumulator.h"
#include "REL/RuntimeDataAccessors.h"

// see https://github.com/Nukem9/SkyrimSETest/blob/master/skyrim64_test/src/patches/TES/BSShader/BSShaderAccumulator.h
namespace RE
{
	namespace BSGraphics
	{
		// Same native class as RE::BSShaderAccumulator; kept only for its
		// runtime-agnostic GetRuntimeData() (no IsVR() branch needed at the call site).
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
		};
#undef RUNTIME_DATA_CONTENT
	}
}

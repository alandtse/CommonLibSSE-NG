#pragma once

#include "RE/B/BSShaderAccumulator.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	namespace BSGraphics
	{
		// Same native class as RE::BSShaderAccumulator (identical RTTI and full field
		// layout, confirmed via Ghidra RE cross-checking SE against VR) -- this was an
		// independent, incompletely-RE'd duplicate declaration. Kept as a thin, layout-
		// compatible subclass (no added members/virtuals) purely to preserve its one
		// piece of RE that canonical doesn't otherwise expose as ergonomically: a single
		// GetRuntimeData() usable on any runtime without an IsVR() branch at the call
		// site, unlike canonical's split GetRuntimeData()/GetVRRuntimeData() pair.
		// RE::BSShaderAccumulator is the canonical declaration to extend going forward.
		class BSShaderAccumulator : public RE::BSShaderAccumulator
		{
		public:
			struct RUNTIME_DATA
			{
#define RUNTIME_DATA_CONTENT                                        \
	BSBatchRenderer*                        batchRenderer;          \
	std::uint32_t                           currentPass;            \
	std::uint32_t                           currentBucket;          \
	bool                                    currentActive;          \
	std::uint8_t                            pad0[0x7];              \
	ShadowSceneNode*                        activeShadowSceneNode;  \
	RE::BSShaderAccumulator::RENDER_MODE    renderMode;             \
	std::uint8_t                            pad1[0x18];             \
	NiPoint3                                eyePosition;            \
	std::uint8_t                            pad2[0x8];

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

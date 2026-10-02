#pragma once

#ifdef ENABLE_SKYRIM_VR
#	include "RE/H/HeldStateHandler.h"
#	include "REL/RuntimeDataAccessors.h"

namespace RE
{
	struct VrSwimHandler : public HeldStateHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_VrSwimHandler;
		inline static constexpr auto VTABLE = VTABLE_VrSwimHandler;

		~VrSwimHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01

		// VR members; the class only exists on VR, so the accessor is always valid.
		// Sizes and the three trailing arrays come from the binary. unk60 holds a
		// per-hand stroke history whose indexing was not fully resolved, so it stays
		// opaque rather than being given invented field names.
		struct VR_RUNTIME_DATA
		{
			std::uint8_t unk60[0x90];            // 60
			std::int32_t handRingIndex[2];       // F0 - ring cursor per hand, cycles 0-4
			float        handLastStrokeTime[2];  // F8 - compared against gTimeManager smoothedRunTimeMS
			bool         handSwimActive[2];      // 100
			std::uint8_t pad102[6];              // 102
		};
		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x60);
#	ifdef EXCLUSIVE_SKYRIM_VR
		VR_RUNTIME_DATA vrRuntimeData;  // 60
#	endif
	};
	STATIC_ASSERT_SIZE(VrSwimHandler, SIZE_UNDEFINED, SIZE_UNDEFINED, 0x108, 0x18);
}
#endif

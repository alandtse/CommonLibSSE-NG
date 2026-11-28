#pragma once

#include "RE/H/HeldStateHandler.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	struct ActivateHandler : public HeldStateHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActivateHandler;
		inline static constexpr auto VTABLE = VTABLE_ActivateHandler;

		~ActivateHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 06
#endif

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                            \
	std::uint8_t  unk18;                   /* 18, 60 */ \
	std::uint8_t  unk19;                   /* 19, 61 */ \
	bool          heldButtonActionSuccess; /* 1A, 62 */ \
	bool          disabled;                /* 1B, 63 */ \
	std::uint32_t unk1C;                   /* 1C, 64 */

			RUNTIME_DATA_CONTENT
		};
		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x18, 0x60);

		inline void SetHeldButtonActionSuccess(bool a_success) noexcept
		{
			GetRuntimeData().heldButtonActionSuccess = a_success;
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 18, 60
#endif

		// VR-only members; nullptr from the accessor on SE/AE
		struct VR_RUNTIME_DATA
		{
			float         unk68;  // 68
			std::uint32_t unk6C;  // 6C
		};
		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x68);
#ifdef EXCLUSIVE_SKYRIM_VR
		VR_RUNTIME_DATA vrRuntimeData;  // 68
#endif
	};
	STATIC_ASSERT_SIZE(ActivateHandler, 0x20, 0x20, 0x70, 0x18);
}
#undef RUNTIME_DATA_CONTENT

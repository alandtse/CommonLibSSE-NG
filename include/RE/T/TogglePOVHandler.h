#pragma once

#include "RE/H/HeldStateHandler.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	struct TogglePOVHandler : public HeldStateHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_TogglePOVHandler;
		inline static constexpr auto VTABLE = VTABLE_TogglePOVHandler;

		~TogglePOVHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 06
#endif

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                    \
	bool          pressRegistered; /* 18, 60 */ \
	std::uint8_t  pad19;           /* 19, 61 */ \
	std::uint16_t pad1A;           /* 1A, 62 */ \
	std::uint32_t pad1C;           /* 1C, 64 */

			RUNTIME_DATA_CONTENT
		};
		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x18, 0x60);

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 18, 60
#endif
	};
	STATIC_ASSERT_SIZE(TogglePOVHandler, 0x20, 0x20, 0x68, 0x18);
}
#undef RUNTIME_DATA_CONTENT

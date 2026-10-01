#pragma once

#include "RE/H/HeldStateHandler.h"

#ifdef ENABLE_SKYRIM_VR
namespace RE
{
	struct TeleportHandler : public HeldStateHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_TeleportHandler;

		~TeleportHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#	ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 04
#	endif

		// members
		std::uint64_t unk_18;  // 18
		std::uint64_t unk_20;  // 20
		std::uint64_t unk_28;  // 28
		std::uint64_t unk_30;  // 30
		std::uint64_t unk_38;  // 38
		std::uint64_t unk_40;  // 40
		std::uint64_t unk_48;  // 48
		std::uint64_t unk_50;  // 50
		std::uint64_t unk_58;  // 58
		std::uint64_t unk_60;  // 60
		std::uint64_t unk_68;  // 68
	};
	static_assert(sizeof(TeleportHandler) == 0x70);

}
#endif

#pragma once

#include "RE/P/PlayerInputHandler.h"
#include "REL/RuntimeDataAccessors.h"

#ifdef ENABLE_SKYRIM_AE
#	include "RE/S/SixaxisEvent.h"
#endif

namespace RE
{
	struct LookHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_LookHandler;
		inline static constexpr auto VTABLE = VTABLE_LookHandler;

		~LookHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessThumbstick(ThumbstickEvent* a_event, PlayerControlsData* a_data) override;  // 02
		void ProcessMouseMove(MouseMoveEvent* a_event, PlayerControlsData* a_data) override;    // 03
#endif

#ifdef ENABLE_SKYRIM_AE
		struct AE1799_RUNTIME_DATA
		{
			std::uint32_t unk10;         // 10 - ctor default 5; consumer unknown
			std::uint32_t pad14;         // 14
			SixaxisEvent  sixaxisEvent;  // 18
			std::uint64_t unkA8;         // A8
			std::int32_t  unkB0;         // B0 - ctor default -1
			std::uint32_t unkB4;         // B4 - ctor default 0
		};
		static_assert(sizeof(AE1799_RUNTIME_DATA) == 0xA8);

		[[nodiscard]] inline AE1799_RUNTIME_DATA* GetAe1799RuntimeData() noexcept
		{
			if (!REL::Module::IsAe1799()) {
				return nullptr;
			}
			return &REL::RelocateMember<AE1799_RUNTIME_DATA>(this, 0x10);
		}

		[[nodiscard]] inline const AE1799_RUNTIME_DATA* GetAe1799RuntimeData() const noexcept
		{
			return const_cast<LookHandler*>(this)->GetAe1799RuntimeData();
		}
#endif
	};
	STATIC_ASSERT_SIZE(LookHandler, 0x10, 0x10, 0x28, 0x10);
}

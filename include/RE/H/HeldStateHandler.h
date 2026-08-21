#pragma once

#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	class HeldStateHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_HeldStateHandler;
		inline static constexpr auto VTABLE = VTABLE_HeldStateHandler;

		~HeldStateHandler() override = default;  // 00

#if defined(EXCLUSIVE_SKYRIM_VR)
		// add
		virtual void UpdateHeldStateActive(const ButtonEvent* a_event);  // 05
		virtual void SetHeldStateActive(bool a_flag);                    // 06
#else
		// Non-virtual wrappers, same as PlayerInputHandler (needed by every
		// non-VR-exclusive build, not just cross-VR -- see its comment): these
		// slots come right after Button, so they need the same AE 1.7.99 +2 shift.
#	ifdef ENABLE_SKYRIM_AE
#		define AE1799_SLOT_SHIFT(idx) (REL::Module::IsAE() && REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_7_99) != std::strong_ordering::less ? (idx) + 2 : (idx))
#	else
#		define AE1799_SLOT_SHIFT(idx) (idx)
#	endif
		void UpdateHeldStateActive(const ButtonEvent* a_event)
		{
			REL::RelocateVirtual<void(HeldStateHandler*, const ButtonEvent*)>(AE1799_SLOT_SHIFT(0x05), 0x05, this, a_event);
		}
		void SetHeldStateActive(bool a_flag)
		{
			REL::RelocateVirtual<void(HeldStateHandler*, bool)>(AE1799_SLOT_SHIFT(0x06), 0x06, this, a_flag);
		}
#	undef AE1799_SLOT_SHIFT
#endif

		// members
		bool          heldStateActive{ false };      // 10
		bool          triggerReleaseEvent{ false };  // 11
		std::uint16_t pad12{ 0 };                    // 12
		std::uint32_t pad14{ 0 };                    // 14
	};
	STATIC_ASSERT_SIZE(HeldStateHandler, 0x18, 0x18, 0x30, 0x18);
}

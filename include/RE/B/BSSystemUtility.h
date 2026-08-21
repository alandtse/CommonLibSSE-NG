#pragma once

#include "RE/B/BSTEvent.h"
#include "REL/Relocation.h"
#include "SKSE/Version.h"

namespace RE
{
	class BSSystemEvent;
	struct BSGamepadEvent;

	class BSSystemUtility :
		public BSTEventSink<BSGamepadEvent>,  // 000
		public BSTEventSource<BSSystemEvent>  // 008
	{
	public:
		virtual ~BSSystemUtility();  // 00

		// override (BSTEventSink<BSGamepadEvent>)
		BSEventNotifyControl ProcessEvent(const BSGamepadEvent* a_event, BSTEventSource<BSGamepadEvent>* a_eventSource) override;  // 01

#ifdef ENABLE_SKYRIM_AE
#	define AE1799_SLOT_SHIFT(idx) (REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99) ? (idx) + 1 : (idx))

		void Unk_02AE(void* a_result)
		{
			if (REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
				REL::RelocateVirtual<void(BSSystemUtility*, void*)>(0x02, 0x02, this, a_result);
			}
		}
#else
#	define AE1799_SLOT_SHIFT(idx) (idx)
#endif

		void GetAuthenticationInfo(char*& a_userAuthID, std::uint64_t& a_size)
		{
			REL::RelocateVirtual<void(BSSystemUtility*, char*&, std::uint64_t&)>(AE1799_SLOT_SHIFT(0x02), AE1799_SLOT_SHIFT(0x02), this, a_userAuthID, a_size);
		}
		void Unk_03(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(AE1799_SLOT_SHIFT(0x03), AE1799_SLOT_SHIFT(0x03), this); }
		void DoInitialize() { REL::RelocateVirtual<void(BSSystemUtility*)>(AE1799_SLOT_SHIFT(0x04), AE1799_SLOT_SHIFT(0x04), this); }
		void Unk_05(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(AE1799_SLOT_SHIFT(0x05), AE1799_SLOT_SHIFT(0x05), this); }
		void DoUpdate() { REL::RelocateVirtual<void(BSSystemUtility*)>(AE1799_SLOT_SHIFT(0x06), AE1799_SLOT_SHIFT(0x06), this); }
		void Unk_07(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(AE1799_SLOT_SHIFT(0x07), AE1799_SLOT_SHIFT(0x07), this); }
		void DoGetUserName(char* a_buffer, std::uint64_t a_size)
		{
			REL::RelocateVirtual<void(BSSystemUtility*, char*, std::uint64_t)>(AE1799_SLOT_SHIFT(0x08), AE1799_SLOT_SHIFT(0x08), this, a_buffer, a_size);
		}
		void Unk_09(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(AE1799_SLOT_SHIFT(0x09), AE1799_SLOT_SHIFT(0x09), this); }
		void Unk_0A(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(AE1799_SLOT_SHIFT(0x0A), AE1799_SLOT_SHIFT(0x0A), this); }
		void Unk_0B(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(AE1799_SLOT_SHIFT(0x0B), AE1799_SLOT_SHIFT(0x0B), this); }
		void Unk_0C(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(AE1799_SLOT_SHIFT(0x0C), AE1799_SLOT_SHIFT(0x0C), this); }
		void DoGetComputerName(char* a_buffer, std::uint64_t a_size)
		{
			REL::RelocateVirtual<void(BSSystemUtility*, char*, std::uint64_t)>(AE1799_SLOT_SHIFT(0x0D), AE1799_SLOT_SHIFT(0x0D), this, a_buffer, a_size);
		}
		void Unk_0E(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(AE1799_SLOT_SHIFT(0x0E), AE1799_SLOT_SHIFT(0x0E), this); }
		void Unk_0F(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(AE1799_SLOT_SHIFT(0x0F), AE1799_SLOT_SHIFT(0x0F), this); }
		void DoAuthenticateUser() { REL::RelocateVirtual<void(BSSystemUtility*)>(AE1799_SLOT_SHIFT(0x10), AE1799_SLOT_SHIFT(0x10), this); }
		void Unk_11(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(AE1799_SLOT_SHIFT(0x11), AE1799_SLOT_SHIFT(0x11), this); }
		bool Unk_12() { return REL::RelocateVirtual<bool(BSSystemUtility*)>(AE1799_SLOT_SHIFT(0x12), AE1799_SLOT_SHIFT(0x12), this); }  // added in 1.6.1130
#undef AE1799_SLOT_SHIFT

		// members
		std::uint64_t unk060[24];  // 060
		std::uint8_t  unk120;      // 120 - added in 1.6.1130
		std::uint8_t  unk121;      // 121 - added in 1.6.1130
		std::uint16_t pad122;      // 122
		std::uint32_t pad124;      // 124
	};
	static_assert(sizeof(BSSystemUtility) == 0x128);
}

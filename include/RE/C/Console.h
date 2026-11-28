#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/I/IMenu.h"
#include "RE/N/NiSmartPointer.h"
#include "REL/RuntimeDataAccessors.h"
#include <SKSE/Version.h>

namespace RE
{
	class TESObjectREFR;
	class TESQuest;

	// menuDepth = 12
	// flags = kPausesGame | kAlwaysOpen | kUsesCursor | kAllowSaving
	// context = kConsole
	class Console : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_Console;
		inline static constexpr auto      VTABLE = VTABLE_Console;
		constexpr static std::string_view MENU_NAME = "Console";

		// AE only
		struct EXTENDED_CONSOLE_DATA
		{
#define EXTENDED_CONSOLE_DATA_CONTENT                            \
	bool showAchievementWarning; /* 00 -- initialized by ctor */ \
	bool ctrlKeyHeld;            /* 01 */

			EXTENDED_CONSOLE_DATA_CONTENT
		};

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                \
	BSTArray<void*> unk00; /* 00 -- element type unknown */ \
	std::uint32_t   unk18; /* 18 */                         \
	std::uint8_t    unk1C; /* 1C */

			RUNTIME_DATA_CONTENT
		};

		~Console() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

		static void                     ExecuteCommand(const char* a_command);
		static NiPointer<TESObjectREFR> GetSelectedRef();
		static ObjectRefHandle          GetSelectedRefHandle();
		static TESQuest*                GetCommandScriptParentQuest();

		void SetSelectedRef(NiPointer<TESObjectREFR> a_refPtr);
		void SetSelectedRef(TESObjectREFR* a_ref);
		void SetSelectedRef(ObjectRefHandle a_handle);

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			const auto offset = REL::Relocate(0x38, 0x30, 0x48);
			return REL::RelocateMember<RUNTIME_DATA>(this, offset, offset);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return const_cast<Console*>(this)->GetRuntimeData();
		}

		// nullptr on AE
		[[nodiscard]] inline void** GetOpcode() noexcept
		{
			if (REL::Module::IsAE()) {
				return nullptr;
			}
			return &REL::RelocateMember<void*>(this, 0x30, 0x40);
		}

		// nullptr on SE and VR
		[[nodiscard]] inline EXTENDED_CONSOLE_DATA* TryGetExtendedConsoleData() noexcept
		{
			if (!REL::Module::IsAE()) {
				return nullptr;
			}
			return &REL::RelocateMember<EXTENDED_CONSOLE_DATA>(this, 0x4D, 0x4D);
		}

		[[nodiscard]] inline const EXTENDED_CONSOLE_DATA* TryGetExtendedConsoleData() const noexcept
		{
			return const_cast<Console*>(this)->TryGetExtendedConsoleData();
		}

		// members
#if defined(EXCLUSIVE_SKYRIM_SE) || defined(EXCLUSIVE_SKYRIM_VR)
		void* opcode;          // 30, 40
		RUNTIME_DATA_CONTENT;  // 38, 48
#elif defined(EXCLUSIVE_SKYRIM_AE)
		RUNTIME_DATA_CONTENT;           // 30
		EXTENDED_CONSOLE_DATA_CONTENT;  // 4D
#endif

	protected:
		void
			SetSelectedRef_Impl(ObjectRefHandle& a_handle);
	};
	STATIC_ASSERT_SIZE(Console, 0x58, 0x50, 0x68, 0x30, 0x30);
}
#undef RUNTIME_DATA_CONTENT
#undef EXTENDED_CONSOLE_DATA_CONTENT

#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSString.h"
#include "RE/B/BSTEvent.h"
#include "REL/Relocation.h"
#include "SKSE/Version.h"

namespace RE
{
	class BSSaveDataEvent;

	class BSSaveDataSystemUtility :
		public BSTEventSource<BSSaveDataEvent>  // 008
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSSaveDataSystemUtility;
		inline static constexpr auto VTABLE = VTABLE_BSSaveDataSystemUtility;

		class Entry
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSSaveDataSystemUtility__Entry;
			inline static constexpr auto VTABLE = VTABLE_BSSaveDataSystemUtility__Entry;

			virtual void Read(const char* a_path);  // 00

			enum class SaveType : std::uint32_t
			{
				kAutosave = 0x0,
				kSave = 0x1,
				kQuicksave = 0x2,
				kCustom = 0x3
			};

			// members
			const char                            fileName[0x104];  // 008
			std::uint32_t                         pad0C;            // 00C
			BSString                              fileNamePtr;      // 110
			std::uint64_t                         unk120;           // 120
			std::uint32_t                         unk128;           // 128
			std::uint32_t                         pad12C;           // 12C
			BSString                              locationName;     // 130
			BSString                              unk140;           // 140
			BSString                              characterName;    // 150
			std::uint64_t                         unk160;           // 160
			std::uint32_t                         unk168;           // 168
			std::uint32_t                         pad16C;           // 16C
			std::uint64_t                         unk170;           // 170
			std::uint32_t                         unk178;           // 178
			std::uint32_t                         saveNumber;       // 17C
			std::uint32_t                         characterID;      // 180
			std::uint32_t                         unk184;           // 184
			bool                                  fileNameValid;    // 188
			bool                                  modded;           // 189
			std::uint8_t                          unk18A;           // 18A
			std::uint8_t                          pad18B;           // 18B
			std::uint32_t                         pad18C;           // 18C
			BSFixedString                         saveTypeName;     // 190
			REX::EnumSet<SaveType, std::uint32_t> saveType;         // 198
			std::uint32_t                         pad19C;           // 19C
		};
		static_assert(sizeof(Entry) == 0x1A0);

		virtual ~BSSaveDataSystemUtility();  // 00

		// add
		virtual bool    CreateSaveDirectory(const char* a_pathName, bool a_ignoreINI) = 0;                               // 01
		virtual errno_t PrepareFileSavePath(const char* a_fileName, char* a_dst, bool a_tmpSave, bool a_ignoreINI) = 0;  // 02 - a_dst must be 0x104 in length
		virtual void    Unk_03(void);                                                                                    // 03 - { return Unk_04(); }
		virtual void    Unk_04(void);                                                                                    // 04 - { return; }

#ifdef ENABLE_SKYRIM_AE
#	define AE1799_SLOT_SHIFT(idx) (REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99) ? (idx) + 6 : (idx))

		bool Unk_05AE(void)
		{
			if (!REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
				return false;
			}
			REL::RelocateVirtual<void(BSSaveDataSystemUtility*)>(0x05, 0x05, this);
			return true;
		}
		bool Unk_06AE(void)
		{
			if (!REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
				return false;
			}
			REL::RelocateVirtual<void(BSSaveDataSystemUtility*)>(0x06, 0x06, this);
			return true;
		}
		bool Unk_07AE(void)
		{
			if (!REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
				return true;
			}
			return REL::RelocateVirtual<bool(BSSaveDataSystemUtility*)>(0x07, 0x07, this);
		}
		bool Unk_08AE(void)
		{
			if (!REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
				return true;
			}
			return REL::RelocateVirtual<bool(BSSaveDataSystemUtility*)>(0x08, 0x08, this);
		}
		bool Unk_09AE(void)
		{
			if (!REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
				return true;
			}
			return REL::RelocateVirtual<bool(BSSaveDataSystemUtility*)>(0x09, 0x09, this);
		}
		bool Unk_0AAE(void)
		{
			if (!REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
				return false;
			}
			REL::RelocateVirtual<void(BSSaveDataSystemUtility*)>(0x0A, 0x0A, this);
			return true;
		}
#else
#	define AE1799_SLOT_SHIFT(idx) (idx)
#endif

		void Unk_05(void)
		{
			REL::RelocateVirtual<void(BSSaveDataSystemUtility*)>(AE1799_SLOT_SHIFT(0x05), AE1799_SLOT_SHIFT(0x05), this);
		}
		void Unk_06(void) { REL::RelocateVirtual<void(BSSaveDataSystemUtility*)>(AE1799_SLOT_SHIFT(0x06), AE1799_SLOT_SHIFT(0x06), this); }
		void Unk_07(void) { REL::RelocateVirtual<void(BSSaveDataSystemUtility*)>(AE1799_SLOT_SHIFT(0x07), AE1799_SLOT_SHIFT(0x07), this); }
		void Unk_08(void) { REL::RelocateVirtual<void(BSSaveDataSystemUtility*)>(AE1799_SLOT_SHIFT(0x08), AE1799_SLOT_SHIFT(0x08), this); }
		void Unk_09(void) { REL::RelocateVirtual<void(BSSaveDataSystemUtility*)>(AE1799_SLOT_SHIFT(0x09), AE1799_SLOT_SHIFT(0x09), this); }
		void Unk_0A(void) { REL::RelocateVirtual<void(BSSaveDataSystemUtility*)>(AE1799_SLOT_SHIFT(0x0A), AE1799_SLOT_SHIFT(0x0A), this); }
		void Unk_0B(void) { REL::RelocateVirtual<void(BSSaveDataSystemUtility*)>(AE1799_SLOT_SHIFT(0x0B), AE1799_SLOT_SHIFT(0x0B), this); }
		void Unk_0C(void) { REL::RelocateVirtual<void(BSSaveDataSystemUtility*)>(AE1799_SLOT_SHIFT(0x0C), AE1799_SLOT_SHIFT(0x0C), this); }
		void Unk_0D(void) { REL::RelocateVirtual<void(BSSaveDataSystemUtility*)>(AE1799_SLOT_SHIFT(0x0D), AE1799_SLOT_SHIFT(0x0D), this); }
		void Unk_0E(void) { REL::RelocateVirtual<void(BSSaveDataSystemUtility*)>(AE1799_SLOT_SHIFT(0x0E), AE1799_SLOT_SHIFT(0x0E), this); }
		void Unk_0F(void) { REL::RelocateVirtual<void(BSSaveDataSystemUtility*)>(AE1799_SLOT_SHIFT(0x0F), AE1799_SLOT_SHIFT(0x0F), this); }
		void Unk_10(void) { REL::RelocateVirtual<void(BSSaveDataSystemUtility*)>(AE1799_SLOT_SHIFT(0x10), AE1799_SLOT_SHIFT(0x10), this); }
		void Unk_11(void) { REL::RelocateVirtual<void(BSSaveDataSystemUtility*)>(AE1799_SLOT_SHIFT(0x11), AE1799_SLOT_SHIFT(0x11), this); }
#undef AE1799_SLOT_SHIFT

		// members
		std::uint8_t  unk060;              // 060
		std::uint8_t  pad061;              // 061
		std::uint16_t pad062;              // 062
		std::uint32_t currentCharacterID;  // 064
		std::uint8_t  unk068;              // 068
		std::uint8_t  pad069;              // 069
		std::uint16_t pad06A;              // 06A
		std::uint32_t pad06C;              // 06C
		Entry         entry;               // 070
		std::uint32_t unk210;              // 210
		std::uint32_t pad214;              // 214
		std::uint64_t unk218;              // 218
		std::uint64_t unk220;              // 220
	};
	static_assert(sizeof(BSSaveDataSystemUtility) == 0x228);
}

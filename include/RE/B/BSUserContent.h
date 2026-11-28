#pragma once

#ifdef ENABLE_SKYRIM_AE

#	include "RE/B/BSString.h"

namespace RE
{
	namespace BSPlatform
	{
		/** Common prefix only: sizeof is 0x288 on AE 1.6.1170 and 0x2A8 on 1.7.104. */
		class BSUserContent
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSPlatform__BSUserContent;
			inline static constexpr auto VTABLE = VTABLE_BSPlatform__BSUserContent;

			struct Data98
			{
				std::uint32_t unk00;  // 00
				BSString      unk08;  // 08
			};
			static_assert(sizeof(Data98) == 0x18);

			BSUserContent() = delete;
			BSUserContent(const BSUserContent&) = delete;
			BSUserContent& operator=(const BSUserContent&) = delete;

			virtual ~BSUserContent();  // 00

			// add
			virtual void Clear();  // 01

			// members
			BSString      unk08;   // 08
			BSString      unk18;   // 18
			BSString      unk28;   // 28
			BSString      author;  // 38
			BSString      unk48;   // 48
			BSString      unk58;   // 58
			BSString      unk68;   // 68
			BSString      unk78;   // 78 - a formatted date on 1.6.1170
			BSString      unk88;   // 88
			Data98        unk98;   // 98
			BSString      unkB0;   // B0
			std::uint64_t unkC0;   // C0
			std::uint64_t unkC8;   // C8
		};
		static_assert(sizeof(BSUserContent) == 0xD0);  // the shared prefix
	}
}

#endif

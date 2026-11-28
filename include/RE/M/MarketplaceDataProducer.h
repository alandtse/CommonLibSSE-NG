#pragma once

#ifdef ENABLE_SKYRIM_AE

#	include "RE/B/BSTArray.h"

namespace RE
{
	class MarketplaceMenu;

	class MarketplaceDataProducer
	{
	public:
		inline static constexpr auto RTTI = RTTI_MarketplaceDataProducer;
		inline static constexpr auto VTABLE = VTABLE_MarketplaceDataProducer;

		struct Entry
		{
			virtual ~Entry();  // 00

			// members
			std::uint8_t unk008[0x280];  // 008
		};
		static_assert(sizeof(Entry) == 0x288);

		virtual ~MarketplaceDataProducer();  // 00

		// members
		MarketplaceMenu* menu;   // 08
		void*            unk10;  // 10
		BSTArray<Entry>  unk18;  // 18
		std::uint32_t    unk30;  // 30
		BSTArray<Entry>  unk38;  // 38
		std::uint32_t    unk50;  // 50
		BSTArray<Entry>  unk58;  // 58
		std::uint64_t    unk70;  // 70
	};
	static_assert(sizeof(MarketplaceDataProducer) == 0x78);
}

#endif

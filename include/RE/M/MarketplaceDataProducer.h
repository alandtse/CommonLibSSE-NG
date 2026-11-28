#pragma once

#ifdef ENABLE_SKYRIM_AE

namespace RE
{
	namespace BSPlatform
	{
		class BSUserContent;
	}

	class MarketplaceMenu;

	class MarketplaceDataProducer
	{
	public:
		inline static constexpr auto RTTI = RTTI_MarketplaceDataProducer;
		inline static constexpr auto VTABLE = VTABLE_MarketplaceDataProducer;

		/** BSTArray header whose element stride differs between AE runtimes. */
		struct UserContentArray
		{
			BSPlatform::BSUserContent* data;      // 00
			std::uint32_t              capacity;  // 08
			std::uint32_t              pad0C;     // 0C
			std::uint32_t              size;      // 10
			std::uint32_t              pad14;     // 14
		};
		static_assert(sizeof(UserContentArray) == 0x18);

		virtual ~MarketplaceDataProducer();  // 00

		// members
		MarketplaceMenu* menu;   // 08
		void*            unk10;  // 10
		UserContentArray unk18;  // 18
		std::uint32_t    unk30;  // 30
		UserContentArray unk38;  // 38
		std::uint32_t    unk50;  // 50
		UserContentArray unk58;  // 58
		std::uint64_t    unk70;  // 70
	};
	static_assert(sizeof(MarketplaceDataProducer) == 0x78);
}

#endif

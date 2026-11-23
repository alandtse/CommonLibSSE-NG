#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	namespace BSScript
	{
		class ObjectTypeInfo;

		class LinkContext
		{
		public:
			// members
			std::uint8_t                    unk00;                  // 00
			std::uint8_t                    pad01;                  // 01
			std::uint16_t                   pad02;                  // 02
			std::uint32_t                   pad04;                  // 04
			BSFixedString                   unk08;                  // 08
			BSTSmartPointer<ObjectTypeInfo> parentTypeInfo;         // 10
			std::uint32_t                   unk18;                  // 18
			std::uint32_t                   pad1C;                  // 1C
			std::byte                       unk20[0x30];            // 20
			BSFixedString                   docString;              // 50
			std::byte                       variableMap[0x30];      // 58 - BSTScrapHashMap
			std::byte                       userFlagMap[0x30];      // 88 - BSTScrapHashMap
			std::byte                       unkMapB8[0x30];         // B8 - BSTScrapHashMap
			std::byte                       propertyMap[0x30];      // E8 - BSTScrapHashMap
			std::byte                       staticFuncMap[0x30];    // 118 - BSTScrapHashMap
			std::byte                       memberFuncMap[0x30];    // 148 - BSTScrapHashMap
			std::byte                       stateMap[0x30];         // 178 - BSTScrapHashMap
			BSFixedString                   autoStateName;          // 1A8
			std::byte                       initialValueMap[0x30];  // 1B0 - BSTScrapHashMap
		};
		static_assert(sizeof(LinkContext) == 0x1E0);
	}
}

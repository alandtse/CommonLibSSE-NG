#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IFunction.h"
#include "RE/O/ObjectTypeInfo.h"
#include "RE/P/PropertyTypeInfo.h"
#include "RE/T/TypeInfo.h"
#include "RE/V/Variable.h"

namespace RE
{
	namespace BSScript
	{
		class LinkContext
		{
		public:
			// members
			std::uint8_t                                                                                unk00;            // 00
			std::uint8_t                                                                                pad01;            // 01
			std::uint16_t                                                                               pad02;            // 02
			std::uint32_t                                                                               pad04;            // 04
			BSFixedString                                                                               unk08;            // 08
			BSTSmartPointer<ObjectTypeInfo>                                                             parentTypeInfo;   // 10
			std::uint32_t                                                                               unk18;            // 18
			std::uint32_t                                                                               pad1C;            // 1C
			BSTScrapHashMap<BSFixedString, UnkValue>                                                    unk20;            // 20
			BSFixedString                                                                               docString;        // 50
			BSTScrapHashMap<BSFixedString, TypeInfo>                                                    variableMap;      // 58
			BSTScrapHashMap<BSFixedString, ObjectTypeInfo::UserFlagInfo>                                userFlagMap;      // 88
			BSTScrapHashMap<BSFixedString, ObjectTypeInfo::UserFlagInfo>                                unkMapB8;         // B8
			BSTScrapHashMap<BSFixedString, PropertyTypeInfo>                                            propertyMap;      // E8
			BSTScrapHashMap<BSFixedString, BSTSmartPointer<IFunction>>                                  staticFuncMap;    // 118
			BSTScrapHashMap<BSFixedString, BSTSmartPointer<IFunction>>                                  memberFuncMap;    // 148
			BSTScrapHashMap<BSFixedString, BSTScrapHashMap<BSFixedString, BSTSmartPointer<IFunction>>*> stateMap;         // 178
			BSFixedString                                                                               autoStateName;    // 1A8
			BSTScrapHashMap<BSFixedString, Variable>                                                    initialValueMap;  // 1B0
		};
		static_assert(sizeof(LinkContext) == 0x1E0);
	}
}

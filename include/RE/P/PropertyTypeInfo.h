#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/T/TypeInfo.h"

namespace RE
{
	namespace BSScript
	{
		class IFunction;

		struct PropertyTypeInfo
		{
		public:
			enum class Permissions
			{
				kReadOnly = 1,
				kWriteOnly = 2
			};

			void GetGetFunction(BSTSmartPointer<IFunction>& a_outFunction);
			void GetSetFunction(BSTSmartPointer<IFunction>& a_outFunction);

			// members
			BSFixedString                            parentObjName;  // 00
			BSFixedString                            propertyName;   // 08
			TypeInfo                                 type;           // 10
			REX::EnumSet<Permissions, std::uint32_t> permissions;    // 18
			std::uint32_t                            pad1C;          // 1C
			BSTSmartPointer<IFunction>               getFunction;    // 20
			BSTSmartPointer<IFunction>               setFunction;    // 28
			std::int32_t                             autoVarIndex;   // 30
			std::uint32_t                            userFlags;      // 34
			BSFixedString                            docString;      // 38
		};
		static_assert(sizeof(PropertyTypeInfo) == 0x40);
	}
}

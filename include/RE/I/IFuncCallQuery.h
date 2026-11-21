#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	namespace BSScript
	{
		class ObjectTypeInfo;
		class Variable;

		namespace Internal
		{
			class IFuncCallQuery : public BSIntrusiveRefCounted
			{
			public:
				inline static constexpr auto RTTI = RTTI_BSScript__Internal__IFuncCallQuery;
				inline static constexpr auto VTABLE = VTABLE_BSScript__Internal__IFuncCallQuery;

				enum class CallType
				{
					kMember,
					kStatic,
					kGetter,
					kSetter
				};

				virtual ~IFuncCallQuery();  // 00

				// add
				virtual bool GetFunctionCallInfo(CallType& a_callType, BSTSmartPointer<ObjectTypeInfo>& a_objType, BSFixedString& a_name, Variable& a_obj, BSScrapArray<Variable>& a_args) const = 0;  // 01

				// members
				std::uint32_t pad0C;  // 0C
			};
			static_assert(sizeof(IFuncCallQuery) == 0x10);
		}
	}
}

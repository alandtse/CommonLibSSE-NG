#include "RE/I/IFunction.h"

#include "RE/O/ObjectTypeInfo.h"

namespace RE
{
	namespace BSScript
	{
		IFunction::IFunction() :
			pad0C(0)
		{}

		bool IFunction::SignaturesMatch(const BSTSmartPointer<IFunction>& a_rhs) const
		{
			if (GetReturnType() != a_rhs->GetReturnType() ||
				GetIsStatic() != a_rhs->GetIsStatic() ||
				GetParamCount() != a_rhs->GetParamCount()) {
				return false;
			}

			for (std::uint32_t i = 0; i < GetParamCount(); ++i) {
				BSFixedString name;
				TypeInfo      lhsType;
				TypeInfo      rhsType;

				GetParam(i, name, lhsType);
				a_rhs->GetParam(i, name, rhsType);

				if (rhsType != lhsType) {
					return false;
				}
			}

			return true;
		}
	}
}

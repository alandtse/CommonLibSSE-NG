#include "RE/P/PropertyTypeInfo.h"
#include "RE/A/AutoPropGetFunction.h"
#include "RE/A/AutoPropSetFunction.h"

namespace RE
{
	namespace BSScript
	{
		void PropertyTypeInfo::GetGetFunction(BSTSmartPointer<IFunction>& a_outFunction)
		{
			if (getFunction != nullptr) {
				a_outFunction = getFunction;
				return;
			}

			if (autoVarIndex != -1) {
				const auto autoPropGetFunction = new AutoPropGetFunction(parentObjName, propertyName, type, autoVarIndex);

				a_outFunction = BSTSmartPointer<IFunction>(autoPropGetFunction);
			}
		}

		void PropertyTypeInfo::GetSetFunction(BSTSmartPointer<IFunction>& a_outFunction)
		{
			if (setFunction != nullptr) {
				a_outFunction = setFunction;
				return;
			}

			if (autoVarIndex != -1) {
				const auto autoPropSetFunction = new AutoPropSetFunction(parentObjName, propertyName, type, autoVarIndex);

				a_outFunction = BSTSmartPointer<IFunction>(autoPropSetFunction);
			}
		}
	}
}

#include "RE/O/ObjectTypeInfo.h"

#include "RE/I/IFunction.h"

namespace RE
{
	namespace BSScript
	{
		ObjectTypeInfo::ObjectTypeInfo(const BSFixedString& a_className)
		{
			name = a_className;
			parentTypeInfo = nullptr;
			docString = "";

			linkedValid = LinkValidState::kNotLinked;
			userFlagCount = 0;
			variableCount = 0;
			variableUserFlagCount = 0;
			initialValueCount = 0;
			propertyCount = 0;
			staticFunctionCount = 0;
			emptyStateMemberFunctionCount = 0;
			namedStateCount = 0;
			autoStateIndex = 0;
			data = nullptr;
		}

		BSFixedString ObjectTypeInfo::UserFlagInfo::GetUserFlag() const
		{
			auto sanitizedType = data & ~kSetOnObject;
			return *reinterpret_cast<BSFixedString*>(&sanitizedType);
		}

		auto ObjectTypeInfo::NamedStateInfo::GetFuncIter()
			-> Func*
		{
			return reinterpret_cast<Func*>((std::uintptr_t)this + memberFunctionOffset);
		}

		auto ObjectTypeInfo::NamedStateInfo::GetFuncIter() const
			-> const Func*
		{
			return reinterpret_cast<const Func*>((std::uintptr_t)this + memberFunctionOffset);
		}

		ObjectTypeInfo::~ObjectTypeInfo()
		{
			ReleaseData(false);
		}

		const char* ObjectTypeInfo::GetName() const
		{
			return name.c_str();
		}

		ObjectTypeInfo* ObjectTypeInfo::GetParent()
		{
			return parentTypeInfo.get();
		}

		const ObjectTypeInfo* ObjectTypeInfo::GetParent() const
		{
			return parentTypeInfo.get();
		}

		TypeInfo::RawType ObjectTypeInfo::GetRawType() const
		{
			return stl::unrestricted_cast<TypeInfo::RawType>(this);
		}

		auto ObjectTypeInfo::GetUnlinkedFunctionIter()
			-> UnlinkedNativeFunction*
		{
			return reinterpret_cast<UnlinkedNativeFunction*>(data);
		}

		auto ObjectTypeInfo::GetUnlinkedFunctionIter() const
			-> const UnlinkedNativeFunction*
		{
			return reinterpret_cast<const UnlinkedNativeFunction*>(data);
		}

		auto ObjectTypeInfo::GetUserFlagIter()
			-> UserFlagInfo*
		{
			return reinterpret_cast<UserFlagInfo*>(data);
		}

		auto ObjectTypeInfo::GetUserFlagIter() const
			-> const UserFlagInfo*
		{
			return reinterpret_cast<const UserFlagInfo*>(data);
		}

		std::uint32_t ObjectTypeInfo::GetTotalNumVariables() const
		{
			auto numVars = GetNumVariables();
			for (auto iter = GetParent(); iter; iter = iter->GetParent()) {
				numVars += iter->GetNumVariables();
			}
			return numVars;
		}

		auto ObjectTypeInfo::GetVariableIter()
			-> VariableInfo*
		{
			return reinterpret_cast<VariableInfo*>(GetUserFlagIter() + GetNumUserFlags());
		}

		auto ObjectTypeInfo::GetVariableIter() const
			-> const VariableInfo*
		{
			return reinterpret_cast<const VariableInfo*>(GetUserFlagIter() + GetNumUserFlags());
		}

		auto ObjectTypeInfo::GetInitialValueIter()
			-> InitialValueInfo*
		{
			return reinterpret_cast<InitialValueInfo*>(GetVariableIter() + GetNumVariables());
		}

		auto ObjectTypeInfo::GetInitialValueIter() const
			-> const InitialValueInfo*
		{
			return reinterpret_cast<const InitialValueInfo*>(GetVariableIter() + GetNumVariables());
		}

		auto ObjectTypeInfo::GetPropertyIter()
			-> PropertyInfo*
		{
			return reinterpret_cast<PropertyInfo*>(GetInitialValueIter() + GetNumInitalValues());
		}

		auto ObjectTypeInfo::GetPropertyIter() const
			-> const PropertyInfo*
		{
			return reinterpret_cast<const PropertyInfo*>(GetInitialValueIter() + GetNumInitalValues());
		}

		auto ObjectTypeInfo::GetGlobalFuncIter()
			-> GlobalFuncInfo*
		{
			return reinterpret_cast<GlobalFuncInfo*>(GetPropertyIter() + GetNumProperties());
		}

		auto ObjectTypeInfo::GetGlobalFuncIter() const
			-> const GlobalFuncInfo*
		{
			return reinterpret_cast<const GlobalFuncInfo*>(GetPropertyIter() + GetNumProperties());
		}

		auto ObjectTypeInfo::GetMemberFuncIter()
			-> MemberFuncInfo*
		{
			return reinterpret_cast<MemberFuncInfo*>(GetGlobalFuncIter() + GetNumGlobalFuncs());
		}

		auto ObjectTypeInfo::GetMemberFuncIter() const
			-> const MemberFuncInfo*
		{
			return reinterpret_cast<const MemberFuncInfo*>(GetGlobalFuncIter() + GetNumGlobalFuncs());
		}

		auto ObjectTypeInfo::GetNamedStateIter()
			-> NamedStateInfo*
		{
			return reinterpret_cast<NamedStateInfo*>(GetMemberFuncIter() + GetNumMemberFuncs());
		}

		auto ObjectTypeInfo::GetNamedStateIter() const
			-> const NamedStateInfo*
		{
			return reinterpret_cast<const NamedStateInfo*>(GetMemberFuncIter() + GetNumMemberFuncs());
		}

		std::uint32_t ObjectTypeInfo::GetPropertyIndex(const BSFixedString& a_name) const
		{
			const auto props = GetPropertyIter();
			if (props) {
				for (std::uint32_t i = 0; i < GetNumProperties(); ++i) {
					const auto& prop = props[i];
					if (prop.name == a_name) {
						return prop.info.autoVarIndex;
					}
				}
			}
			return static_cast<std::uint32_t>(-1);
		}

		[[nodiscard]] bool ObjectTypeInfo::HasAutoState() const noexcept
		{
			return autoStateIndex < namedStateCount;
		}

		const BSFixedString ObjectTypeInfo::GetInitialStateName() const
		{
			if (linkedValid == LinkValidState::kLinkedValid && HasAutoState()) {
				return GetNamedStateIter()[autoStateIndex].name;
			}
			return "";
		}

		void ObjectTypeInfo::ReleaseData(const bool a_keepNativeFunctions)
		{
			UnlinkedNativeFunction* nativeList = nullptr;

			// destroys one function slot, first moving natives onto the unlinked list when asked to
			const auto releaseFunc = [&](BSTSmartPointer<IFunction>& a_func) {
				if (a_keepNativeFunctions && a_func->GetIsNative()) {
					auto* node = static_cast<UnlinkedNativeFunction*>(RE::malloc(sizeof(UnlinkedNativeFunction)));
					// the engine drops the whole list if this allocation fails
					if (!node) {
						nativeList = nullptr;
					} else {
						node->next = nativeList;
						new (&node->func) BSTSmartPointer(a_func);
						nativeList = node;
					}
				}
				std::destroy_at(&a_func);
			};

			if (linkedValid == LinkValidState::kLinkedInvalid || linkedValid == LinkValidState::kLinkedValid) {
				for (auto *it = GetUserFlagIter(), *end = it + GetNumUserFlags(); it != end; ++it) {
					it->data &= ~UserFlagInfo::kSetOnObject;
					std::destroy_at(reinterpret_cast<BSFixedString*>(&it->data));
				}
				for (auto *it = GetVariableIter(), *end = it + GetNumVariables(); it != end; ++it) {
					std::destroy_at(&it->name);
				}
				for (auto *it = GetInitialValueIter(), *end = it + GetNumInitalValues(); it != end; ++it) {
					std::destroy_at(&it->initialValue);
				}
				for (auto *it = GetPropertyIter(), *end = it + GetNumProperties(); it != end; ++it) {
					std::destroy_at(it);
				}
				for (auto *it = GetGlobalFuncIter(), *end = it + GetNumGlobalFuncs(); it != end; ++it) {
					releaseFunc(it->func);
				}
				for (auto *it = GetMemberFuncIter(), *end = it + GetNumMemberFuncs(); it != end; ++it) {
					releaseFunc(it->func);
				}
				for (auto *state = GetNamedStateIter(), *end = state + GetNumNamedStates(); state != end; ++state) {
					for (auto *fn = state->GetFuncIter(), *fnEnd = fn + state->GetNumFuncs(); fn != fnEnd; ++fn) {
						releaseFunc(fn->func);
					}
					std::destroy_at(&state->name);
				}
				RE::free(data);
				data = nativeList;
			} else if (!a_keepNativeFunctions) {
				for (auto* node = GetUnlinkedFunctionIter(); node != nullptr;) {
					auto* next = node->next;
					std::destroy_at(&node->func);
					RE::free(node);
					node = next;
				}
				data = nullptr;
			}

			docString = "";

			linkedValid = LinkValidState::kNotLinked;
			userFlagCount = 0;
			variableCount = 0;
			variableUserFlagCount = 0;
			initialValueCount = 0;
			propertyCount = 0;
			staticFunctionCount = 0;
			emptyStateMemberFunctionCount = 0;
			namedStateCount = 0;
			autoStateIndex = 0;

			if (!a_keepNativeFunctions) {
				name = "";
				parentTypeInfo = nullptr;
			}
		}
	}
}

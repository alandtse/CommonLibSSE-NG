#include "RE/O/Object.h"

#include "RE/I/IObjectHandlePolicy.h"
#include "RE/O/ObjectTypeInfo.h"
#include "RE/V/VirtualMachine.h"

static constexpr std::uintptr_t kPendingResetBit = 0x1;

namespace
{

	RE::BSScript::IObjectHandlePolicy* GetHandlePolicy() noexcept
	{
		static REL::Relocation<RE::BSScript::IObjectHandlePolicy**> handlePolicy{ REL::VariantID(527437, 414391, 0x3422948) };
		return *handlePolicy;
	}

	void SetHandlePolicy(RE::BSScript::IObjectHandlePolicy* a_policy) noexcept
	{
		static REL::Relocation<RE::BSScript::IObjectHandlePolicy**> handlePolicy{ REL::VariantID(527437, 414391, 0x3422948) };
		*handlePolicy = a_policy;
	}

	void SpinBackoff(std::uint32_t& a_spins) noexcept
	{
		if (a_spins++ < 10000)
			REX::W32::Sleep(0);
		else
			REX::W32::Sleep(1);
	}
}

static constexpr std::int32_t kLockBit = static_cast<std::int32_t>(1u << 31);

namespace RE
{
	namespace BSScript
	{
		Object::Object(const BSTSmartPointer<ObjectTypeInfo>& a_type, IObjectHandlePolicy* a_policy, uint32_t a_numProperties) :
			remainingPropsToInit(a_numProperties), type(a_type), currentState("")
		{
			constructed = 0;
			initialized = 0;
			valid = 1;
			owningStack = 0;

			// Object CTOR sets the policy each time its created
			SetHandlePolicy(a_policy);

			handleRef.ChangeHandle(a_policy->EmptyHandle());

			// 0-init required to prevent cleanup of garbage variable data as they are changed/modified
			std::memset((void*)variables, 0, sizeof(Variable) * type->GetTotalNumVariables());
		}

		Object::~Object()
		{
			if (IsConstructed()) {
				const std::uint32_t size = type ? type->GetVariableCount() : 0;
				for (std::uint32_t i = 0; i < size; ++i) {
					variables[i].SetNone();
				}

				constructed = false;
				initialized = false;
			}

			const auto currentStack = GetOwningStack();
			if (currentStack != nullptr) {
				UnlockFromStack(currentStack.get());
			}
		}

		void Object::Initialize()
		{
			// Setup valid, initial state and all variable types with their initial values
			valid = 1;

			auto currentType = type;

			bool stateAssigned = false;

			while (currentType != nullptr) {
				valid = valid && (currentType->linkedValid == ObjectTypeInfo::LinkValidState::kLinkedValid);

				if (!stateAssigned) {
					currentState = currentType->GetInitialStateName();
					stateAssigned = !currentState.empty();
				}

				currentType = currentType->parentTypeInfo;
			}

			if (valid) {
				uint32_t currentVariableIndex = 0;
				// Walk the type chain in reverse to construct all variables with their types
				std::stack<BSTSmartPointer<ObjectTypeInfo>> parentChain;
				currentType = type;
				while (currentType != nullptr) {
					parentChain.push(currentType);
					currentType = currentType->parentTypeInfo;
				}

				while (!parentChain.empty()) {
					currentType = parentChain.top();

					// Type must be preserved even if initial value for a variable does not exist
					for (auto& info : std::span(currentType->GetVariableIter(), currentType->GetNumVariables())) {
						variables[currentVariableIndex] = Variable(info.type);
						currentVariableIndex++;
					}
					for (auto& value : std::span(currentType->GetInitialValueIter(), currentType->GetNumInitalValues())) {
						variables[value.variableIndex] = value.initialValue;
					}

					parentChain.pop();
				}

				constructed = 1;
			}
		}

		VMHandle Object::GetHandle() const
		{
			return handleRef.GetHandle();
		}

		ObjectTypeInfo* Object::GetTypeInfo()
		{
			return type.get();
		}

		const ObjectTypeInfo* Object::GetTypeInfo() const
		{
			return type.get();
		}

		void* Object::Resolve(VMTypeID a_typeID) const
		{
			auto vm = Internal::VirtualMachine::GetSingleton();
			auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			auto myHandle = GetHandle();
			if (policy && policy->HandleIsType(a_typeID, myHandle) && policy->IsHandleObjectAvailable(myHandle)) {
				return policy->GetObjectForHandle(a_typeID, myHandle);
			} else {
				return nullptr;
			}
		}

		void Object::IncRef()
		{
			return handleRef.IncRef();
		}

		std::uint32_t Object::DecRef()
		{
			return handleRef.DecRef();
		}

		Variable* Object::GetProperty(const BSFixedString& a_name)
		{
			return const_cast<Variable*>(
				const_cast<const Object*>(this)->GetProperty(a_name));
		}

		const Variable* Object::GetProperty(const BSFixedString& a_name) const
		{
			constexpr auto INVALID = static_cast<std::uint32_t>(-1);

			auto idx = INVALID;
			for (auto cls = type.get(); cls && idx == INVALID; cls = cls->GetParent()) {
				idx = cls->GetPropertyIndex(a_name);
			}

			return idx != INVALID ? std::addressof(variables[idx]) : nullptr;
		}

		Variable* Object::GetVariable(const BSFixedString& a_name)
		{
			return const_cast<Variable*>(
				const_cast<const Object*>(this)->GetVariable(a_name));
		}

		const Variable* Object::GetVariable(const BSFixedString& a_name) const
		{
			constexpr auto INVALID = static_cast<std::uint32_t>(-1);

			auto          idx = INVALID;
			std::uint32_t offset = 0;
			for (auto cls = type.get(); cls; cls = cls->GetParent()) {
				const auto vars = cls->GetVariableIter();
				if (idx == INVALID) {
					if (vars) {
						for (std::uint32_t i = 0; i < cls->GetNumVariables(); i++) {
							const auto& var = vars[i];
							if (var.name == a_name) {
								idx = i;
								break;
							}
						}
					}
				} else {
					offset += cls->GetNumVariables();
				}
			}

			if (idx == INVALID) {
				return nullptr;
			}

			return std::addressof(variables[offset + idx]);
		}

		bool Object::TryLockToStack(Stack* a_stack) noexcept
		{
			std::uintptr_t expected = 0;
			auto           desired = reinterpret_cast<std::uintptr_t>(a_stack);

			if (owningStack.compare_exchange_strong(expected, desired)) {
				if (a_stack != nullptr) {
					a_stack->IncRef();
				}
				return true;
			}

			const auto current = expected & ~kPendingResetBit;
			return current == desired;
		}

		void Object::UnlockFromStack(Stack* a_stack) noexcept
		{
			if (a_stack == nullptr) {
				return;
			}

			const auto target = reinterpret_cast<std::uintptr_t>(a_stack);
			auto       current = owningStack.load(std::memory_order_relaxed);

			while ((current & ~kPendingResetBit) == target) {
				// clear pointer, keep whatever the tag bit currently is
				const auto desired = current & kPendingResetBit;
				if (owningStack.compare_exchange_weak(current, desired)) {
					a_stack->DecRef();
					break;
				}
			}
		}

		// Lock
		void Object::LockPendingReset() noexcept
		{
			auto current = owningStack.load(std::memory_order_relaxed);
			while (!owningStack.compare_exchange_weak(current, current | kPendingResetBit)) {}
		}

		// Unlock
		void Object::UnlockPendingReset() noexcept
		{
			auto current = owningStack.load(std::memory_order_relaxed);
			while (!owningStack.compare_exchange_weak(current, current & ~kPendingResetBit)) {}
		}

		[[nodiscard]] BSTSmartPointer<Stack> Object::GetOwningStack() const noexcept
		{
			return BSTSmartPointer(reinterpret_cast<Stack*>(owningStack.load(std::memory_order_relaxed) & ~kPendingResetBit));
		}

		[[nodiscard]] bool Object::IsPendingReset() const noexcept
		{
			return (owningStack.load(std::memory_order_relaxed) & kPendingResetBit) != 0;
		}

		void Object::ReleaseProperties()
		{
			const auto variableCount = type->GetTotalNumVariables();

			for (size_t i = 0; i < variableCount; i++) {
				variables[i] = Variable();
			}
		}

		void Object::ObjectHandleRef::IncRef() const noexcept
		{
			// fast path (count != 1): plain lock-free c -> c+1, lock bit never touched
			// boundary path (count == 1): SpinCAS itself performs the lock-acquire
			std::int32_t old = SpinCAS([](std::int32_t c) { return c == 1 ? (kLockBit | 1) : c + 1; });

			if (old == 1) {
				GetHandlePolicy()->PersistHandle(_handle);
				_refCountAndHandleLock.store(2, std::memory_order_release);
			}
		}

		std::uint32_t Object::ObjectHandleRef::DecRef() const noexcept
		{
			std::int32_t old = SpinCAS([](std::int32_t c) { return c == 2 ? (kLockBit | 2) : c - 1; });

			if (old == 2) {
				GetHandlePolicy()->ReleaseHandle(_handle);
				_refCountAndHandleLock.store(1, std::memory_order_release);
				return 1;
			}
			return static_cast<std::uint32_t>(old - 1);
		}

		std::uint32_t Object::ObjectHandleRef::GetRefCount() const noexcept
		{
			std::uint32_t spins = 0;
			while (true) {
				std::int32_t current = _refCountAndHandleLock.load(std::memory_order_relaxed);
				if ((current & kLockBit) == 0) {
					return static_cast<std::uint32_t>(current);
				}
				SpinBackoff(spins);
			}
		}

		VMHandle Object::ObjectHandleRef::GetHandle() const noexcept
		{
			// Always unconditionally called for `GetHandle()`, likely to create empty handle if it does not exist
			auto           _ = GetHandlePolicy()->EmptyHandle();
			std::int32_t   original = Lock();
			const VMHandle result = _handle;
			Unlock(original);
			return result;
		}

		void Object::ObjectHandleRef::ChangeHandle(const VMHandle a_newHandle) noexcept
		{
			const std::int32_t original = Lock();

			if (original > 1) {
				auto* policy = GetHandlePolicy();
				policy->PersistHandle(a_newHandle);
				policy->ReleaseHandle(_handle);
			}

			_handle = a_newHandle;
			Unlock(original);
		}

		template <class F>
		std::int32_t Object::ObjectHandleRef::SpinCAS(F a_computeDesired) const noexcept
		{
			std::uint32_t spins = 0;
			while (true) {
				std::int32_t current = _refCountAndHandleLock.load(std::memory_order_relaxed);
				if ((current & kLockBit) == 0) {
					std::int32_t desired = a_computeDesired(current);
					if (_refCountAndHandleLock.compare_exchange_weak(current, desired)) {
						return current;
					}
				} else {
					SpinBackoff(spins);
				}
			}
		}

		std::int32_t Object::ObjectHandleRef::Lock() const noexcept
		{
			return SpinCAS([](std::int32_t c) { return c | kLockBit; });
		}

		void Object::ObjectHandleRef::Unlock(std::int32_t a_original) const noexcept
		{
			_refCountAndHandleLock.store(a_original, std::memory_order_release);
		}

	}
}

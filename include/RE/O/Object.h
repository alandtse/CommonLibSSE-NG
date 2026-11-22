#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IObjectHandlePolicy.h"
#include "RE/M/MemoryManager.h"
#include "RE/S/Stack.h"
#include "RE/V/Variable.h"

namespace RE
{
	namespace BSScript
	{
		class Stack;
		class ObjectTypeInfo;

		class Object
		{
		public:
			struct ObjectHandleRef
			{
			public:
				void          IncRef() const noexcept;
				std::uint32_t DecRef() const noexcept;
				std::uint32_t GetRefCount() const noexcept;

				VMHandle GetHandle() const noexcept;
				void     ChangeHandle(const VMHandle a_newHandle) noexcept;

			private:
				template <class F>
				std::int32_t SpinCAS(F a_computeDesired) const noexcept;
				std::int32_t Lock() const noexcept;
				void         Unlock(std::int32_t a_original) const noexcept;

				VMHandle                          _handle{};               // 00
				mutable std::atomic<std::int32_t> _refCountAndHandleLock;  // 08
			};
			static_assert(sizeof(ObjectHandleRef) == 0x10);

			explicit Object(const BSTSmartPointer<ObjectTypeInfo>& a_type, IObjectHandlePolicy* a_policy, uint32_t a_numProperties);

			~Object();

			void Initialize();

			[[nodiscard]] VMHandle              GetHandle() const;
			ObjectTypeInfo*                     GetTypeInfo();
			[[nodiscard]] const ObjectTypeInfo* GetTypeInfo() const;
			[[nodiscard]] constexpr bool        IsConstructed() const noexcept { return static_cast<bool>(constructed); }
			[[nodiscard]] constexpr bool        IsInitialized() const noexcept { return static_cast<bool>(initialized); }
			[[nodiscard]] constexpr bool        IsValid() const noexcept { return static_cast<bool>(valid); }

			[[nodiscard]] void* Resolve(VMTypeID a_typeID) const;

			void          IncRef();
			std::uint32_t DecRef();

			Variable*                     GetProperty(const BSFixedString& a_name);
			[[nodiscard]] const Variable* GetProperty(const BSFixedString& a_name) const;
			Variable*                     GetVariable(const BSFixedString& a_name);
			[[nodiscard]] const Variable* GetVariable(const BSFixedString& a_name) const;

			[[nodiscard]] bool TryLockToStack(Stack* a_stack) noexcept;
			void               UnlockFromStack(Stack* a_stack) noexcept;
			void               LockPendingReset() noexcept;
			void               UnlockPendingReset() noexcept;

			[[nodiscard]] BSTSmartPointer<Stack> GetOwningStack() const noexcept;
			[[nodiscard]] bool                   IsPendingReset() const noexcept;

			void ReleaseProperties();

			TES_HEAP_REDEFINE_NEW();

			[[nodiscard]] inline void* operator new(std::size_t basesSize, size_t numVariables)
			{
				size_t     totalClassSize = basesSize + sizeof(Variable) * numVariables;
				const auto mem = RE::malloc(totalClassSize);
				if (mem) {
					return mem;
				} else {
					stl::report_and_fail("out of memory"sv);
				}
			}

			// members
			std::uint32_t                   constructed: 1;            // 00 - 0
			std::uint32_t                   initialized: 1;            // 00 - 1
			std::uint32_t                   valid: 1;                  // 00 - 2
			std::uint32_t                   remainingPropsToInit: 29;  // 00 - 3
			BSTSmartPointer<ObjectTypeInfo> type;                      // 08
			BSFixedString                   currentState;              // 10
			std::atomic<uintptr_t>          owningStack;               // 18 - stack that claims execution on this object, first bit used as pending reset flag
			ObjectHandleRef                 handleRef{};               // 20
			Variable                        variables[0];              // 30 - size == classPtr->GetTotalNumVariables() + 3
		};
		static_assert(sizeof(Object) == 0x30);
	}
}

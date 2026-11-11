#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/T/TypeInfo.h"
#include "RE/V/Variable.h"

namespace RE
{
	namespace BSScript
	{
		class Array : public BSIntrusiveRefCounted
		{
		public:
			using value_type = Variable;
			using size_type = std::uint32_t;
			using difference_type = std::int32_t;
			using reference = value_type&;
			using const_reference = const value_type&;
			using pointer = value_type*;
			using const_pointer = const value_type*;
			using iterator = value_type*;
			using const_iterator = const value_type*;
			using reverse_iterator = std::reverse_iterator<iterator>;
			using const_reverse_iterator = std::reverse_iterator<const_iterator>;

			explicit Array(const TypeInfo& a_typeInfo, uint32_t a_size);

			~Array();

			[[nodiscard]] inline void* operator new(std::size_t basesSize, size_t arraySize)
			{
				size_t     totalClassSize = basesSize + sizeof(Variable) * arraySize;
				const auto mem = RE::malloc(totalClassSize);
				if (mem) {
					return mem;
				} else {
					stl::report_and_fail("out of memory"sv);
				}
			}

			[[nodiscard]] reference operator[](size_type a_pos);

			[[nodiscard]] const_reference operator[](size_type a_pos) const;

			[[nodiscard]] reference front();

			[[nodiscard]] const_reference front() const;

			[[nodiscard]] reference back();

			[[nodiscard]] const_reference back() const;

			[[nodiscard]] pointer data() noexcept;

			[[nodiscard]] const_pointer data() const noexcept;

			[[nodiscard]] iterator begin() noexcept;

			[[nodiscard]] const_iterator begin() const noexcept;

			[[nodiscard]] const_iterator cbegin() const noexcept;

			[[nodiscard]] iterator end() noexcept;

			[[nodiscard]] const_iterator end() const noexcept;

			[[nodiscard]] const_iterator cend() const noexcept;

			[[nodiscard]] reverse_iterator rbegin() noexcept;

			[[nodiscard]] const_reverse_iterator rbegin() const noexcept;

			[[nodiscard]] const_reverse_iterator crbegin() const noexcept;

			[[nodiscard]] reverse_iterator rend() noexcept;

			[[nodiscard]] const_reverse_iterator rend() const noexcept;

			[[nodiscard]] const_reverse_iterator crend() const noexcept;

			[[nodiscard]] bool empty() const noexcept;

			[[nodiscard]] size_type size() const noexcept;

			[[nodiscard]] size_type max_size() const noexcept;

			[[nodiscard]] TypeInfo& type_info();

			[[nodiscard]] const TypeInfo& type_info() const;

			[[nodiscard]] TypeInfo::RawType type() const;

			BSSpinLock& getLock() const
			{
				return _lock;
			}

		private:
			static inline constexpr size_type MAX_SIZE = 128;

			// members
			[[maybe_unused]] std::uint32_t _pad04;        // 04
			TypeInfo                       _elementType;  // 08
			std::uint32_t                  _size;         // 10
			mutable BSSpinLock             _lock{};       // 14
			Variable                       _data[0];      // 20 - Size varies by array size
		};

		static_assert(sizeof(Array) == 0x20);  // Real size is 0x20 + _size * sizeof(Variable)
	}
}
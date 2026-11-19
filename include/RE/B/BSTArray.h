#pragma once

#include "RE/M/MemoryManager.h"

namespace RE
{
	class ScrapHeap;

	class BSTArrayBase
	{
	public:
		using size_type = std::uint32_t;

		class IAllocatorFunctor
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSTArrayBase__IAllocatorFunctor;
			inline static constexpr auto VTABLE = VTABLE_BSTArrayBase__IAllocatorFunctor;

			// add
			virtual bool Allocate(std::uint32_t a_num, std::uint32_t a_elemSize) = 0;                                                                                                             // 00
			virtual bool Reallocate(std::uint32_t a_minNewSizeInItems, std::uint32_t a_frontCopyCount, std::uint32_t a_shiftCount, std::uint32_t a_backCopyCount, std::uint32_t a_elemSize) = 0;  // 01
			virtual void Deallocate() = 0;                                                                                                                                                        // 02

			virtual ~IAllocatorFunctor() = default;  // 03

			TES_HEAP_REDEFINE_NEW();
		};
		static_assert(sizeof(IAllocatorFunctor) == 0x8);

		constexpr BSTArrayBase() noexcept = default;
		constexpr BSTArrayBase(const BSTArrayBase&) noexcept = default;
		constexpr BSTArrayBase(BSTArrayBase&& a_rhs) noexcept :
			_size(a_rhs.size())
		{
			a_rhs._size = 0;
		}

		inline ~BSTArrayBase() noexcept { _size = 0; }

		BSTArrayBase& operator=(const BSTArrayBase&) noexcept = default;
		BSTArrayBase& operator=(BSTArrayBase&& a_rhs) noexcept
		{
			_size = a_rhs.size();
			a_rhs._size = 0;
			return *this;
		}

		[[nodiscard]] constexpr bool      empty() const noexcept { return _size == 0; }
		[[nodiscard]] constexpr size_type size() const noexcept { return _size; }

	protected:
		constexpr void set_size(size_type a_size) noexcept { _size = a_size; }

	private:
		// members
		std::uint32_t _size{ 0 };  // 0
	};
	static_assert(sizeof(BSTArrayBase) == 0x4);

	class BSTArrayHeapAllocator
	{
	public:
		using size_type = std::uint32_t;

		constexpr BSTArrayHeapAllocator() noexcept = default;

		inline BSTArrayHeapAllocator(const BSTArrayHeapAllocator& a_rhs)
		{
			if (a_rhs.data()) {
				_capacity = a_rhs.capacity();
				_data = allocate(capacity());
				std::memcpy(data(), a_rhs.data(), capacity());
			}
		}

		constexpr BSTArrayHeapAllocator(BSTArrayHeapAllocator&& a_rhs) noexcept :
			_data(a_rhs.data()),
			_capacity(a_rhs.capacity())
		{
			a_rhs._data = nullptr;
			a_rhs._capacity = 0;
		}

		inline ~BSTArrayHeapAllocator()
		{
			deallocate(data());
			_data = nullptr;
			_capacity = 0;
		}

		inline BSTArrayHeapAllocator& operator=(const BSTArrayHeapAllocator& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				deallocate(data());
				_data = nullptr;
				_capacity = 0;

				if (a_rhs.data()) {
					_capacity = a_rhs.capacity();
					_data = allocate(capacity());
					std::memcpy(data(), a_rhs.data(), capacity());
				}
			}
			return *this;
		}

		inline BSTArrayHeapAllocator& operator=(BSTArrayHeapAllocator&& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				deallocate(data());
				_data = a_rhs.data();
				_capacity = a_rhs.capacity();

				a_rhs._data = nullptr;
				a_rhs._capacity = 0;
			}
			return *this;
		}

		TES_HEAP_REDEFINE_NEW();

		[[nodiscard]] constexpr void*       data() noexcept { return _data; }
		[[nodiscard]] constexpr const void* data() const noexcept { return _data; }

		[[nodiscard]] constexpr size_type capacity() const noexcept { return _capacity; }

	protected:
		inline void* allocate(std::size_t a_size)
		{
			const auto mem = malloc(a_size);
			if (!mem)
				stl::report_and_fail("out of memory");

			std::memset(mem, 0, a_size);
			return mem;
		}

		inline void deallocate(void* a_ptr) { free(a_ptr); }

		constexpr void set_allocator_traits(void* a_data, std::uint32_t a_capacity, std::size_t) noexcept
		{
			_data = a_data;
			_capacity = a_capacity;
		}

	private:
		// members
		void*         _data{ nullptr };  // 00
		std::uint32_t _capacity{ 0 };    // 08
	};
	static_assert(sizeof(BSTArrayHeapAllocator) == 0x10);

	template <std::uint32_t N>
	class BSTSmallArrayHeapAllocator
	{
	public:
		using size_type = std::uint32_t;

		constexpr BSTSmallArrayHeapAllocator() noexcept :
			_capacity(0),
			_local(1)
		{}

		inline BSTSmallArrayHeapAllocator(const BSTSmallArrayHeapAllocator& a_rhs) :
			_capacity(0),
			_local(1)
		{
			copy(a_rhs);
		}

		inline BSTSmallArrayHeapAllocator(BSTSmallArrayHeapAllocator&& a_rhs) :
			_capacity(0),
			_local(1)
		{
			copy(std::move(a_rhs));
		}

		inline ~BSTSmallArrayHeapAllocator() { release(); }

		inline BSTSmallArrayHeapAllocator& operator=(const BSTSmallArrayHeapAllocator& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				copy(a_rhs);
			}
			return *this;
		}

		inline BSTSmallArrayHeapAllocator& operator=(BSTSmallArrayHeapAllocator&& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				copy(std::move(a_rhs));
			}
			return *this;
		}

		TES_HEAP_REDEFINE_NEW();

		[[nodiscard]] constexpr void*       data() noexcept { return local() ? _data.local : _data.heap; }
		[[nodiscard]] constexpr const void* data() const noexcept { return local() ? _data.local : _data.heap; }

		[[nodiscard]] constexpr size_type capacity() const noexcept { return _capacity; }

	protected:
		void* allocate(std::size_t a_size)
		{
			if (a_size > N) {
				const auto mem = malloc(a_size);
				if (!mem)
					stl::report_and_fail("out of memory");

				std::memset(mem, 0, a_size);
				return mem;
			} else {
				return _data.local;
			}
		}

		void deallocate(void* a_ptr)
		{
			if (a_ptr != _data.local) {
				free(a_ptr);
			}
		}

		constexpr void set_allocator_traits(void* a_data, std::uint32_t a_capacity, std::size_t a_typeSize) noexcept
		{
			_capacity = a_capacity;
			if (a_capacity * a_typeSize > N) {
				_local = 0;
				_data.heap = a_data;
			}
		}

	private:
		union Data
		{
			void* heap;
			char  local[N]{ 0 };
		};

		inline void copy(const BSTSmallArrayHeapAllocator& a_rhs)
		{
			release();

			_capacity = a_rhs._capacity;
			_local = a_rhs._local;

			if (!local()) {
				const auto mem = malloc(capacity());
				if (!mem) {
					stl::report_and_fail("out of memory"sv);
				} else {
					_data.heap = mem;
				}
			}

			std::memcpy(data(), a_rhs.data(), capacity());
		}

		inline void copy(BSTSmallArrayHeapAllocator&& a_rhs)
		{
			release();

			_capacity = a_rhs._capacity;
			_local = a_rhs._local;
			std::memmove(data(), a_rhs.data(), capacity());

			std::memset(a_rhs.data(), 0, a_rhs.capacity());
			a_rhs._capacity = N;
			a_rhs._local = 1;
		}

		[[nodiscard]] constexpr bool local() const noexcept { return _local != 0; }

		inline void release()
		{
			if (!local()) {
				free(_data.heap);
			}

			std::memset(data(), 0, capacity());
			_capacity = N;
			_local = 1;
		}

		// members
		std::uint32_t _capacity: 31;  // 00
		std::uint32_t _local: 1;      // 00
		Data          _data;          // 08
	};

	class BSScrapArrayAllocator
	{
	public:
		using size_type = std::uint32_t;

		constexpr BSScrapArrayAllocator() noexcept = default;

		inline BSScrapArrayAllocator(const BSScrapArrayAllocator& a_rhs) :
			_capacity(a_rhs._capacity)
		{
			if (capacity() > 0) {
				_data = allocate(capacity());
				std::memcpy(data(), a_rhs.data(), capacity());
			}
		}

		constexpr BSScrapArrayAllocator(BSScrapArrayAllocator&& a_rhs) noexcept :
			_allocator(a_rhs._allocator),
			_data(a_rhs._data),
			_capacity(a_rhs._capacity)
		{
			a_rhs._allocator = nullptr;
			a_rhs._data = nullptr;
			a_rhs._capacity = 0;
		}

		~BSScrapArrayAllocator();

		inline BSScrapArrayAllocator& operator=(const BSScrapArrayAllocator& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				if (_data) {
					deallocate(_data);
					_data = nullptr;
				}

				_capacity = a_rhs.capacity();
				if (capacity() > 0) {
					_data = allocate(capacity());
					std::memcpy(data(), a_rhs.data(), capacity());
				}
			}
			return *this;
		}

		inline BSScrapArrayAllocator& operator=(BSScrapArrayAllocator&& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				if (_data) {
					deallocate(_data);
				}

				_allocator = a_rhs._allocator;
				_data = a_rhs._data;
				_capacity = a_rhs._capacity;

				a_rhs._allocator = nullptr;
				a_rhs._data = nullptr;
				a_rhs._capacity = 0;
			}
			return *this;
		}

		TES_HEAP_REDEFINE_NEW();

		[[nodiscard]] constexpr void*       data() noexcept { return _data; }
		[[nodiscard]] constexpr const void* data() const noexcept { return _data; }

		[[nodiscard]] constexpr size_type capacity() const noexcept { return _capacity; }

	protected:
		void* allocate(std::size_t a_size);
		void  deallocate(void* a_ptr);

		constexpr void set_allocator_traits(void* a_data, std::uint32_t a_capacity, std::size_t) noexcept
		{
			_data = a_data;
			_capacity = a_capacity;
		}

	private:
		// members
		ScrapHeap* _allocator{ nullptr };  // 00
		void*      _data{ nullptr };       // 08
		size_type  _capacity{ 0 };         // 10
	};
	static_assert(sizeof(BSScrapArrayAllocator) == 0x18);

	template <class T, class Allocator = BSTArrayHeapAllocator>
	class BSTArray :
		public Allocator,
		public BSTArrayBase
	{
	public:
		using allocator_type = Allocator;
		using size_type = typename BSTArrayBase::size_type;
		using value_type = T;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;

		BSTArray() = default;

		inline BSTArray(const BSTArray& a_rhs)
		{
			const auto newCapacity = a_rhs.capacity();
			if (newCapacity == 0) {
				return;
			}

			const auto newSize = a_rhs.size();
			const auto newData = allocate(newCapacity);
			for (size_type i = 0; i < newSize; ++i) {
				std::construct_at(newData + i, a_rhs[i]);
			}

			set_allocator_traits(newData, newCapacity);
			set_size(newSize);
		}

		inline BSTArray(const std::initializer_list<T> a_list)
		{
			if (a_list.size() == 0) {
				return;
			}

			const auto newSize = a_list.size();
			const auto newData = allocate(newSize);
			size_type  i = 0;
			for (const auto& elem : a_list) {
				std::construct_at(newData + i++, elem);
			}

			set_allocator_traits(newData, newSize);
			set_size(newSize);
		}

		BSTArray(BSTArray&&) = default;

		explicit inline BSTArray(size_type a_count)
		{
			if (a_count == 0) {
				return;
			}

			const auto newCapacity = a_count;
			const auto newSize = a_count;
			const auto newData = allocate(newCapacity);
			for (size_type i = 0; i < newSize; ++i) {
				std::construct_at(newData + i);
			}

			set_allocator_traits(newData, newCapacity);
			set_size(newSize);
		}

		inline ~BSTArray() { release(); }

		inline BSTArray& operator=(const BSTArray& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				clear();

				const auto newCapacity = a_rhs.capacity();
				change_capacity(newCapacity);

				const auto newSize = a_rhs.size();
				set_size(newSize);

				const auto newData = data();
				for (size_type i = 0; i < newSize; ++i) {
					std::construct_at(newData + i, a_rhs[i]);
				}
			}
			return *this;
		}

		BSTArray& operator=(BSTArray&& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				release();

				const auto newCapacity = a_rhs.capacity();
				const auto newSize = a_rhs.size();
				const auto newData = a_rhs.data();

				set_allocator_traits(newData, newCapacity);
				a_rhs.set_allocator_traits(0, 0);

				set_size(newSize);
				a_rhs.set_size(0);
			}
			return *this;
		}

		TES_HEAP_REDEFINE_NEW();

		[[nodiscard]] constexpr reference operator[](size_type a_pos) noexcept
		{
			assert(a_pos < size());
			return data()[a_pos];
		}

		[[nodiscard]] constexpr const_reference operator[](size_type a_pos) const noexcept
		{
			assert(a_pos < size());
			return data()[a_pos];
		}

		[[nodiscard]] constexpr reference       front() noexcept { return operator[](0); }
		[[nodiscard]] constexpr const_reference front() const noexcept { return operator[](0); }

		[[nodiscard]] constexpr reference       back() noexcept { return operator[](size() - 1); }
		[[nodiscard]] constexpr const_reference back() const noexcept { return operator[](size() - 1); }

		[[nodiscard]] constexpr pointer       data() noexcept { return static_cast<pointer>(allocator_type::data()); }
		[[nodiscard]] constexpr const_pointer data() const noexcept { return static_cast<const_pointer>(allocator_type::data()); }

		[[nodiscard]] constexpr iterator       begin() noexcept { return empty() ? nullptr : data(); }
		[[nodiscard]] constexpr const_iterator begin() const noexcept { return empty() ? nullptr : data(); }
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] constexpr iterator       end() noexcept { return empty() ? nullptr : data() + size(); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return empty() ? nullptr : data() + size(); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] constexpr bool empty() const noexcept { return BSTArrayBase::empty(); }

		[[nodiscard]] constexpr size_type size() const noexcept { return BSTArrayBase::size(); }

		inline void reserve(size_type a_newCap)
		{
			if (a_newCap > capacity()) {
				change_capacity(a_newCap);
			}
		}

		[[nodiscard]] constexpr size_type capacity() const noexcept { return allocator_type::capacity(); }

		inline void shrink_to_fit()
		{
			const auto newCapacity = size();
			if (newCapacity != capacity()) {
				change_capacity(newCapacity);
			}
		}

		inline void clear()
		{
			if (!empty()) {
				change_size(0);
			}
		}

		inline iterator erase(const_iterator a_pos)
		{
			auto                    pos = const_cast<iterator>(a_pos);
			std::optional<iterator> result;
			if (pos != begin()) {
				result = pos - 1;
			}

			for (auto prev = pos++; pos != cend(); prev = pos++) {
				*prev = std::move(*pos);
			}
			pop_back();

			return result ? *result + 1 : begin();
		}

		inline void push_back(const value_type& a_value) { emplace_back(a_value); }
		inline void push_back(value_type&& a_value) { emplace_back(std::move(a_value)); }

		template <class... Args>
		inline reference emplace_back(Args&&... a_args)
		{
			if (size() == capacity()) {
				grow_capacity();
			}

			set_size(size() + 1);
			auto& elem = back();
			std::construct_at(std::addressof(elem), std::forward<Args>(a_args)...);
			return elem;
		}

		inline void insert(const_iterator position, const value_type& a_value) { emplace(position, a_value); }
		inline void insert(const_iterator position, value_type&& a_value) { emplace(position, std::move(a_value)); }

		inline void push_front(const value_type& a_value) { emplace(cbegin(), a_value); }
		inline void push_front(value_type&& a_value) { emplace(cbegin(), std::move(a_value)); }

		template <class... Args>
		inline reference emplace(const_iterator position, Args&&... a_args)
		{
			assert(position >= cbegin() && position <= cend());

			if (position == cend()) {
				return emplace_back(std::forward<Args>(a_args)...);
			}

			pointer   oldData;
			pointer   newData;
			size_type newCapacity;

			if (size() == capacity()) {
				newCapacity = next_capacity();
				newData = allocate(newCapacity);  // manually grow capacity to avoid unnecessary memcpy from change_capacity
				oldData = data();
			} else {
				newData = data();
				oldData = nullptr;
				newCapacity = capacity();
			}

			const auto headPartToCopy = position - cbegin();
			const auto tailPartToCopy = cend() - position;
			const auto tailBytesToCopy = tailPartToCopy * sizeof(T);
			std::memcpy(newData + headPartToCopy + 1, cend() - tailPartToCopy, tailBytesToCopy);
			std::construct_at(newData + headPartToCopy, std::forward<Args>(a_args)...);
			const auto headBytesToCopy = headPartToCopy * sizeof(T);
			std::memcpy(newData, cbegin(), headBytesToCopy);

			if (oldData) {
				deallocate(oldData);
				set_allocator_traits(newData, newCapacity);
			}

			set_size(size() + 1);

			return *(newData + headPartToCopy);
		}

		inline void pop_back()
		{
			assert(!empty());
			std::destroy_at(std::addressof(back()));
			set_size(size() - 1);
		}

		inline void resize(size_type a_count)
		{
			if (a_count != size()) {
				change_size(a_count);
			}
		}

		inline void resize(size_type a_count, const value_type& a_value)
		{
			if (a_count != size()) {
				change_size(a_count, a_value);
			}
		}

	private:
		static constexpr size_type DF_CAP = 4;           // beth default
		static constexpr float     GROWTH_FACTOR = 2.0;  // not part of native type

		[[nodiscard]] inline pointer allocate(size_type a_num)
		{
			return static_cast<pointer>(allocator_type::allocate(a_num * sizeof(value_type)));
		}

		inline void deallocate(void* a_ptr) { allocator_type::deallocate(a_ptr); }

		constexpr void set_allocator_traits(void* a_data, size_type a_capacity) noexcept
		{
			allocator_type::set_allocator_traits(a_data, a_capacity, sizeof(value_type));
		}

		constexpr void set_size(size_type a_size) noexcept { BSTArrayBase::set_size(a_size); }

		inline void change_capacity(size_type a_newCapacity)
		{
			const auto newData = a_newCapacity > 0 ? allocate(a_newCapacity) : nullptr;
			const auto oldData = data();
			if (oldData) {
				const auto oldCapacity = capacity();
				if (newData) {
					const auto bytesToCopy = (std::min)(oldCapacity, a_newCapacity) * sizeof(value_type);
#ifdef __clang__
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wnontrivial-memaccess"
#endif
					std::memcpy(newData, oldData, bytesToCopy);
#ifdef __clang__
#	pragma clang diagnostic pop
#endif
				}
				deallocate(oldData);
			}
			set_allocator_traits(newData, a_newCapacity);
		}

		template <class... Args>
		inline void change_size(size_type a_newSize, Args&&... a_args)
		{
			if (a_newSize > capacity()) {
				grow_capacity(a_newSize);
			}

			const auto oldSize = size();
			if (a_newSize > oldSize) {
				for (size_type i = oldSize; i < a_newSize; ++i) {
					std::construct_at(data() + i, std::forward<Args>(a_args)...);
				}
			} else {
				for (size_type i = a_newSize; i < oldSize; ++i) {
					std::destroy_at(data() + i);
				}
			}

			set_size(a_newSize);
		}

		/// Calculates the next value for the array capacity.
		/// Capacity grows exponentially: hint * 2^level, where level is the number of times the capacity has grown.
		[[nodiscard]] inline size_type next_capacity() const { return next_capacity(capacity()); }

		/// Calculates the next value for the array capacity.
		/// Capacity grows exponentially: hint * 2^level, where level is the number of times the capacity has grown.
		inline size_type next_capacity(size_type a_hint) const
		{
			auto cap = a_hint;
			cap = cap > 0 ? static_cast<size_type>(std::ceil(static_cast<float>(cap) * GROWTH_FACTOR)) : DF_CAP;
			return cap;
		}

		inline void grow_capacity() { grow_capacity(capacity()); }

		inline void grow_capacity(size_type a_hint)
		{
			change_capacity(next_capacity(a_hint));
		}

		inline void release()
		{
			clear();
			change_capacity(0);
		}
	};

	template <class T, std::uint32_t N = 1>
	using BSTSmallArray = BSTArray<T, BSTSmallArrayHeapAllocator<sizeof(T) * N>>;

	template <class T>
	using BSScrapArray = BSTArray<T, BSScrapArrayAllocator>;

	template <class T>
	class BSStaticArray
	{
	public:
		using value_type = T;
		using size_type = std::uint32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;

		[[nodiscard]] constexpr reference operator[](size_type a_pos) noexcept
		{
			assert(a_pos < _size);
			return _data[a_pos];
		}

		[[nodiscard]] constexpr const_reference operator[](size_type a_pos) const noexcept
		{
			assert(a_pos < _size);
			return _data[a_pos];
		}

		[[nodiscard]] constexpr reference       front() noexcept { return operator[](0); }
		[[nodiscard]] constexpr const_reference front() const noexcept { return operator[](0); }

		[[nodiscard]] constexpr reference       back() noexcept { return operator[](size() - 1); }
		[[nodiscard]] constexpr const_reference back() const noexcept { return operator[](size() - 1); }

		[[nodiscard]] constexpr pointer       data() noexcept { return _data; }
		[[nodiscard]] constexpr const_pointer data() const noexcept { return _data; }

		[[nodiscard]] constexpr iterator       begin() noexcept { return empty() ? nullptr : data(); }
		[[nodiscard]] constexpr const_iterator begin() const noexcept { return empty() ? nullptr : data(); }
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] constexpr iterator       end() noexcept { return empty() ? nullptr : data() + size(); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return empty() ? nullptr : data() + size(); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] constexpr bool empty() const noexcept { return size() == 0; }

		[[nodiscard]] constexpr size_type size() const noexcept { return _size; }

	private:
		// members
		pointer       _data{ nullptr };  // 00
		std::uint32_t _size{ 0 };        // 08
	};

	template <class T>
	class BSTSmallSharedArray
	{
	public:
		using size_type = typename std::uint32_t;
		using value_type = T;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;

		static_assert(std::is_nothrow_copy_constructible_v<T>, "BSTSmallSharedArray requires T to be nothrow copy constructible");
		static_assert(std::is_nothrow_move_constructible_v<T>, "BSTSmallSharedArray requires T to be nothrow move constructible");
		static_assert(std::is_nothrow_move_assignable_v<T>, "BSTSmallSharedArray requires T to be nothrow move assignable");
		static_assert(std::is_nothrow_destructible_v<T>, "BSTSmallSharedArray requires T to be nothrow destructible");
		static_assert(alignof(T) <= alignof(std::max_align_t), "BSTSmallSharedArray's heap allocation path does not support T with an over-aligned requirement");

		constexpr BSTSmallSharedArray() noexcept = default;

		inline BSTSmallSharedArray(const BSTSmallSharedArray& a_rhs)
		{
			const auto newCapacity = a_rhs.capacity();
			if (newCapacity == 0) {
				return;
			}

			const auto newSize = a_rhs.size();
			const auto newData = allocate(newCapacity);
			for (size_type i = 0; i < newSize; ++i) {
				std::construct_at(newData + i, a_rhs[i]);
			}

			if (newData != &_data.local) {
				_data.heap = newData;
			}
			_capacity = newCapacity;
			set_size(newSize);
		}

		inline BSTSmallSharedArray(const std::initializer_list<T> a_list)
		{
			if (a_list.size() == 0) {
				return;
			}

			const auto newSize = static_cast<size_type>(a_list.size());
			const auto newData = allocate(newSize);
			size_type  i = 0;
			for (const auto& elem : a_list) {
				std::construct_at(newData + i++, elem);
			}

			if (newData != &_data.local) {
				_data.heap = newData;
			}
			_capacity = newSize;
			set_size(newSize);
		}

		BSTSmallSharedArray(BSTSmallSharedArray&& a_rhs) noexcept
		{
			const auto newCapacity = a_rhs._capacity;
			const auto newSize = a_rhs._size;

			if (newSize == 1) {
				// The local value may be larger than a pointer, so move the whole value
				// through its own move constructor instead of only copying sizeof(void*)
				// bytes of it (which is all `_data.heap = a_rhs._data.heap;` would move).
				std::construct_at(std::addressof(_data.local), std::move(a_rhs._data.local));
				std::destroy_at(std::addressof(a_rhs._data.local));
			} else if (newSize > 1) {
				_data.heap = a_rhs._data.heap;
				a_rhs._data.heap = nullptr;
			}

			_capacity = newCapacity;
			_size = newSize;

			a_rhs._capacity = 0;
			a_rhs._size = 0;
		}

		inline ~BSTSmallSharedArray()
		{
			release();
		}

		inline BSTSmallSharedArray& operator=(const BSTSmallSharedArray& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				clear();

				const auto newCapacity = a_rhs.capacity();
				change_capacity(newCapacity);

				const auto newSize = a_rhs.size();
				set_size(newSize);

				const auto newData = data();
				for (size_type i = 0; i < newSize; ++i) {
					std::construct_at(newData + i, a_rhs[i]);
				}
			}
			return *this;
		}

		BSTSmallSharedArray& operator=(BSTSmallSharedArray&& a_rhs) noexcept
		{
			if (this != std::addressof(a_rhs)) {
				release();

				const auto newCapacity = a_rhs.capacity();
				const auto newSize = a_rhs.size();
				const auto newData = a_rhs.data();

				if (newSize == 1) {
					// release() left the destination's local slot with no live T, so it must be
					// placement-constructed rather than assigned into.
					std::construct_at(std::addressof(_data.local), std::move(a_rhs._data.local));
					std::destroy_at(std::addressof(a_rhs._data.local));
				} else if (newSize > 1) {
					_data.heap = newData;
					a_rhs._data.heap = nullptr;
				}

				_capacity = newCapacity;
				a_rhs._capacity = 0;

				set_size(newSize);
				a_rhs.set_size(0);
			}
			return *this;
		}

		TES_HEAP_REDEFINE_NEW();

		[[nodiscard]] constexpr reference operator[](size_type a_pos) noexcept
		{
			assert(a_pos < size());
			return data()[a_pos];
		}

		[[nodiscard]] constexpr const_reference operator[](size_type a_pos) const noexcept
		{
			assert(a_pos < size());
			return data()[a_pos];
		}

		[[nodiscard]] constexpr reference       front() noexcept { return operator[](0); }
		[[nodiscard]] constexpr const_reference front() const noexcept { return operator[](0); }

		[[nodiscard]] constexpr reference       back() noexcept { return operator[](size() - 1); }
		[[nodiscard]] constexpr const_reference back() const noexcept { return operator[](size() - 1); }

		[[nodiscard]] inline pointer data() noexcept
		{
			return size() > 1 ? _data.heap : std::addressof(_data.local);
		}

		[[nodiscard]] inline const_pointer data() const noexcept
		{
			return size() > 1 ? _data.heap : std::addressof(_data.local);
		}

		[[nodiscard]] constexpr iterator       begin() noexcept { return empty() ? nullptr : data(); }
		[[nodiscard]] constexpr const_iterator begin() const noexcept { return empty() ? nullptr : data(); }
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] constexpr iterator       end() noexcept { return empty() ? nullptr : data() + size(); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return empty() ? nullptr : data() + size(); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] constexpr bool empty() const noexcept { return _size == 0; }

		[[nodiscard]] constexpr size_type size() const noexcept { return _size; }

		[[nodiscard]] constexpr size_type capacity() const noexcept { return _capacity; }

		inline void clear()
		{
			if (!empty()) {
				change_size(0);
			}
		}

		// The real BSTSmallSharedArray uses a swap & pop on the last element, favoring O(1) time complexity
		// over order preservation. This behavior is matched here
		inline iterator erase(const_iterator a_pos)
		{
			assert(a_pos >= cbegin() && a_pos < cend());

			const auto index = static_cast<size_type>(a_pos - cbegin());
			if (index != size() - 1) {
				(*this)[index] = std::move(back());
			}
			pop_back();

			// pop_back() could transition the heap back to a local buffer, so index has
			// to be re-calculated
			return index < size() ? (begin() + index) : end();
		}

		inline void push_back(const value_type& a_value) { emplace_back(a_value); }
		inline void push_back(value_type&& a_value) { emplace_back(std::move(a_value)); }

		template <class... Args>
		inline reference emplace_back(Args&&... a_args)
		{
			static_assert(std::is_nothrow_constructible_v<T, Args...>, "BSTSmallSharedArray::emplace_back requires T to be nothrow constructible from the given arguments");

			// a_args may alias an existing element (e.g. push_back(arr[0])), and growing
			// storage can overwrite the inline slot or free the heap block it lives in, so
			// the new element is built in independent storage before that can happen.
			std::optional<value_type> temp(std::in_place, std::forward<Args>(a_args)...);

			if (size() == capacity()) {
				change_capacity(_capacity + 1);
			}

			set_size(size() + 1);
			auto& elem = back();
			std::construct_at(std::addressof(elem), std::move(*temp));
			return elem;
		}

		inline void insert(const_iterator position, const value_type& a_value) { emplace(position, a_value); }
		inline void insert(const_iterator position, value_type&& a_value) { emplace(position, std::move(a_value)); }

		inline void push_front(const value_type& a_value) { emplace(cbegin(), a_value); }
		inline void push_front(value_type&& a_value) { emplace(cbegin(), std::move(a_value)); }

		template <class... Args>
		inline reference emplace(const_iterator position, Args&&... a_args)
		{
			static_assert(std::is_nothrow_constructible_v<T, Args...>, "BSTSmallSharedArray::emplace requires T to be nothrow constructible from the given arguments");

			assert(position >= cbegin() && position <= cend());

			if (position == cend()) {
				return emplace_back(std::forward<Args>(a_args)...);
			}

			// Build the new element before touching any existing storage: a_args may alias
			// an existing element, and either branch below can relocate or free it.
			std::optional<value_type> temp(std::in_place, std::forward<Args>(a_args)...);

			const auto headCount = static_cast<size_type>(position - cbegin());
			const auto oldSize = size();

			pointer   newData;
			size_type newCapacity;
			bool      grew;

			if (size() == capacity()) {
				grew = true;
				newCapacity = _capacity + 1;
				const auto oldData = data();
				newData = allocate(newCapacity);

				// Relocate every existing element into the new buffer through its own move
				// constructor, then destroy the original: a nontrivial T's move constructor
				// may need to run (e.g. to repair a self-referential address), so a byte
				// copy cannot stand in for it.
				for (size_type i = 0; i < headCount; ++i) {
					std::construct_at(newData + i, std::move(oldData[i]));
					std::destroy_at(oldData + i);
				}
				for (size_type i = headCount; i < oldSize; ++i) {
					std::construct_at(newData + i + 1, std::move(oldData[i]));
					std::destroy_at(oldData + i);
				}

				deallocate(oldData);
			} else {
				grew = false;
				newCapacity = capacity();
				newData = data();

				// Shift the tail back one slot, moving from the end so no live element is
				// overwritten before it has itself been moved out of.
				for (size_type i = oldSize; i > headCount; --i) {
					std::construct_at(newData + i, std::move(newData[i - 1]));
					std::destroy_at(newData + i - 1);
				}
			}

			std::construct_at(newData + headCount, std::move(*temp));

			if (grew) {
				_data.heap = newData;
				_capacity = newCapacity;
			}

			set_size(oldSize + 1);

			return *(newData + headCount);
		}

		inline void pop_back()
		{
			assert(!empty());
			std::destroy_at(std::addressof(back()));
			set_size(size() - 1);
		}

	private:
		[[nodiscard]] inline pointer allocate(size_type a_num)
		{
			if (a_num <= 1) {
				return std::addressof(_data.local);
			}

			auto mem = calloc<value_type>(a_num);
			if (!mem)
				stl::report_and_fail("out of memory");
			return mem;
		}

		inline void deallocate(void* a_ptr)
		{
			if (_capacity < 2) {
				// Local element, no deallocation
				return;
			}

			RE::free(a_ptr);
		}

		constexpr void set_size(size_type a_size) noexcept
		{
			// Handle Heap -> Local transition
			const auto oldSize = _size;
			if (a_size == 0 && oldSize >= 2) {
				// Heap -> Inline, no surviving element
				RE::free(_data.heap);
				_data.heap = nullptr;
				_capacity = 0;
			} else if (a_size == 0 && oldSize == 1) {
				_data.heap = nullptr;
				_capacity = 0;
			} else if (a_size == 1 && oldSize >= 2) {
				// Heap -> Inline transition, 1 surviving element
				value_type survivor = std::move(_data.heap[0]);
				std::destroy_at(std::addressof(_data.heap[0]));
				RE::free(_data.heap);
				_data.heap = nullptr;
				std::construct_at(std::addressof(_data.local), std::move(survivor));  // placement-construct, not assignment
				_capacity = 1;
			}

			_size = a_size;
		}

		inline void change_capacity(size_type a_newCapacity)
		{
			const auto newData = a_newCapacity > 0 ? allocate(a_newCapacity) : nullptr;
			const auto oldData = data();
			if (oldData) {
				if (newData && newData != oldData) {
					// Relocate live elements through T's own move constructor rather than a
					// byte copy: a nontrivial T (e.g. one that stores and repairs its own
					// address) is not safe to relocate by bytes alone.
					const auto elementsToMove = (std::min)(size(), a_newCapacity);
					for (size_type i = 0; i < elementsToMove; ++i) {
						std::construct_at(newData + i, std::move(oldData[i]));
						std::destroy_at(oldData + i);
					}
				}
				deallocate(oldData);
			}
			_data.heap = newData;
			_capacity = a_newCapacity;
		}

		inline void change_size(size_type a_newSize)
		{
			if (a_newSize > capacity()) {
				change_capacity(a_newSize);
			}

			const auto oldSize = size();
			if (a_newSize <= oldSize) {
				for (size_type i = a_newSize; i < oldSize; ++i) {
					std::destroy_at(data() + i);
				}
			}

			set_size(a_newSize);
		}

		inline void release()
		{
			clear();
			change_capacity(0);
		}

		union Data
		{
			~Data(){};

			pointer    heap{ 0 };
			value_type local;
		};

		// members
		std::uint32_t _size{ 0 };      // 00
		std::uint32_t _capacity{ 0 };  // 04
		Data          _data{ 0 };      // 08
	};
	static_assert(sizeof(BSTSmallSharedArray<void*>) == 0x10);

}

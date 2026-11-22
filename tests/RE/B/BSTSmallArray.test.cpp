#include "catch2/catch_all.hpp"

#include "RE/B/BSTArray.h"

#include <vector>

namespace
{
	template <class T>
	using TestSmallArray = RE::BSTSmallArray<T, 4>;

	template <class T, class Allocator>
	[[nodiscard]] bool UsesLocalBuffer(const RE::BSTArray<T, Allocator>& a_arr) noexcept
	{
		if (a_arr.empty()) {
			return true;
		}

		const auto arrBegin = reinterpret_cast<std::uintptr_t>(std::addressof(a_arr));
		const auto arrEnd = arrBegin + sizeof(a_arr);
		const auto dataAddr = reinterpret_cast<std::uintptr_t>(std::addressof(a_arr[0]));
		return dataAddr >= arrBegin && dataAddr < arrEnd;
	}

	struct LifecycleTracker
	{
		static inline int liveCount = 0;
		static inline int corruptionCount = 0;

		static void Reset()
		{
			liveCount = 0;
			corruptionCount = 0;
		}

		explicit LifecycleTracker(int a_value = 0) :
			value(a_value)
		{
			++liveCount;
		}

		LifecycleTracker(const LifecycleTracker& a_rhs) :
			value(a_rhs.value)
		{
			a_rhs.CheckAlive();
			++liveCount;
		}

		LifecycleTracker(LifecycleTracker&& a_rhs) noexcept :
			value(a_rhs.value)
		{
			a_rhs.CheckAlive();
			++liveCount;
		}

		LifecycleTracker& operator=(const LifecycleTracker& a_rhs)
		{
			CheckAlive();
			a_rhs.CheckAlive();
			value = a_rhs.value;
			return *this;
		}

		LifecycleTracker& operator=(LifecycleTracker&& a_rhs) noexcept
		{
			CheckAlive();
			a_rhs.CheckAlive();
			value = a_rhs.value;
			return *this;
		}

		~LifecycleTracker()
		{
			CheckAlive();
			_magic = 0;
			--liveCount;
		}

		int value;

	private:
		void CheckAlive() const
		{
			if (_magic != kMagic) {
				++corruptionCount;
			}
		}

		static constexpr std::uint32_t kMagic = 0xC0FFEE;
		std::uint32_t                  _magic{ kMagic };
	};

	// Larger than a pointer on purpose - a byte-level move that only transfers pointer-sized
	// bytes out of the local buffer would leave `z` wrong.
	struct Vec3
	{
		int x;
		int y;
		int z;
	};
	static_assert(sizeof(Vec3) > sizeof(void*));
}

TEST_CASE("BSTSmallArray/DefaultConstruction", "[unit]")
{
	TestSmallArray<int> arr;
	CHECK(arr.empty());
	CHECK(arr.size() == 0);
	CHECK(arr.capacity() == 0);
	CHECK(arr.begin() == arr.end());
	CHECK(arr.begin() == nullptr);
}

TEST_CASE("BSTSmallArray/DefaultTemplateParameterGrowsToHeapImmediately", "[unit]")
{
	RE::BSTSmallArray<int> grown;
	grown.push_back(1);
	CHECK_FALSE(UsesLocalBuffer(grown));

	RE::BSTSmallArray<int> exact{ 1 };
	CHECK(UsesLocalBuffer(exact));
}

TEST_CASE("BSTSmallArray/LocalBufferGrowth", "[unit]")
{
	TestSmallArray<int> arr;

	SECTION("push_back fills the inline buffer without allocating")
	{
		for (int i = 1; i <= 4; ++i) {
			arr.push_back(i);
			CHECK(UsesLocalBuffer(arr));
		}
		CHECK(arr.size() == 4);
		CHECK(arr.capacity() == 4);
		for (int i = 0; i < 4; ++i) {
			CHECK(arr[i] == i + 1);
		}
	}

	SECTION("a fifth element overflows to the heap")
	{
		for (int i = 1; i <= 4; ++i) {
			arr.push_back(i);
		}
		REQUIRE(UsesLocalBuffer(arr));

		arr.push_back(5);
		CHECK_FALSE(UsesLocalBuffer(arr));
		REQUIRE(arr.size() == 5);
		for (int i = 0; i < 5; ++i) {
			CHECK(arr[i] == i + 1);
		}
	}

	SECTION("emplace_back forwards constructor arguments and returns a reference to the slot")
	{
		auto& ref = arr.emplace_back(7);
		CHECK(std::addressof(ref) == std::addressof(arr[0]));
		CHECK(arr[0] == 7);
		CHECK(UsesLocalBuffer(arr));
	}

	SECTION("initializer-list construction with fewer elements than the inline capacity stays local")
	{
		TestSmallArray<int> single{ 9 };
		CHECK(single.size() == 1);
		CHECK(single.capacity() == 1);
		CHECK(single[0] == 9);
		CHECK(UsesLocalBuffer(single));
	}

	SECTION("initializer-list construction with zero elements stays empty")
	{
		TestSmallArray<int> none(std::initializer_list<int>{});
		CHECK(none.empty());
		CHECK(none.capacity() == 0);
	}
}

TEST_CASE("BSTSmallArray/CopySemantics", "[unit]")
{
	SECTION("copying a local-backed array is independent of the source")
	{
		TestSmallArray<int> src;
		src.push_back(1);
		src.push_back(2);
		REQUIRE(UsesLocalBuffer(src));

		TestSmallArray<int> copy(src);
		REQUIRE(copy.size() == 2);
		CHECK(copy[0] == 1);
		CHECK(copy[1] == 2);

		copy[0] = 999;
		CHECK(src[0] == 1);
	}

	SECTION("copying a heap-backed array is a deep, independent copy")
	{
		TestSmallArray<int> src;
		for (int i = 1; i <= 6; ++i) {
			src.push_back(i);
		}
		REQUIRE_FALSE(UsesLocalBuffer(src));

		TestSmallArray<int> copy(src);
		REQUIRE(copy.size() == 6);
		for (int i = 0; i < 6; ++i) {
			CHECK(copy[i] == i + 1);
		}

		copy[0] = -1;
		CHECK(src[0] == 1);
	}

	SECTION("copy assignment replaces existing contents")
	{
		TestSmallArray<int> src;
		src.push_back(5);

		TestSmallArray<int> dst;
		dst.push_back(1);
		dst.push_back(2);
		dst.push_back(3);
		dst = src;

		REQUIRE(dst.size() == 1);
		CHECK(dst[0] == 5);
	}

	SECTION("self copy-assignment is a no-op")
	{
		TestSmallArray<int> arr;
		arr.push_back(1);
		arr.push_back(2);

		// Routed through a pointer so this doesn't read as a literal `arr = arr;`, which
		// clang flags with -Wself-assign-overloaded under this project's /WX.
		auto* self = &arr;
		arr = *self;

		REQUIRE(arr.size() == 2);
		CHECK(arr[0] == 1);
		CHECK(arr[1] == 2);
	}

	SECTION("self move-assignment is a no-op")
	{
		TestSmallArray<int> arr;
		arr.push_back(1);
		arr.push_back(2);

		auto* self = &arr;
		arr = std::move(*self);

		REQUIRE(arr.size() == 2);
		CHECK(arr[0] == 1);
		CHECK(arr[1] == 2);
	}
}

TEST_CASE("BSTSmallArray/MoveConstructFromEmpty", "[unit]")
{
	TestSmallArray<int> src;
	TestSmallArray<int> moved(std::move(src));
	CHECK(moved.empty());
	CHECK(src.empty());
}

TEST_CASE("BSTSmallArray/MoveConstructFromLocalPreservesValues", "[unit]")
{
	LifecycleTracker::Reset();

	{
		TestSmallArray<LifecycleTracker> src;
		src.emplace_back(11);
		src.emplace_back(22);
		REQUIRE(UsesLocalBuffer(src));

		TestSmallArray<LifecycleTracker> moved(std::move(src));

		REQUIRE(moved.size() == 2);
		CHECK(moved[0].value == 11);
		CHECK(moved[1].value == 22);
		CHECK(src.empty());
		CHECK(src.capacity() == 0);
	}

	CHECK(LifecycleTracker::corruptionCount == 0);
	CHECK(LifecycleTracker::liveCount == 0);
}

TEST_CASE("BSTSmallArray/MoveConstructPreservesValuesLargerThanAPointer", "[unit]")
{
	TestSmallArray<Vec3> src;
	src.push_back(Vec3{ 1, 2, 3 });
	REQUIRE(UsesLocalBuffer(src));

	TestSmallArray<Vec3> moved(std::move(src));

	REQUIRE(moved.size() == 1);
	CHECK(moved[0].x == 1);
	CHECK(moved[0].y == 2);
	CHECK(moved[0].z == 3);
}

TEST_CASE("BSTSmallArray/MoveConstructFromHeapTransfersBuffer", "[unit]")
{
	LifecycleTracker::Reset();

	{
		TestSmallArray<LifecycleTracker> src;
		for (int i = 0; i < 6; ++i) {
			src.emplace_back(i);
		}
		REQUIRE_FALSE(UsesLocalBuffer(src));
		const auto* originalData = src.data();

		TestSmallArray<LifecycleTracker> moved(std::move(src));

		CHECK(moved.data() == originalData);
		REQUIRE(moved.size() == 6);
		for (int i = 0; i < 6; ++i) {
			CHECK(moved[i].value == i);
		}
		CHECK(src.empty());
	}

	CHECK(LifecycleTracker::corruptionCount == 0);
	CHECK(LifecycleTracker::liveCount == 0);
}

TEST_CASE("BSTSmallArray/MoveAssignmentFromLocalPreservesValues", "[unit]")
{
	LifecycleTracker::Reset();

	{
		TestSmallArray<LifecycleTracker> src;
		src.emplace_back(11);
		src.emplace_back(22);
		src.emplace_back(33);
		REQUIRE(UsesLocalBuffer(src));

		TestSmallArray<LifecycleTracker> dst;
		dst.emplace_back(999);

		dst = std::move(src);

		REQUIRE(dst.size() == 3);
		CHECK(dst[0].value == 11);
		CHECK(dst[1].value == 22);
		CHECK(dst[2].value == 33);
		CHECK(src.empty());
	}

	CHECK(LifecycleTracker::corruptionCount == 0);
	CHECK(LifecycleTracker::liveCount == 0);
}

TEST_CASE("BSTSmallArray/MoveAssignmentFromHeapTransfersBuffer", "[unit]")
{
	TestSmallArray<int> src;
	for (int i = 1; i <= 6; ++i) {
		src.push_back(i);
	}
	REQUIRE_FALSE(UsesLocalBuffer(src));
	const auto* originalData = src.data();

	TestSmallArray<int> dst;
	dst.push_back(777);

	dst = std::move(src);

	CHECK(dst.data() == originalData);
	REQUIRE(dst.size() == 6);
	for (int i = 0; i < 6; ++i) {
		CHECK(dst[i] == i + 1);
	}
	CHECK(src.empty());
}

TEST_CASE("BSTSmallArray/ElementOperations", "[unit]")
{
	TestSmallArray<int> arr;
	for (const int v : { 1, 2, 3, 4 }) {
		arr.push_back(v);
	}
	REQUIRE(UsesLocalBuffer(arr));

	SECTION("erase shifts the tail left and preserves order")
	{
		const auto it = arr.erase(arr.cbegin() + 1);  // erase "2"
		REQUIRE(arr.size() == 3);
		CHECK(arr[0] == 1);
		CHECK(arr[1] == 3);
		CHECK(arr[2] == 4);
		CHECK(*it == 3);
	}

	SECTION("erasing the last element returns end()")
	{
		const auto it = arr.erase(arr.cend() - 1);
		CHECK(arr.size() == 3);
		CHECK(it == arr.end());
	}

	SECTION("insert in the middle shifts the tail and preserves order")
	{
		arr.insert(arr.cbegin() + 2, 99);
		const std::vector<int> expected{ 1, 2, 99, 3, 4 };
		CHECK(std::vector<int>(arr.begin(), arr.end()) == expected);
	}

	SECTION("push_front inserts before the current first element")
	{
		arr.push_front(0);
		const std::vector<int> expected{ 0, 1, 2, 3, 4 };
		CHECK(std::vector<int>(arr.begin(), arr.end()) == expected);
	}

	SECTION("pop_back removes the last element")
	{
		arr.pop_back();
		REQUIRE(arr.size() == 3);
		CHECK(arr[2] == 3);
	}

	SECTION("clear destroys every element but keeps the allocated capacity")
	{
		const auto capacityBeforeClear = arr.capacity();
		arr.clear();
		CHECK(arr.empty());
		CHECK(arr.capacity() == capacityBeforeClear);
	}
}

TEST_CASE("BSTSmallArray/HeapStaysHeapAfterShrinking", "[unit]")
{
	TestSmallArray<int> arr;
	for (int i = 1; i <= 6; ++i) {
		arr.push_back(i);
	}
	REQUIRE_FALSE(UsesLocalBuffer(arr));

	while (arr.size() > 1) {
		arr.pop_back();
	}
	CHECK(arr.size() == 1);
	CHECK_FALSE(UsesLocalBuffer(arr));
}

TEST_CASE("BSTSmallArray/ShrinkToFit", "[unit]")
{
	SECTION("heap-backed array shrinking back within the inline capacity returns to local storage")
	{
		LifecycleTracker::Reset();

		{
			TestSmallArray<LifecycleTracker> arr;
			for (int i = 0; i < 6; ++i) {
				arr.emplace_back(i);
			}
			REQUIRE_FALSE(UsesLocalBuffer(arr));

			arr.pop_back();
			arr.pop_back();
			arr.pop_back();
			arr.pop_back();
			REQUIRE(arr.size() == 2);
			REQUIRE_FALSE(UsesLocalBuffer(arr));  // popping alone never reclaims the buffer

			arr.shrink_to_fit();

			CHECK(arr.capacity() == 2);
			CHECK(UsesLocalBuffer(arr));
			REQUIRE(arr.size() == 2);
			CHECK(arr[0].value == 0);
			CHECK(arr[1].value == 1);
		}

		CHECK(LifecycleTracker::corruptionCount == 0);
		CHECK(LifecycleTracker::liveCount == 0);
	}

	SECTION("heap-backed array shrinking to a size still over the inline capacity stays on the heap")
	{
		TestSmallArray<int> arr;
		for (int i = 1; i <= 10; ++i) {
			arr.push_back(i);
		}
		REQUIRE_FALSE(UsesLocalBuffer(arr));

		while (arr.size() > 5) {
			arr.pop_back();
		}
		REQUIRE(arr.capacity() > 5);

		arr.shrink_to_fit();

		CHECK(arr.capacity() == 5);
		CHECK_FALSE(UsesLocalBuffer(arr));
		REQUIRE(arr.size() == 5);
		for (int i = 0; i < 5; ++i) {
			CHECK(arr[i] == i + 1);
		}
	}

	SECTION("local-backed array shrinking to a smaller local capacity preserves values")
	{
		// Regression: change_capacity() used to memcpy the inline buffer onto itself here -
		// allocate() returns that same fixed address for any capacity that still fits inline,
		// so a shrink that stays local never actually needs to move anything, but running
		// memcpy(x, x, n) to do that "nothing" is undefined behavior.
		LifecycleTracker::Reset();

		{
			TestSmallArray<LifecycleTracker> arr;
			arr.emplace_back(1);
			arr.emplace_back(2);
			arr.emplace_back(3);
			arr.emplace_back(4);
			REQUIRE(UsesLocalBuffer(arr));
			REQUIRE(arr.capacity() == 4);

			arr.pop_back();
			arr.pop_back();
			REQUIRE(arr.size() == 2);
			REQUIRE(arr.capacity() == 4);

			arr.shrink_to_fit();

			CHECK(arr.capacity() == 2);
			CHECK(UsesLocalBuffer(arr));
			REQUIRE(arr.size() == 2);
			CHECK(arr[0].value == 1);
			CHECK(arr[1].value == 2);
		}

		CHECK(LifecycleTracker::corruptionCount == 0);
		CHECK(LifecycleTracker::liveCount == 0);
	}

	SECTION("shrink_to_fit is a no-op when capacity already equals size")
	{
		TestSmallArray<int> arr;
		for (int i = 1; i <= 4; ++i) {
			arr.push_back(i);
		}
		REQUIRE(arr.size() == 4);
		REQUIRE(arr.capacity() == 4);

		const auto* originalData = arr.data();
		arr.shrink_to_fit();

		CHECK(arr.capacity() == 4);
		CHECK(arr.data() == originalData);
	}

	SECTION("shrink_to_fit on an empty array is a no-op")
	{
		TestSmallArray<int> arr;
		arr.shrink_to_fit();
		CHECK(arr.empty());
		CHECK(arr.capacity() == 0);
	}
}

TEST_CASE("BSTSmallArray/NoDoubleFreeOrCorruption", "[unit]")
{
	LifecycleTracker::Reset();

	SECTION("destroying a local-backed array destroys each value exactly once")
	{
		{
			TestSmallArray<LifecycleTracker> arr;
			arr.emplace_back(1);
			arr.emplace_back(2);
			REQUIRE(UsesLocalBuffer(arr));
		}
		CHECK(LifecycleTracker::corruptionCount == 0);
		CHECK(LifecycleTracker::liveCount == 0);
	}

	SECTION("destroying a heap-backed array destroys each value exactly once")
	{
		{
			TestSmallArray<LifecycleTracker> arr;
			for (int i = 0; i < 6; ++i) {
				arr.emplace_back(i);
			}
			REQUIRE_FALSE(UsesLocalBuffer(arr));
		}
		CHECK(LifecycleTracker::corruptionCount == 0);
		CHECK(LifecycleTracker::liveCount == 0);
	}

	SECTION("clear() followed by more insertions and destruction is consistent")
	{
		{
			TestSmallArray<LifecycleTracker> arr;
			arr.emplace_back(1);
			arr.emplace_back(2);
			arr.clear();
			arr.emplace_back(3);
		}
		CHECK(LifecycleTracker::corruptionCount == 0);
		CHECK(LifecycleTracker::liveCount == 0);
	}

	SECTION("copy construction and destruction of both copies is consistent")
	{
		{
			TestSmallArray<LifecycleTracker> src;
			src.emplace_back(1);
			src.emplace_back(2);
			TestSmallArray<LifecycleTracker> copy(src);
		}
		CHECK(LifecycleTracker::corruptionCount == 0);
		CHECK(LifecycleTracker::liveCount == 0);
	}

	SECTION("repeated move-assignment between local and heap-backed arrays is consistent")
	{
		{
			TestSmallArray<LifecycleTracker> a;
			a.emplace_back(1);
			a.emplace_back(2);

			TestSmallArray<LifecycleTracker> b;
			for (int i = 0; i < 6; ++i) {
				b.emplace_back(i + 10);
			}

			a = std::move(b);  // local <- heap
			REQUIRE(a.size() == 6);

			TestSmallArray<LifecycleTracker> c;
			c.emplace_back(100);
			c = std::move(a);  // heap <- heap (now moved-into a is heap-backed)
			REQUIRE(c.size() == 6);
		}
		CHECK(LifecycleTracker::corruptionCount == 0);
		CHECK(LifecycleTracker::liveCount == 0);
	}
}

TEST_CASE("BSTSmallArray/GrowthKeepsAllValuesCorrect", "[unit]")
{
	TestSmallArray<std::uintptr_t> arr;
	for (std::uintptr_t i = 0; i < 50; ++i) {
		arr.push_back(i);
	}

	REQUIRE(arr.size() == 50);
	std::uintptr_t expected = 0;
	for (const auto& value : arr) {
		CHECK(value == expected);
		++expected;
	}
	CHECK(expected == 50);
}

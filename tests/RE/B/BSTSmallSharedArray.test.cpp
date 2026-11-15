#include "catch2/catch_all.hpp"

#include "RE/B/BSTArray.h"

#include <vector>

namespace
{
	// Larger than a pointer on purpose - see BSTSmallSharedArray/MoveConstructorPreservesValuesLargerThanAPointer.
	struct Vec3
	{
		int x;
		int y;
		int z;
	};
	static_assert(sizeof(Vec3) > sizeof(void*));

	template <class T>
	[[nodiscard]] bool UsesLocalBuffer(const RE::BSTSmallSharedArray<T>& a_arr) noexcept
	{
		if (a_arr.empty()) {
			return true;
		}

		const auto arrBegin = reinterpret_cast<std::uintptr_t>(std::addressof(a_arr));
		const auto arrEnd = arrBegin + sizeof(a_arr);
		const auto dataAddr = reinterpret_cast<std::uintptr_t>(std::addressof(a_arr[0]));
		return dataAddr >= arrBegin && dataAddr < arrEnd;
	}
}

TEST_CASE("BSTSmallSharedArray/DefaultConstruction", "[unit]")
{
	RE::BSTSmallSharedArray<int> arr;
	CHECK(arr.empty());
	CHECK(arr.size() == 0);
	CHECK(arr.capacity() == 0);
	CHECK(arr.begin() == arr.end());
	CHECK(arr.begin() == nullptr);
}

TEST_CASE("BSTSmallSharedArray/LocalBufferSingleElement", "[unit]")
{
	RE::BSTSmallSharedArray<int> arr;

	SECTION("push_back onto an empty array stays local")
	{
		arr.push_back(42);
		CHECK(arr.size() == 1);
		CHECK(arr.capacity() == 1);
		CHECK(UsesLocalBuffer(arr));
		CHECK(arr[0] == 42);
		CHECK(arr.front() == 42);
		CHECK(arr.back() == 42);
	}

	SECTION("emplace_back forwards constructor arguments and returns a reference to the slot")
	{
		auto& ref = arr.emplace_back(7);
		CHECK(std::addressof(ref) == std::addressof(arr[0]));
		CHECK(arr[0] == 7);
		CHECK(UsesLocalBuffer(arr));
	}

	SECTION("push_front onto an empty array behaves like push_back")
	{
		arr.push_front(5);
		CHECK(arr.size() == 1);
		CHECK(arr[0] == 5);
		CHECK(UsesLocalBuffer(arr));
	}

	SECTION("initializer-list construction with one element stays local")
	{
		RE::BSTSmallSharedArray<int> single{ 9 };
		CHECK(single.size() == 1);
		CHECK(single.capacity() == 1);
		CHECK(single[0] == 9);
		CHECK(UsesLocalBuffer(single));
	}

	SECTION("initializer-list construction with zero elements stays empty")
	{
		RE::BSTSmallSharedArray<int> none(std::initializer_list<int>{});
		CHECK(none.empty());
		CHECK(none.capacity() == 0);
	}

	SECTION("iterating a single-element array visits exactly one value")
	{
		arr.push_back(3);
		const std::vector<int> seen(arr.begin(), arr.end());
		CHECK(seen == std::vector<int>{ 3 });
	}

	SECTION("erase on the only element empties the array")
	{
		arr.push_back(11);
		const auto it = arr.erase(arr.cbegin());
		CHECK(arr.empty());
		CHECK(arr.capacity() == 0);
		CHECK(it == arr.end());
	}

	SECTION("pop_back on the only element empties the array")
	{
		arr.push_back(11);
		arr.pop_back();
		CHECK(arr.empty());
		CHECK(arr.size() == 0);
		CHECK(arr.capacity() == 0);
	}

	SECTION("clear on a single-element array empties it")
	{
		arr.push_back(1);
		arr.clear();
		CHECK(arr.empty());
		CHECK(arr.capacity() == 0);
	}
}

TEST_CASE("BSTSmallSharedArray/CopySemanticsLocalOnly", "[unit]")
{
	SECTION("copying an empty array")
	{
		RE::BSTSmallSharedArray<int> src;
		RE::BSTSmallSharedArray<int> copy(src);
		CHECK(copy.empty());
		CHECK(copy.capacity() == 0);
	}

	SECTION("copying a single-element array is independent of the source")
	{
		RE::BSTSmallSharedArray<int> src;
		src.push_back(100);

		RE::BSTSmallSharedArray<int> copy(src);
		REQUIRE(copy.size() == 1);
		CHECK(copy[0] == 100);
		CHECK(UsesLocalBuffer(copy));

		copy[0] = 200;
		CHECK(src[0] == 100);
	}

	SECTION("copy assignment replaces existing contents")
	{
		RE::BSTSmallSharedArray<int> src;
		src.push_back(5);

		RE::BSTSmallSharedArray<int> dst;
		dst.push_back(999);
		dst = src;

		REQUIRE(dst.size() == 1);
		CHECK(dst[0] == 5);
		CHECK(UsesLocalBuffer(dst));
	}

	SECTION("self copy-assignment is a no-op")
	{
		RE::BSTSmallSharedArray<int> arr;
		arr.push_back(1);

		// Routed through a pointer so this doesn't read as a literal `arr = arr;`, which
		// clang flags with -Wself-assign-overloaded under this project's /WX.
		auto* self = &arr;
		arr = *self;

		REQUIRE(arr.size() == 1);
		CHECK(arr[0] == 1);
	}
}

TEST_CASE("BSTSmallSharedArray/MoveSemanticsLocalOnly", "[unit]")
{
	SECTION("move-constructing from an empty array")
	{
		RE::BSTSmallSharedArray<int> src;
		RE::BSTSmallSharedArray<int> moved(std::move(src));
		CHECK(moved.empty());
		CHECK(src.empty());
	}

	SECTION("move-constructing from a single-element array preserves the value, for a pointer-sized T")
	{
		RE::BSTSmallSharedArray<int> src;
		src.push_back(55);

		RE::BSTSmallSharedArray<int> moved(std::move(src));
		REQUIRE(moved.size() == 1);
		CHECK(moved[0] == 55);
		CHECK(src.empty());
	}

	SECTION("move assignment from a single-element array preserves the value")
	{
		RE::BSTSmallSharedArray<int> src;
		src.push_back(21);

		RE::BSTSmallSharedArray<int> dst;
		dst = std::move(src);

		REQUIRE(dst.size() == 1);
		CHECK(dst[0] == 21);
		CHECK(src.empty());
	}
}

TEST_CASE("BSTSmallSharedArray/MoveConstructorPreservesValuesLargerThanAPointer", "[unit]")
{
	// Vec3 is bigger than a pointer: a single-element move that only copies pointer-sized
	// bytes out of the local value would leave `z` wrong.
	RE::BSTSmallSharedArray<Vec3> src;
	src.push_back(Vec3{ 1, 2, 3 });
	REQUIRE(src.size() == 1);
	REQUIRE(UsesLocalBuffer(src));

	RE::BSTSmallSharedArray<Vec3> moved(std::move(src));

	REQUIRE(moved.size() == 1);
	CHECK(moved[0].x == 1);
	CHECK(moved[0].y == 2);
	CHECK(moved[0].z == 3);
}

TEST_CASE("BSTSmallSharedArray/HeapTransition", "[unit]")
{
	SECTION("a second element transitions from local to heap")
	{
		RE::BSTSmallSharedArray<int> arr;
		arr.push_back(1);
		REQUIRE(UsesLocalBuffer(arr));

		arr.push_back(2);
		CHECK(arr.size() == 2);
		CHECK(arr.capacity() >= 2);
		CHECK_FALSE(UsesLocalBuffer(arr));
		CHECK(arr[0] == 1);
		CHECK(arr[1] == 2);
	}

	SECTION("popping back down to one element transitions from heap to local")
	{
		RE::BSTSmallSharedArray<int> arr;
		arr.push_back(1);
		arr.push_back(2);
		REQUIRE_FALSE(UsesLocalBuffer(arr));

		arr.pop_back();
		CHECK(arr.size() == 1);
		CHECK(arr.capacity() == 1);
		CHECK(UsesLocalBuffer(arr));
		CHECK(arr[0] == 1);
	}

	SECTION("erasing down to one element also transitions back to local")
	{
		RE::BSTSmallSharedArray<int> arr;
		arr.push_back(10);
		arr.push_back(20);
		arr.push_back(30);
		REQUIRE(arr.size() == 3);

		// erase() swaps the erased slot with the last element: index 0 is overwritten with
		// the old last value (30), then that now-duplicated last slot is popped.
		arr.erase(arr.cbegin());
		REQUIRE(arr.size() == 2);
		CHECK(arr[0] == 30);
		CHECK(arr[1] == 20);

		arr.erase(arr.cbegin());
		REQUIRE(arr.size() == 1);
		CHECK(UsesLocalBuffer(arr));
		CHECK(arr[0] == 20);
	}

	SECTION("erase swaps the erased slot with the last element instead of preserving order")
	{
		// erase() intentionally diverges from BSTArray::erase(): it swaps the erased slot
		// with the last element and pops, which is O(1) instead of O(n) but does not
		// preserve the relative order of what remains.
		RE::BSTSmallSharedArray<int> arr;
		for (const int v : { 1, 2, 3, 4, 5 }) {
			arr.push_back(v);
		}

		const auto it = arr.erase(arr.cbegin() + 1);  // erase "2"; "5" (the old last) replaces it
		REQUIRE(arr.size() == 4);
		CHECK(arr[0] == 1);
		CHECK(arr[1] == 5);
		CHECK(arr[2] == 3);
		CHECK(arr[3] == 4);
		CHECK(it == arr.begin() + 1);
	}

	SECTION("erasing the last element returns end()")
	{
		RE::BSTSmallSharedArray<int> arr;
		for (const int v : { 1, 2, 3 }) {
			arr.push_back(v);
		}

		const auto it = arr.erase(arr.cbegin() + 2);
		CHECK(arr.size() == 2);
		CHECK(it == arr.end());
	}

	SECTION("insert in the middle shifts the tail and preserves order")
	{
		RE::BSTSmallSharedArray<int> arr;
		for (const int v : { 1, 2, 4, 5 }) {
			arr.push_back(v);
		}

		arr.insert(arr.cbegin() + 2, 3);
		const std::vector<int> expected{ 1, 2, 3, 4, 5 };
		CHECK(std::vector<int>(arr.begin(), arr.end()) == expected);
	}

	SECTION("push_front inserts before the current first element")
	{
		RE::BSTSmallSharedArray<int> arr;
		arr.push_back(2);
		arr.push_back(3);
		arr.push_front(1);

		const std::vector<int> expected{ 1, 2, 3 };
		CHECK(std::vector<int>(arr.begin(), arr.end()) == expected);
	}

	SECTION("clear on a heap-backed array releases the buffer")
	{
		RE::BSTSmallSharedArray<int> arr;
		arr.push_back(1);
		arr.push_back(2);
		arr.push_back(3);
		REQUIRE_FALSE(UsesLocalBuffer(arr));

		arr.clear();
		CHECK(arr.empty());
		CHECK(arr.capacity() == 0);
	}

	SECTION("copying a heap-backed array is a deep, independent copy")
	{
		RE::BSTSmallSharedArray<int> src;
		src.push_back(1);
		src.push_back(2);

		RE::BSTSmallSharedArray<int> copy(src);
		REQUIRE(copy.size() == 2);
		CHECK(copy[0] == 1);
		CHECK(copy[1] == 2);

		copy[0] = 999;
		CHECK(src[0] == 1);
	}

	SECTION("move-constructing a heap-backed array transfers the buffer without reallocating")
	{
		RE::BSTSmallSharedArray<int> src;
		src.push_back(1);
		src.push_back(2);
		const auto* originalData = src.data();

		RE::BSTSmallSharedArray<int> moved(std::move(src));
		CHECK(moved.data() == originalData);
		CHECK(moved.size() == 2);
		CHECK(moved[0] == 1);
		CHECK(moved[1] == 2);
		CHECK(src.empty());
	}

	SECTION("move assignment of a heap-backed array transfers the buffer without reallocating")
	{
		RE::BSTSmallSharedArray<int> src;
		src.push_back(1);
		src.push_back(2);
		const auto* originalData = src.data();

		RE::BSTSmallSharedArray<int> dst;
		dst.push_back(777);
		dst = std::move(src);

		CHECK(dst.data() == originalData);
		CHECK(dst.size() == 2);
		CHECK(dst[0] == 1);
		CHECK(dst[1] == 2);
		CHECK(src.empty());
	}

	SECTION("growing past several elements keeps all values correct")
	{
		RE::BSTSmallSharedArray<std::uintptr_t> arr;
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
}

#include "catch2/catch_all.hpp"

#include "RE/B/BSTArray.h"
#include "RE/S/ScrapHeap.h"

#include <vector>

namespace
{
	class TestScrapHeap : public RE::ScrapHeap
	{};

	template <class T>
	[[nodiscard]] RE::BSScrapArray<T> MakeScrapArray(RE::ScrapHeap& a_heap)
	{
		RE::BSScrapArray<T> arr;
		arr.SetAllocator(std::addressof(a_heap));
		return arr;
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
}

TEST_CASE("BSScrapArray/DefaultConstruction", "[unit]")
{
	RE::BSScrapArray<int> arr;
	CHECK(arr.empty());
	CHECK(arr.size() == 0);
	CHECK(arr.capacity() == 0);
	CHECK(arr.begin() == arr.end());
	CHECK(arr.begin() == nullptr);
	CHECK(arr.GetAllocator() == nullptr);
}

TEST_CASE("BSScrapArray/AllocatorAccessors", "[unit]")
{
	TestScrapHeap heap;

	RE::BSScrapArray<int> arr;
	CHECK(arr.GetAllocator() == nullptr);

	arr.SetAllocator(&heap);
	CHECK(arr.GetAllocator() == &heap);
}

TEST_CASE("BSScrapArray/GrowthAndElementAccess", "[unit]")
{
	TestScrapHeap heap;
	auto          arr = MakeScrapArray<int>(heap);

	for (int i = 1; i <= 10; ++i) {
		arr.push_back(i);
	}

	REQUIRE(arr.size() == 10);
	for (int i = 0; i < 10; ++i) {
		CHECK(arr[i] == i + 1);
	}
	CHECK(arr.capacity() >= arr.size());
	// growth reallocates the backing buffer but must never touch the ScrapHeap identity
	CHECK(arr.GetAllocator() == &heap);
}

TEST_CASE("BSScrapArray/ElementOperations", "[unit]")
{
	TestScrapHeap heap;
	auto          arr = MakeScrapArray<int>(heap);
	for (const int v : { 1, 2, 3, 4 }) {
		arr.push_back(v);
	}

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

	SECTION("clear destroys every element but keeps the allocated capacity and ScrapHeap identity")
	{
		const auto capacityBeforeClear = arr.capacity();
		arr.clear();
		CHECK(arr.empty());
		CHECK(arr.capacity() == capacityBeforeClear);
		CHECK(arr.GetAllocator() == &heap);
	}
}

TEST_CASE("BSScrapArray/MoveConstruction", "[unit]")
{
	SECTION("moving an empty array leaves both empty")
	{
		TestScrapHeap heap;
		auto          src = MakeScrapArray<int>(heap);

		RE::BSScrapArray<int> moved(std::move(src));

		CHECK(moved.empty());
		CHECK(moved.GetAllocator() == &heap);
		CHECK(src.empty());
		CHECK(src.GetAllocator() == nullptr);
	}

	SECTION("moving a populated array transfers values, the buffer, and the ScrapHeap identity")
	{
		TestScrapHeap heap;
		auto          src = MakeScrapArray<int>(heap);
		for (int i = 1; i <= 6; ++i) {
			src.push_back(i);
		}
		const auto* originalData = src.data();

		RE::BSScrapArray<int> moved(std::move(src));

		CHECK(moved.data() == originalData);
		CHECK(moved.GetAllocator() == &heap);
		REQUIRE(moved.size() == 6);
		for (int i = 0; i < 6; ++i) {
			CHECK(moved[i] == i + 1);
		}

		CHECK(src.empty());
		CHECK(src.capacity() == 0);
		CHECK(src.GetAllocator() == nullptr);
	}
}

TEST_CASE("BSScrapArray/MoveAssignment", "[unit]")
{
	SECTION("replaces existing contents and transfers the ScrapHeap identity, not the destination's own")
	{
		LifecycleTracker::Reset();

		{
			TestScrapHeap srcHeap;
			TestScrapHeap dstHeap;

			auto src = MakeScrapArray<LifecycleTracker>(srcHeap);
			src.emplace_back(11);
			src.emplace_back(22);
			src.emplace_back(33);

			auto dst = MakeScrapArray<LifecycleTracker>(dstHeap);
			dst.emplace_back(999);

			dst = std::move(src);

			REQUIRE(dst.size() == 3);
			CHECK(dst[0].value == 11);
			CHECK(dst[1].value == 22);
			CHECK(dst[2].value == 33);
			CHECK(dst.GetAllocator() == &srcHeap);

			CHECK(src.empty());
			CHECK(src.GetAllocator() == nullptr);
		}

		CHECK(LifecycleTracker::corruptionCount == 0);
		CHECK(LifecycleTracker::liveCount == 0);
	}

	SECTION("moving from an empty, never-allocated array clears the destination's identity too")
	{
		TestScrapHeap dstHeap;

		// Deliberately not using MakeScrapArray(), which always calls SetAllocator(): this needs
		// a source whose _allocator is genuinely still null, to confirm the move unconditionally
		// overwrites the destination's _allocator rather than skipping a "null" source.
		RE::BSScrapArray<int> src;
		REQUIRE(src.GetAllocator() == nullptr);

		auto dst = MakeScrapArray<int>(dstHeap);
		dst.push_back(1);

		dst = std::move(src);

		CHECK(dst.empty());
		CHECK(dst.GetAllocator() == nullptr);
	}

	SECTION("self move-assignment is a no-op")
	{
		TestScrapHeap heap;
		auto          arr = MakeScrapArray<int>(heap);
		arr.push_back(1);
		arr.push_back(2);

		// Routed through a pointer so this doesn't read as a literal `arr = arr;`, which clang
		// flags with -Wself-assign-overloaded under this project's /WX.
		auto* self = &arr;
		arr = std::move(*self);

		REQUIRE(arr.size() == 2);
		CHECK(arr[0] == 1);
		CHECK(arr[1] == 2);
		CHECK(arr.GetAllocator() == &heap);
	}
}

TEST_CASE("BSScrapArray/CopyAssignment", "[unit]")
{
	SECTION("deep-copies values independently of the source")
	{
		TestScrapHeap heap;
		auto          src = MakeScrapArray<int>(heap);
		src.push_back(5);

		auto dst = MakeScrapArray<int>(heap);
		dst.push_back(1);
		dst.push_back(2);
		dst.push_back(3);

		dst = src;

		REQUIRE(dst.size() == 1);
		CHECK(dst[0] == 5);

		dst[0] = -1;
		CHECK(src[0] == 5);
	}

	SECTION("destination keeps its own ScrapHeap identity rather than the source's")
	{
		// Unlike move-assignment, BSScrapArrayAllocator's copy assignment never touches
		// _allocator - only the move path is the subject of this fix.
		TestScrapHeap srcHeap;
		TestScrapHeap dstHeap;

		auto src = MakeScrapArray<int>(srcHeap);
		src.push_back(1);

		auto dst = MakeScrapArray<int>(dstHeap);
		dst = src;

		CHECK(dst.GetAllocator() == &dstHeap);
	}

	SECTION("self copy-assignment is a no-op")
	{
		TestScrapHeap heap;
		auto          arr = MakeScrapArray<int>(heap);
		arr.push_back(1);
		arr.push_back(2);

		auto* self = &arr;
		arr = *self;

		REQUIRE(arr.size() == 2);
		CHECK(arr[0] == 1);
		CHECK(arr[1] == 2);
	}
}

TEST_CASE("BSScrapArray/NoDoubleFreeOrCorruption", "[unit]")
{
	LifecycleTracker::Reset();

	SECTION("destroying a populated array destroys each value exactly once")
	{
		{
			TestScrapHeap heap;
			auto          arr = MakeScrapArray<LifecycleTracker>(heap);
			for (int i = 0; i < 6; ++i) {
				arr.emplace_back(i);
			}
		}
		CHECK(LifecycleTracker::corruptionCount == 0);
		CHECK(LifecycleTracker::liveCount == 0);
	}

	SECTION("clear() followed by more insertions and destruction is consistent")
	{
		{
			TestScrapHeap heap;
			auto          arr = MakeScrapArray<LifecycleTracker>(heap);
			arr.emplace_back(1);
			arr.emplace_back(2);
			arr.clear();
			arr.emplace_back(3);
		}
		CHECK(LifecycleTracker::corruptionCount == 0);
		CHECK(LifecycleTracker::liveCount == 0);
	}

	SECTION("a chain of move-assignments is consistent")
	{
		{
			TestScrapHeap heapA;
			TestScrapHeap heapB;
			TestScrapHeap heapC;

			auto a = MakeScrapArray<LifecycleTracker>(heapA);
			a.emplace_back(1);
			a.emplace_back(2);

			auto b = MakeScrapArray<LifecycleTracker>(heapB);
			for (int i = 0; i < 6; ++i) {
				b.emplace_back(i + 10);
			}

			a = std::move(b);
			REQUIRE(a.size() == 6);
			CHECK(a.GetAllocator() == &heapB);

			auto c = MakeScrapArray<LifecycleTracker>(heapC);
			c.emplace_back(100);
			c = std::move(a);
			REQUIRE(c.size() == 6);
			CHECK(c.GetAllocator() == &heapB);
		}
		CHECK(LifecycleTracker::corruptionCount == 0);
		CHECK(LifecycleTracker::liveCount == 0);
	}
}

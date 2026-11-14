#include "catch2/catch_all.hpp"

#include "RE/B/BSTHashMap.h"

namespace
{
	// Movable-only value whose destructor records whether it ever ran twice on the same
	// object (the symptom of value_union's old unconditional ctor/dtor double-destructing
	// an already-released entry).
	struct DoubleFreeTracker
	{
		static inline int destroyCount = 0;
		static inline int doubleFreeCount = 0;

		static void Reset()
		{
			destroyCount = 0;
			doubleFreeCount = 0;
		}

		DoubleFreeTracker() = default;
		DoubleFreeTracker(const DoubleFreeTracker&) = delete;
		DoubleFreeTracker& operator=(const DoubleFreeTracker&) = delete;

		DoubleFreeTracker(DoubleFreeTracker&& a_rhs) noexcept :
			_destroyed(a_rhs._destroyed)
		{}

		DoubleFreeTracker& operator=(DoubleFreeTracker&& a_rhs) noexcept
		{
			if (this != std::addressof(a_rhs)) {
				_destroyed = a_rhs._destroyed;
			}
			return *this;
		}

		~DoubleFreeTracker()
		{
			++destroyCount;
			if (_destroyed) {
				++doubleFreeCount;
			}
			_destroyed = true;
		}

	private:
		bool _destroyed{ false };
	};

	// Hashes a key to itself so slot placement is deterministic and a collision can be
	// engineered exactly, instead of relying on BSCRC32's distribution.
	struct IdentityHash
	{
		[[nodiscard]] std::uint32_t operator()(int a_key) const noexcept
		{
			return static_cast<std::uint32_t>(a_key);
		}
	};

	// `_capacity`/`_free`/`_good` are protected on BSTScatterTableStandardParent, so a
	// subclass can reach them the same way BSTScatterTable's own member functions do.
	struct SkyrimClearedHashMap : RE::BSTStaticHashMap<int, int, 2048, IdentityHash>
	{
		// Decompiled from the running game: Skyrim's own Clear() releases every occupied
		// slot (which clear() already does correctly) and then resets `_free` AND `_good`
		// to `_capacity` - never to 0. That value is pinned here by hand, independently of
		// whatever this library's own clear() currently does to `_good`, so this test still
		// catches it if clear() and get_free_entry()'s scan direction are ever both reverted
		// back to the old (good=0, scan-upward) pair: that combination is internally
		// consistent and would otherwise still pass a test that only trusted clear() to set
		// `_good` up correctly, even though it diverges from what Skyrim itself leaves behind.
		void ForceSkyrimClear()
		{
			clear();
			_free = _capacity;
			_good = _capacity;
		}

		// Exposes the internal cursor directly so the test can pin the exact slot the
		// fix's downward scan lands on, rather than only observing it indirectly through
		// find()/iteration - see the comment at the call site for why that matters.
		[[nodiscard]] std::uint32_t DebugGood() const noexcept { return _good; }
	};
}

TEST_CASE("BSTHashMap/NoDoubleFree", "[unit]")
{
	DoubleFreeTracker::Reset();

	SECTION("destroying a populated map destroys each value exactly once")
	{
		{
			RE::BSTStaticHashMap<int, DoubleFreeTracker, 8> map;
			REQUIRE(map.emplace(1, DoubleFreeTracker{}).second);
			REQUIRE(map.emplace(2, DoubleFreeTracker{}).second);
			REQUIRE(map.emplace(3, DoubleFreeTracker{}).second);
		}  // map destructs here, destroying every occupied entry_type in its fixed buffer

		// Not asserting an exact destroyCount here: emplace()'s forwarding chain
		// constructs and destroys its own temporaries along the way (the argument passed
		// in, the intermediate value_type built inside emplace()), each legitimately
		// destroyed once on top of the 3 values actually stored in the map. That total is
		// an implementation detail of the forwarding path, not something this test should
		// pin to - doubleFreeCount==0 is the real invariant.
		CHECK(DoubleFreeTracker::doubleFreeCount == 0);
	}

	SECTION("clear() followed by destruction still destroys each value exactly once")
	{
		{
			RE::BSTStaticHashMap<int, DoubleFreeTracker, 8> map;
			REQUIRE(map.emplace(1, DoubleFreeTracker{}).second);
			REQUIRE(map.emplace(2, DoubleFreeTracker{}).second);
			map.clear();
			REQUIRE(map.emplace(3, DoubleFreeTracker{}).second);
		}

		CHECK(DoubleFreeTracker::doubleFreeCount == 0);
	}
}

TEST_CASE("BSTHashMap/FreeEntryBoundary", "[unit]")
{
	SkyrimClearedHashMap map;

	// Fill most (but not all) of the table; with the identity hash every key here lands in
	// its own slot, so none of this collides.
	for (int i = 0; i < 2000; ++i) {
		REQUIRE(map.emplace(i, i).second);
	}
	REQUIRE(map.size() == 2000);

	// Forces the table into exactly the state Skyrim's own Clear() leaves it in - every
	// slot freed, `_good` pinned to `_capacity` rather than trusted to this library's own
	// clear() - so the next free-entry scan must start from that out-of-bounds sentinel
	// and move into range before reading anything.
	map.ForceSkyrimClear();
	REQUIRE(map.size() == 0);

	// Key 0 takes slot 0 directly (free real estate) - `_good` is untouched by this insert.
	REQUIRE(map.emplace(0, 0).second);

	// Key 2048 hashes to the same slot as key 0 (2048 & 2047 == 0), forcing the very first
	// get_free_entry() call since clear() while `_good` still equals capacity.
	REQUIRE(map.emplace(2048, 2048).second);

	// Pin the exact slot the fix's downward scan must land on: from `_good == 2048`
	// (capacity), the first (and only) decrement lands on slot 2047, which is free.
	// An upward, check-first scan landing on some other free slot by luck (its first
	// read is undefined - entries[capacity] is one past this fixed buffer's end) would
	// not be caught by this if it only checked reachability below, since a value placed
	// correctly anywhere still finds its way into the chain. Note this assertion (and the
	// insert above) is only well-defined to run against the fixed scan: forcing `_good`
	// to this exact out-of-bounds sentinel and reverting the scan to upward would read
	// past the end of this map's buffer, which is undefined behavior, not a guaranteed
	// clean test failure.
	CHECK(map.DebugGood() == 2047);

	CHECK(map.size() == 2);

	// The regression this guards against: the second insert used to land in a slot the
	// chain never linked to, so it was physically written but unreachable - exactly the
	// in-game symptom, where contains() on the new key comes back false permanently.
	CHECK(map.contains(2048));

	const auto it = map.find(2048);
	REQUIRE(it != map.end());
	CHECK(it->second == 2048);

	std::size_t seen = 0;
	for ([[maybe_unused]] const auto& entry : map) {
		++seen;
	}
	CHECK(seen == map.size());
}

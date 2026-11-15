#include "catch2/catch_all.hpp"

#include "RE/B/BSTPointerAndFlags.h"
#include "RE/B/BSTSmartPointer.h"

namespace
{
	struct RefCountedTracker
	{
		static inline int destroyCount = 0;

		static void Reset() { destroyCount = 0; }

		void IncRef() noexcept { ++refCount; }

		std::uint32_t DecRef() noexcept { return --refCount; }

		~RefCountedTracker() { ++destroyCount; }

		std::uint32_t refCount{ 0 };
	};

	struct TestPointerAndFlags : RE::BSTPointerAndFlags<RE::BSTSmartPointer<RefCountedTracker>, 1>
	{
		TestPointerAndFlags() = default;

		TestPointerAndFlags(RE::BSTSmartPointer<RefCountedTracker> a_ptr, bool a_flag)
		{
			_storage.ptr = a_ptr;
			_storage.address |= static_cast<std::uintptr_t>(a_flag);
		}

		[[nodiscard]] bool GetFlag() const noexcept { return _storage.address & FLAG_MASK; }
	};
}

TEST_CASE("BSTPointerAndFlags/DefaultConstruction", "[unit]")
{
	TestPointerAndFlags obj;
	CHECK(obj.get() == nullptr);
	CHECK_FALSE(static_cast<bool>(obj));
	CHECK_FALSE(obj.GetFlag());
}

TEST_CASE("BSTPointerAndFlags/ConstructionAcquiresAReference", "[unit]")
{
	RefCountedTracker::Reset();

	auto ptr = RE::make_smart<RefCountedTracker>();
	REQUIRE(ptr->refCount == 1);

	TestPointerAndFlags obj(ptr, true);
	CHECK(ptr->refCount == 2);
	CHECK(obj.get() == ptr.get());
	CHECK(obj.GetFlag());
}

TEST_CASE("BSTPointerAndFlags/CopySemantics", "[unit]")
{
	RefCountedTracker::Reset();

	SECTION("copy constructor shares ownership")
	{
		auto                ptr = RE::make_smart<RefCountedTracker>();
		TestPointerAndFlags obj1(ptr, false);
		REQUIRE(ptr->refCount == 2);

		TestPointerAndFlags obj2(obj1);
		CHECK(ptr->refCount == 3);
		CHECK(obj2.get() == obj1.get());
	}

	SECTION("copy constructor preserves the flag")
	{
		auto                ptr = RE::make_smart<RefCountedTracker>();
		TestPointerAndFlags obj1(ptr, true);

		TestPointerAndFlags obj2(obj1);
		CHECK(obj2.GetFlag());
	}

	SECTION("copy assignment releases the old reference and acquires the new one")
	{
		auto                ptrA = RE::make_smart<RefCountedTracker>();
		auto                ptrB = RE::make_smart<RefCountedTracker>();
		TestPointerAndFlags obj(ptrA, false);
		TestPointerAndFlags objB(ptrB, true);
		REQUIRE(ptrA->refCount == 2);
		REQUIRE(ptrB->refCount == 2);

		obj = objB;
		CHECK(ptrA->refCount == 1);
		CHECK(ptrB->refCount == 3);
		CHECK(obj.get() == ptrB.get());
		CHECK(obj.GetFlag());
	}

	SECTION("self copy-assignment is a no-op")
	{
		auto                ptr = RE::make_smart<RefCountedTracker>();
		TestPointerAndFlags obj(ptr, false);

		// Routed through a pointer so this doesn't read as a literal `obj = obj;`, which
		// clang flags with -Wself-assign-overloaded under this project's /WX.
		auto* self = &obj;
		obj = *self;

		CHECK(ptr->refCount == 2);
		CHECK(obj.get() == ptr.get());
	}
}

TEST_CASE("BSTPointerAndFlags/MoveSemantics", "[unit]")
{
	RefCountedTracker::Reset();

	SECTION("move constructor transfers ownership without changing the refcount")
	{
		auto                ptr = RE::make_smart<RefCountedTracker>();
		TestPointerAndFlags obj1(ptr, false);
		REQUIRE(ptr->refCount == 2);

		TestPointerAndFlags obj2(std::move(obj1));
		CHECK(ptr->refCount == 2);
		CHECK(obj2.get() == ptr.get());
		CHECK(obj1.get() == nullptr);
		CHECK_FALSE(static_cast<bool>(obj1));
	}

	SECTION("move constructor preserves the flag")
	{
		auto                ptr = RE::make_smart<RefCountedTracker>();
		TestPointerAndFlags obj1(ptr, true);

		TestPointerAndFlags obj2(std::move(obj1));
		CHECK(obj2.GetFlag());
	}

	SECTION("move assignment releases the previously held reference")
	{
		auto                ptrA = RE::make_smart<RefCountedTracker>();
		auto                ptrB = RE::make_smart<RefCountedTracker>();
		TestPointerAndFlags obj(ptrA, false);
		TestPointerAndFlags objB(ptrB, true);
		REQUIRE(ptrA->refCount == 2);
		REQUIRE(ptrB->refCount == 2);

		obj = std::move(objB);
		CHECK(ptrA->refCount == 1);
		CHECK(ptrB->refCount == 2);
		CHECK(obj.get() == ptrB.get());
		CHECK(obj.GetFlag());
		CHECK(objB.get() == nullptr);
	}

	SECTION("self move-assignment is a no-op")
	{
		auto                ptr = RE::make_smart<RefCountedTracker>();
		TestPointerAndFlags obj(ptr, false);

		auto* self = &obj;
		obj = std::move(*self);

		CHECK(ptr->refCount == 2);
		CHECK(obj.get() == ptr.get());
	}
}

TEST_CASE("BSTPointerAndFlags/DestructorAndReset", "[unit]")
{
	RefCountedTracker::Reset();

	SECTION("destructor releases exactly one reference")
	{
		auto ptr = RE::make_smart<RefCountedTracker>();
		{
			TestPointerAndFlags obj(ptr, false);
			REQUIRE(ptr->refCount == 2);
		}
		CHECK(ptr->refCount == 1);
	}

	SECTION("the underlying object is destroyed only once every reference is gone")
	{
		{
			auto ptr = RE::make_smart<RefCountedTracker>();
			{
				TestPointerAndFlags obj(ptr, false);
			}
			CHECK(RefCountedTracker::destroyCount == 0);
		}
		CHECK(RefCountedTracker::destroyCount == 1);
	}

	SECTION("reset releases the reference and clears the flag")
	{
		auto                ptr = RE::make_smart<RefCountedTracker>();
		TestPointerAndFlags obj(ptr, true);
		REQUIRE(ptr->refCount == 2);

		obj.reset();
		CHECK(ptr->refCount == 1);
		CHECK(obj.get() == nullptr);
		CHECK_FALSE(obj.GetFlag());
	}
}

TEST_CASE("BSTPointerAndFlags/Access", "[unit]")
{
	RefCountedTracker::Reset();

	auto                ptr = RE::make_smart<RefCountedTracker>();
	TestPointerAndFlags obj(ptr, false);

	CHECK(&*obj == ptr.get());
	CHECK(obj->refCount == ptr->refCount);
	CHECK(static_cast<bool>(obj));
}

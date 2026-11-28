#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"

namespace RE
{
	class BSPathingDoor;

	// Refcounted door-passage policy used by path searches.
	class BSPathingLockData : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathingLockData;

		virtual ~BSPathingLockData();                                                          // 00
		virtual std::uint32_t      GetType() const = 0;                                        // 01 - CRC32 of the class name
		virtual bool               TryPassDoor(BSPathingDoor** a_door, float* a_costOut) = 0;  // 02
		virtual bool               CanPassDoor(BSPathingDoor** a_door);                        // 03 - TryPassDoor with a zero cost
		virtual void               Write(void* a_stream) const = 0;                            // 04
		virtual void               Read(void* a_stream) = 0;                                   // 05
		virtual BSPathingLockData* Clone() const = 0;                                          // 06

		// members
		std::uint32_t pad0C;  // 0C
	};
	static_assert(sizeof(BSPathingLockData) == 0x10);
}

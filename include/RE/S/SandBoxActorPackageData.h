#pragma once

#include "RE/A/ActorPackageData.h"
#include "RE/B/BSPointerHandle.h"

namespace RE
{
	class SandBoxActorPackageData : public ActorPackageData
	{
	public:
		inline static constexpr auto RTTI = RTTI_SandBoxActorPackageData;
		inline static constexpr auto VTABLE = VTABLE_SandBoxActorPackageData;

		~SandBoxActorPackageData() override;  // 00

		// members
		std::uint32_t   unk08;     // 08
		std::uint32_t   unk0C;     // 0C - default 0xFFFFFFFF (index/id sentinel)
		std::uint32_t   unk10;     // 10
		ObjectRefHandle target14;  // 14
		std::uint64_t   unk18;     // 18
		std::uint32_t   unk20;     // 20 - default 0xFFFFFFFF (index/id sentinel)
		std::uint32_t   pad24;     // 24
		// 28: matches this repo's BSTArray<T> layout exactly (data/capacity/allocator-pad/size/struct-pad) --
		// Func7_140714630 indexes data+i*0x10, so T is a 0x10-byte element of unconfirmed type.
		void*           arrayData;      // 28 - BSTArrayHeapAllocator::_data
		std::uint32_t   arrayCapacity;  // 30 - BSTArrayHeapAllocator::_capacity
		std::uint32_t   allocatorPad;   // 34 - BSTArrayHeapAllocator's trailing pad
		std::uint32_t   arrayCount;     // 38 - BSTArrayBase::_size; Func7_140714630's iteration count
		std::uint32_t   structPad;      // 3C - BSTArray<T>'s trailing pad
		std::uint32_t   unk40;          // 40
		std::uint32_t   unk44;          // 44 - default 1
		std::uint32_t   pad48;          // 48
		ObjectRefHandle target4C;       // 4C
		std::uint8_t    unk50;          // 50 - default 0x7F
		std::uint8_t    pad51[3];       // 51
		ObjectRefHandle target54;       // 54
		std::uint32_t   pad58;          // 58
		std::uint32_t   unk5C[2];       // 5C - misaligned uint64 write in the binary; split to avoid compiler padding
		std::uint32_t   unk64;          // 64
		std::uint32_t   unk68;          // 68 - default 0xFFFFFFFF (index/id sentinel)
		std::uint8_t    unk6C[7];       // 6C - default all 0x80 (sentinel array)
		std::uint8_t    pad73[5];       // 73
	};
	static_assert(sizeof(SandBoxActorPackageData) == 0x78);
}

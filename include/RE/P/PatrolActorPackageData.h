#pragma once

#include "RE/A/ActorPackageData.h"
#include "RE/B/BSPointerHandle.h"

namespace RE
{
	class PatrolActorPackageData : public ActorPackageData
	{
	public:
		inline static constexpr auto RTTI = RTTI_PatrolActorPackageData;
		inline static constexpr auto VTABLE = VTABLE_PatrolActorPackageData;

		~PatrolActorPackageData() override;  // 00

		// members
		std::uint32_t   unk08;        // 08
		std::uint32_t   pad0C;        // 0C
		ObjectRefHandle target;       // 10
		std::uint32_t   pad14;        // 14
		std::uint8_t    unk18[0x10];  // 18 - BSTArrayHeapAllocator-constructed (likely a BSTArray<T>); element type unconfirmed
		std::uint32_t   unk28;        // 28
		std::uint8_t    pad2C[0x14];  // 2C - untouched by the ctor
	};
	static_assert(sizeof(PatrolActorPackageData) == 0x40);
}

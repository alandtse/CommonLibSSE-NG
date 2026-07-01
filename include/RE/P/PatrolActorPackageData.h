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
		std::uint32_t   unk08;   // 08 - observed 5
		std::uint32_t   pad0C;   // 0C
		ObjectRefHandle target;  // 10
		std::uint32_t   pad14;   // 14
		// 18: array-like block; sub_1407110F0 constructs it via BSTArray<BGSInstancedQuestObjective>::Ctor.
		// Not this repo's RE::BSTArray<T> byte-for-byte (that's 0x18 here, this block is only 0x10).
		std::uint8_t    objectives18[0x10];  // 18
		std::uint32_t   unk28;               // 28
		std::uint32_t   pad2C;               // 2C
		ObjectRefHandle refHandle30;         // 30
		bool            unk34;               // 34
		bool            unk35;               // 35 - observed true
		std::uint16_t   pad36;               // 36
		std::uint32_t   unk38;               // 38
		std::uint32_t   pad3C;               // 3C
	};
	static_assert(sizeof(PatrolActorPackageData) == 0x40);
}

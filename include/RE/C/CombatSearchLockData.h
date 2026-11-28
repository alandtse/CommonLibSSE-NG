#pragma once

#include "RE/B/BSPathingLockData.h"

namespace RE
{
	class CombatSearchLockData : public BSPathingLockData
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatSearchLockData;
		inline static constexpr auto VTABLE = VTABLE_CombatSearchLockData;

		~CombatSearchLockData() override;                                                   // 00
		std::uint32_t      GetType() const override;                                        // 01
		bool               TryPassDoor(BSPathingDoor** a_door, float* a_costOut) override;  // 02
		void               Write(void* a_stream) const override;                            // 04
		void               Read(void* a_stream) override;                                   // 05
		BSPathingLockData* Clone() const override;                                          // 06

		// members
		std::uint32_t actorHandle;          // 10
		std::uint32_t pad14;                // 14
		std::uint8_t  ownerLockData[0x28];  // 18 - ActorLockData
		bool          useMinimalUseCost;    // 40
		std::uint8_t  pad41[7];             // 41
	};
	static_assert(sizeof(CombatSearchLockData) == 0x48);
}

#pragma once

#include "RE/A/AITimer.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/C/CombatObject.h"

namespace RE
{
	class CombatController;

	class CombatTargetSelector : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatTargetSelector;
		inline static constexpr auto VTABLE = VTABLE_CombatTargetSelector;

		~CombatTargetSelector() override;  // 00

		// members
		CombatController* combatController;  // 10
		ActorHandle       targetHandle;      // 18
		std::uint32_t     unk1C;             // 1C
		std::uint32_t     unk20;             // 20
	};
	static_assert(sizeof(CombatTargetSelector) == 0x28);

	class CombatTargetSelectorFixed : public CombatTargetSelector
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatTargetSelectorFixed;
		inline static constexpr auto VTABLE = VTABLE_CombatTargetSelectorFixed;

		~CombatTargetSelectorFixed() override;  // 00
	};
	static_assert(sizeof(CombatTargetSelectorFixed) == 0x28);

	class CombatTargetSelectorStandard : public CombatTargetSelector
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatTargetSelectorStandard;
		inline static constexpr auto VTABLE = VTABLE_CombatTargetSelectorStandard;

		~CombatTargetSelectorStandard() override;  // 00

		// members
		AITimer unk28;  // 28
	};
	static_assert(sizeof(CombatTargetSelectorStandard) == 0x30);
}

#pragma once

#include "RE/C/CombatAimController.h"

namespace RE
{
	class CombatTrackTargetAimController : public CombatAimController
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatTrackTargetAimController;
		inline static constexpr auto VTABLE = VTABLE_CombatTrackTargetAimController;

		~CombatTrackTargetAimController() override;  // 00

		// members
		std::uint32_t unk48;  // 48
		std::uint8_t  unk4C;  // 4C
	};
	static_assert(sizeof(CombatTrackTargetAimController) == 0x50);

	class CombatMeleeAimController : public CombatTrackTargetAimController
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatMeleeAimController;
		inline static constexpr auto VTABLE = VTABLE_CombatMeleeAimController;

		~CombatMeleeAimController() override;  // 00

		// members
		std::uint32_t unk50;  // 50
	};
	static_assert(sizeof(CombatMeleeAimController) == 0x58);
}

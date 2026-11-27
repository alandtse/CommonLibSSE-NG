#pragma once

#include "RE/A/AITimer.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/C/CombatObject.h"

namespace RE
{
	class CombatPathSpeedController : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathSpeedController;
		inline static constexpr auto VTABLE = VTABLE_CombatPathSpeedController;

		~CombatPathSpeedController() override;  // 00
	};
	static_assert(sizeof(CombatPathSpeedController) == 0x10);

	class CombatApproachTargetSpeedController : public CombatPathSpeedController
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatApproachTargetSpeedController;
		inline static constexpr auto VTABLE = VTABLE_CombatApproachTargetSpeedController;

		~CombatApproachTargetSpeedController() override;  // 00

		// members
		ObjectRefHandle handle10;  // 10
		std::uint32_t   unk14;     // 14
		std::uint32_t   unk18;     // 18
		std::uint32_t   unk1C;     // 1C
		std::uint32_t   unk20;     // 20
		AITimer         unk24;     // 24
		std::uint32_t   unk2C;     // 2C
	};
	static_assert(sizeof(CombatApproachTargetSpeedController) == 0x30);

	class DiveBombSpeedController : public CombatPathSpeedController
	{
	public:
		inline static constexpr auto RTTI = RTTI_DiveBombSpeedController;
		inline static constexpr auto VTABLE = VTABLE_DiveBombSpeedController;

		~DiveBombSpeedController() override;  // 00

		// members
		std::uint32_t handle10;  // 10
	};
	static_assert(sizeof(DiveBombSpeedController) == 0x18);

	class CombatDisableActionController : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatDisableActionController;
		inline static constexpr auto VTABLE = VTABLE_CombatDisableActionController;

		~CombatDisableActionController() override;  // 00

		// members
		ActorHandle actorHandle;  // 10
	};
	static_assert(sizeof(CombatDisableActionController) == 0x18);
}

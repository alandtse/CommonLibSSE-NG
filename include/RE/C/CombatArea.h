#pragma once

#include "RE/A/AITimer.h"
#include "RE/B/BGSWorldLocation.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/C/CombatObject.h"

namespace RE
{
	class CombatController;
	class TESForm;

	class CombatArea : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatArea;
		inline static constexpr auto VTABLE = VTABLE_CombatArea;

		~CombatArea() override;  // 00

		// members
		CombatController* combatController;  // 10
		TESForm*          unk18;             // 18
		AITimer           unk20;             // 20
		std::uint32_t     unk28;             // 28
		std::uint8_t      unk2C;             // 2C
		std::uint8_t      unk2D;             // 2D
	};
	static_assert(sizeof(CombatArea) == 0x30);

	class CombatAreaRadius : public CombatArea
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatAreaRadius;
		inline static constexpr auto VTABLE = VTABLE_CombatAreaRadius;

		~CombatAreaRadius() override;  // 00

		// members
		BGSWorldLocation center;  // 30
		float            radius;  // 48
	};
	static_assert(sizeof(CombatAreaRadius) == 0x50);

	class CombatAreaStandard : public CombatAreaRadius
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatAreaStandard;
		inline static constexpr auto VTABLE = VTABLE_CombatAreaStandard;

		~CombatAreaStandard() override;  // 00
	};
	static_assert(sizeof(CombatAreaStandard) == 0x50);

	class CombatAreaReference : public CombatAreaRadius
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatAreaReference;
		inline static constexpr auto VTABLE = VTABLE_CombatAreaReference;

		~CombatAreaReference() override;  // 00

		// members
		ObjectRefHandle refHandle;  // 50
		AITimer         unk54;      // 54
	};
	static_assert(sizeof(CombatAreaReference) == 0x60);

	class CombatAreaHoldPosition : public CombatAreaReference
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatAreaHoldPosition;
		inline static constexpr auto VTABLE = VTABLE_CombatAreaHoldPosition;

		~CombatAreaHoldPosition() override;  // 00
	};
	static_assert(sizeof(CombatAreaHoldPosition) == 0x60);
}

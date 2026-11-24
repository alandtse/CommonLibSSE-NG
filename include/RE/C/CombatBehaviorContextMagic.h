#pragma once

#include "RE/C/CombatBehaviorContext.h"
#include "RE/M/MagicSystem.h"

namespace RE
{
	class ActorMagicCaster;
	class CombatInventoryItemMagic;
	class CombatMagicCaster;
	class CombatProjectileAimController;
	class MagicItem;

	class CombatBehaviorContextMagic : public CombatBehaviorContext
	{
	public:
		CombatBehaviorContextMagic(CombatInventoryItemMagic* citem);

		float                    CalcCastMagicChance() const;
		float                    CalcDualCastMagicChance() const;
		MagicSystem::CastingType GetCastingType();

		void ReleaseMembers()
		{
			using func_t = void(CombatBehaviorContextMagic*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(48036, 49082) };
			func(this);
		}
		bool StartCast(bool a_atPlayer)
		{
			using func_t = bool(CombatBehaviorContextMagic*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(48037, 49083) };
			return func(this, a_atPlayer);
		}
		void PrepareCastAnimation()
		{
			using func_t = void(CombatBehaviorContextMagic*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(48038, 49085) };
			func(this);
		}
		void InterruptCast()
		{
			using func_t = void(CombatBehaviorContextMagic*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(48040, 49087) };
			func(this);
		}
		void* GetCastTarget(void* a_out)
		{
			using func_t = void*(CombatBehaviorContextMagic*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(48041, 49088) };
			return func(this, a_out);
		}
		bool CanCastNow(void* a_ctx)
		{
			using func_t = bool(CombatBehaviorContextMagic*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(48043, 49090) };
			return func(this, a_ctx);
		}
		bool IsWithinCastRange(void* a_ctx)
		{
			using func_t = bool(CombatBehaviorContextMagic*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(48044, 49091) };
			return func(this, a_ctx);
		}
		bool IsCastTargetUsable()
		{
			using func_t = bool(CombatBehaviorContextMagic*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(48045, 49092) };
			return func(this);
		}
		bool IsAimReady()
		{
			using func_t = bool(CombatBehaviorContextMagic*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(48046, 49093) };
			return func(this);
		}
		bool IsMagicItemSelected()
		{
			using func_t = bool(CombatBehaviorContextMagic*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(48049, 49096) };
			return func(this);
		}
		bool CanAffordCast()
		{
			using func_t = bool(CombatBehaviorContextMagic*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(48050, 49097) };
			return func(this);
		}

		// members
		ActorMagicCaster*              magicCaster;     // 00
		MagicItem*                     mitem;           //		08
		CombatMagicCaster*             combatMcaster;   // 10
		CombatProjectileAimController* projAimControl;  // 18
	};
	static_assert(sizeof(CombatBehaviorContextMagic) == 0x20);
}

#include "RE/C/CombatPathingGoalPolicy.h"

namespace RE
{
	void CombatPathingGoalPolicyFindTargetLocation::SaveGame(BGSSaveGameBuffer* a_buf)
	{
		using func_t = decltype(&CombatPathingGoalPolicyFindTargetLocation::SaveGame);
		static REL::Relocation<func_t> func{ RELOCATION_ID(45741, 47054) };
		return func(this, a_buf);
	}

	void CombatPathingGoalPolicyFindTargetLocation::LoadGame(BGSLoadGameBuffer* a_buf)
	{
		using func_t = decltype(&CombatPathingGoalPolicyFindTargetLocation::LoadGame);
		static REL::Relocation<func_t> func{ RELOCATION_ID(45742, 47055) };
		return func(this, a_buf);
	}

	void CombatPathingGoalPolicyFlank::SaveGame(BGSSaveGameBuffer* a_buf)
	{
		using func_t = decltype(&CombatPathingGoalPolicyFlank::SaveGame);
		static REL::Relocation<func_t> func{ RELOCATION_ID(47142, 48387) };
		return func(this, a_buf);
	}

	void CombatPathingGoalPolicyFlank::LoadGame(BGSLoadGameBuffer* a_buf)
	{
		using func_t = decltype(&CombatPathingGoalPolicyFlank::LoadGame);
		static REL::Relocation<func_t> func{ RELOCATION_ID(47143, 48388) };
		return func(this, a_buf);
	}

	void CombatPathingGoalPolicyRetreat::SaveGame(BGSSaveGameBuffer* a_buf)
	{
		using func_t = decltype(&CombatPathingGoalPolicyRetreat::SaveGame);
		static REL::Relocation<func_t> func{ RELOCATION_ID(49317, 50538) };
		return func(this, a_buf);
	}

	void CombatPathingGoalPolicyRetreat::LoadGame(BGSLoadGameBuffer* a_buf)
	{
		using func_t = decltype(&CombatPathingGoalPolicyRetreat::LoadGame);
		static REL::Relocation<func_t> func{ RELOCATION_ID(49318, 50539) };
		return func(this, a_buf);
	}

	void CombatPathingGoalPolicyReturnToCombatArea::SaveGame(BGSSaveGameBuffer* a_buf)
	{
		using func_t = decltype(&CombatPathingGoalPolicyReturnToCombatArea::SaveGame);
		static REL::Relocation<func_t> func{ RELOCATION_ID(48240, 49270) };
		return func(this, a_buf);
	}

	void CombatPathingGoalPolicyReturnToCombatArea::LoadGame(BGSLoadGameBuffer* a_buf)
	{
		using func_t = decltype(&CombatPathingGoalPolicyReturnToCombatArea::LoadGame);
		static REL::Relocation<func_t> func{ RELOCATION_ID(48241, 49271) };
		return func(this, a_buf);
	}

	void CombatPathingGoalPolicyFindAttackLocation::SaveGame(BGSSaveGameBuffer* a_buf)
	{
		using func_t = decltype(&CombatPathingGoalPolicyFindAttackLocation::SaveGame);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46972, 48144) };
		return func(this, a_buf);
	}
}

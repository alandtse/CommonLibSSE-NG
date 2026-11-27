#include "RE/C/CombatAcquireItem.h"

namespace RE
{
	bool CombatAcquireItem::IsValid() const
	{
		using func_t = decltype(&CombatAcquireItem::IsValid);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46338, 47580) };
		return func(this);
	}

	void CombatAcquireItem::LoadGame(BGSLoadGameBuffer* a_buffer)
	{
		using func_t = decltype(&CombatAcquireItem::LoadGame);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46340, 47582) };
		return func(this, a_buffer);
	}

	void CombatAcquireItem::SaveGame(BGSSaveGameBuffer* a_buffer)
	{
		using func_t = decltype(&CombatAcquireItem::SaveGame);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46339, 47581) };
		return func(this, a_buffer);
	}
}

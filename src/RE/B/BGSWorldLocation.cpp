#include "RE/B/BGSWorldLocation.h"

namespace RE
{
	void BGSWorldLocation::SaveGame(BGSSaveGameBuffer* a_buf)
	{
		using func_t = decltype(&BGSWorldLocation::SaveGame);
		static REL::Relocation<func_t> func{ RELOCATION_ID(18135, 18521) };
		return func(this, a_buf);
	}

	void BGSWorldLocation::LoadGame(BGSLoadGameBuffer* a_buf)
	{
		using func_t = decltype(&BGSWorldLocation::LoadGame);
		static REL::Relocation<func_t> func{ RELOCATION_ID(18136, 18522) };
		return func(this, a_buf);
	}
}

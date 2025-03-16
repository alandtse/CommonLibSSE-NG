#include "RE/B/BGSFootstepManager.h"

namespace RE
{
	BGSFootstepManager* BGSFootstepManager::GetSingleton()
	{
		static REL::Relocation<BGSFootstepManager**> singleton{ RELOCATION_ID(517045, 401262) };
		return *singleton;
	}
}

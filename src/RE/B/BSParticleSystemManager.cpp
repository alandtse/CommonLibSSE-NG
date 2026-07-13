#include "RE/B/BSParticleSystemManager.h"

#include "REL/Relocation.h"

namespace RE
{
	bool BSParticleSystemManager::IsValidMasterParticleSystem(std::uint32_t a_index)
	{
		using func_t = decltype(&BSParticleSystemManager::IsValidMasterParticleSystem);
		static REL::Relocation<func_t> func{ RELOCATION_ID(74857, 76605) };
		return func(this, a_index);
	}

	BSMasterParticleSystem* BSParticleSystemManager::GetMasterParticleSystemAt(std::uint32_t a_index)
	{
		using func_t = decltype(&BSParticleSystemManager::GetMasterParticleSystemAt);
		static REL::Relocation<func_t> func{ RELOCATION_ID(74860, 76608) };
		return func(this, a_index);
	}
}

#include "RE/B/BSTempNodeManager.h"

#include "REL/Relocation.h"

namespace RE
{
	void BSTempNodeManager::UpdateTempNodeTimers(float a_elapsedTime)
	{
		using func_t = decltype(&BSTempNodeManager::UpdateTempNodeTimers);
		static REL::Relocation<func_t> func{ RELOCATION_ID(74387, 76110) };
		return func(this, a_elapsedTime);
	}
}

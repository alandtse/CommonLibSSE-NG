#include "RE/B/BSCullingProcess.h"

namespace RE
{
	bool BSCullingProcess::AddShared(NiAVObject* a_object)
	{
		using func_t = decltype(&BSCullingProcess::AddShared);
		static REL::Relocation<func_t> func{ RELOCATION_ID(74812, 76562) };
		return func(this, a_object);
	}

}
#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	class NiBound
	{
	public:
		void ComputeFromData(int a_count, NiPoint3* a_vertices)
		{
			using func_t = void(NiBound*, int, NiPoint3*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(69587, 70972) };
			func(this, a_count, a_vertices);
		}

		// members
		NiPoint3 center;  // 00
		float    radius;  // 0C
	};
	static_assert(sizeof(NiBound) == 0x10);
}

#include "RE/M/MovementControllerAI.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	bool MovementControllerAI::Unk_09()
	{
		return REL::RelocateVirtual<decltype(&MovementControllerAI::Unk_09)>(0x09, 0x0A, this);
	}
#endif
}

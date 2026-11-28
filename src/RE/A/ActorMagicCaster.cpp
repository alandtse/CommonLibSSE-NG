#include "RE/A/ActorMagicCaster.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void ActorMagicCaster::Update(float a_delta)
	{
		REL::RelocateVirtual<decltype(&ActorMagicCaster::Update)>(0x1D, 0x1F, this, a_delta);
	}
#endif
}

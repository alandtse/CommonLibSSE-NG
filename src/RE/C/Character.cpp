#include "RE/C/Character.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void Character::Unk_128()
	{
		REL::RelocateVirtual<decltype(&Character::Unk_128)>(0x128, 0x12A, this);
	}

	void Character::Unk_129()
	{
		REL::RelocateVirtual<decltype(&Character::Unk_129)>(0x129, 0x12B, this);
	}
#endif
}

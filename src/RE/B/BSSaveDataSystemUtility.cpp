#include "RE/B/BSSaveDataSystemUtility.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void BSSaveDataSystemUtility::Entry::Read(const char* a_path)
	{
		REL::RelocateVirtual<decltype(&BSSaveDataSystemUtility::Entry::Read)>(0x00, 0x01, this, a_path);
	}
#endif
}

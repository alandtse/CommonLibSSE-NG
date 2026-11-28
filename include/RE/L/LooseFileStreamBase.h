#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSSystemFile.h"
#include "REL/Common.h"

namespace RE
{
	namespace BSResource
	{
		struct LooseFileStreamBase
		{
		public:
#ifdef EXCLUSIVE_SKYRIM_AE
			virtual ~LooseFileStreamBase();  // 00 - AE only
#endif

			// members
			BSFixedString prefix;    // 00 (AE 08)
			BSFixedString dirName;   // 08 (AE 10)
			BSFixedString fileName;  // 10 (AE 18)
			BSSystemFile  file;      // 18 (AE 20)
		};
#ifdef EXCLUSIVE_SKYRIM_AE
		static_assert(sizeof(LooseFileStreamBase) == 0x30);
#else
		static_assert(sizeof(LooseFileStreamBase) == 0x28);
#endif
	}
}

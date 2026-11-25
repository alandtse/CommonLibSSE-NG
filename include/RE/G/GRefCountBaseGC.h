#pragma once

#include "RE/G/GNewOverrideBase.h"

namespace RE
{
	template <std::uint32_t STAT>
	class GRefCountBaseGC : public GNewOverrideBase<STAT>
	{
	public:
		enum
		{
			kStatType = STAT
		};

		// add
		virtual void Unk_00(void);  // 00
		virtual void Unk_01(void);  // 01 - pure

		virtual ~GRefCountBaseGC();  // 02

		// members
		void*         pRCCRaw;          // 08 - GASRefCountCollector*, scan-list next while buffered
		std::uint32_t refCount;         // 10 - low 26 bits count, high bits collector colour and flags
		std::uint32_t pad14;            // 14
		std::uint64_t rootIndexOrPrev;  // 18 - Roots slot index, scan-list prev while buffered
	};
	// size == 0x20
}

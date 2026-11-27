#pragma once

#include "RE/N/NiMath.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BGSLoadGameBuffer;
	class BGSSaveGameBuffer;
	class TESForm;

	struct BGSWorldLocation
	{
		[[nodiscard]] float GetDistance(const BGSWorldLocation& a_rhs) const { return space != a_rhs.space ? NI_INFINITY : pos.GetDistance(a_rhs.pos); }
		[[nodiscard]] float GetSquaredDistance(const BGSWorldLocation& a_rhs) const { return space != a_rhs.space ? NI_INFINITY : pos.GetSquaredDistance(a_rhs.pos); }

		void SaveGame(BGSSaveGameBuffer* a_buf);
		void LoadGame(BGSLoadGameBuffer* a_buf);

		// members
		NiPoint3 pos;    // 00
		TESForm* space;  // 10
	};
	static_assert(sizeof(BGSWorldLocation) == 0x18);
}

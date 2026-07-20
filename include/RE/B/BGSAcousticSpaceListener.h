#pragma once

#include "RE/H/hkpEntityListener.h"

namespace RE
{
	class BGSAcousticSpaceListener : public hkpEntityListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSAcousticSpaceListener;
		inline static constexpr auto VTABLE = VTABLE_BGSAcousticSpaceListener;

		~BGSAcousticSpaceListener() override;  // 00

		// override (hkpEntityListener)
		void EntityRemovedCallback(hkpEntity* a_entity) override;  // 02

		// add
		virtual void Unk_06(void);  // 06 - removes an entry from an internal handle set
		virtual void Unk_07(void);  // 07 - inserts an entry into the same handle set

		// members
		std::uint8_t unk08[0x48];  // 08 - not yet RE'd
	};
	static_assert(sizeof(BGSAcousticSpaceListener) == 0x50);
}

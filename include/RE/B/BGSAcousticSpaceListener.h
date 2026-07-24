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

		class hkpCollidable;

		// add
		virtual void RemoveCollidable(const hkpCollidable* a_collidable);  // 06
		virtual void AddCollidable(const hkpCollidable* a_collidable);     // 07

		// members
		std::uint8_t unk08[0x48];  // 08 - not yet RE'd
	};
	static_assert(sizeof(BGSAcousticSpaceListener) == 0x50);
}

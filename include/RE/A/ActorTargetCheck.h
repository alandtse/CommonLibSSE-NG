#pragma once

#include "RE/P/ProcessLists.h"

namespace RE
{
	class ActorTargetCheck : public ProcessLists::GetActorsFilter
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActorTargetCheck;
		inline static constexpr auto VTABLE = VTABLE_ActorTargetCheck;

		~ActorTargetCheck() override;  // 00

		// override (GetActorsFilter)
		bool IsValid(Actor* a_actor) override;  // 01

		// members
		std::uint64_t unk08;   // 08
		Actor*        caster;  // 10 - excluded from valid targets (MagicCaster::GetOwner2)
		std::uint64_t unk18;   // 18
	};
	static_assert(sizeof(ActorTargetCheck) == 0x20);
}

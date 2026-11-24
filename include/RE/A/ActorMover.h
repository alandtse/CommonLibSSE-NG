#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	class Actor;

	class ActorMover
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActorMover;
		inline static constexpr auto VTABLE = VTABLE_ActorMover;

		virtual ~ActorMover();  // 00

		// add
		virtual void Unk_01(void);  // 01 - { return; }
		virtual void Unk_02(void);  // 02 - { return 0; }
		virtual void Unk_03(void);  // 03 - { return 0; }

		bool TurnToFace(NiPoint3* a_target, float a_tolerance)
		{
			using func_t = bool(ActorMover*, NiPoint3*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(40591, 41620) };
			return func(this, a_target, a_tolerance);
		}

		// members
		Actor* actor;  // 08
	};
	static_assert(sizeof(ActorMover) == 0x10);
}

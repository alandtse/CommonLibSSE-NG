#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementSetGoal : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementSetGoal;
		inline static constexpr auto VTABLE = VTABLE_IMovementSetGoal;

		~IMovementSetGoal() override;  // 00

		// add
		virtual bool SetGoal(void* a_request) = 0;  // 01
		virtual void Unk_02(void) = 0;              // 02 - SetGoalWithoutSolving
		virtual void ClearGoal() = 0;               // 03
		virtual void Unk_04(void) = 0;              // 04 - RepathFromCurrentLocation

		void RepathFromCurrentLocation()
		{
			using func_t = void(IMovementSetGoal*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88431, 90855) };
			func(this);
		}
		void SetGoalWithoutSolving(void* a_p1, void* a_request, void* a_p3)
		{
			using func_t = void(IMovementSetGoal*, void*, void*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88432, 90856) };
			func(this, a_p1, a_request, a_p3);
		}
	};
	static_assert(sizeof(IMovementSetGoal) == 0x8);
}

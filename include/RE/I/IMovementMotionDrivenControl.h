#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementMotionDrivenControl : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementMotionDrivenControl;
		inline static constexpr auto VTABLE = VTABLE_IMovementMotionDrivenControl;

		~IMovementMotionDrivenControl() override;  // 00

		// add
		virtual void PrepareAnimationDrivenAgents() = 0;  // 01
		virtual void PrepareMotionDrivenAgents() = 0;     // 02
		virtual void SetAnimationDriven(void) = 0;        // 03
		virtual void SetMotionDriven(void) = 0;           // 04
		virtual void Unk_05(void) = 0;                    // 05
		virtual bool IsMotionDriven(void) = 0;            // 06
		virtual void Unk_07(void) = 0;                    // 07
		virtual void Unk_08(void) = 0;                    // 08
	};
	static_assert(sizeof(IMovementMotionDrivenControl) == 0x8);
}

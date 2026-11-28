#pragma once

#include "RE/I/IMovementInterface.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class IMovementDirectControl : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementDirectControl;
		inline static constexpr auto VTABLE = VTABLE_IMovementDirectControl;

		~IMovementDirectControl() override;  // 00

		// add
		virtual void EnableDirectControl() = 0;                                // 01
		virtual void SetDirection(NiPoint3* a_direction) = 0;                  // 02
		virtual void SetSpeed(float a_speed) = 0;                              // 03
		virtual void SetRotation(NiPoint3* a_rotation) = 0;                    // 04
		virtual void BlendDirection(NiPoint3* a_direction, float a_time) = 0;  // 05
		virtual void BlendSpeed(float a_speed, float a_time) = 0;              // 06
		virtual void BlendRotation(NiPoint3* a_rotation, float a_time) = 0;    // 07
		virtual void DisableDirectControl() = 0;                               // 08
	};
	static_assert(sizeof(IMovementDirectControl) == 0x8);
}

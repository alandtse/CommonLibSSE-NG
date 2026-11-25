#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class NiPoint3;
	class NiTransform;
	struct MovementPlayIdleData;

	class IMovementQueryTweener : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementQueryTweener;
		inline static constexpr auto VTABLE = VTABLE_IMovementQueryTweener;

		~IMovementQueryTweener() override;  // 00

		// add
		virtual bool                  GetTweenerTransform(NiTransform& a_out) = 0;                     // 01
		virtual bool                  GetTweenerVelocity(NiPoint3& a_velocity, float& a_yawRate) = 0;  // 02
		virtual MovementPlayIdleData* GetPlayIdleData() = 0;                                           // 03
	};
	static_assert(sizeof(IMovementQueryTweener) == 0x8);
}

#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class NiPoint3;

	class IMovementState : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementState;
		inline static constexpr auto VTABLE = VTABLE_IMovementState;

		bool CanStrafe() const;

		~IMovementState() override;  // 00

		// add
		virtual void  Unk_01(void) = 0;          // 01 - GetFormID() -> std::uint32_t
		virtual void  Unk_02(void) = 0;          // 02 - GetPathingLocation(BSPathingLocation&)
		virtual void  Unk_03(void) = 0;          // 03 - GetPosition(NiPoint3&)
		virtual void  Unk_04(void) = 0;          // 04 - GetAngle(NiPoint3&)
		virtual float DoGetMovementSpeed() = 0;  // 05 - GetCurrentMovementSpeed()
		virtual float DoGetRotationSpeed() = 0;  // 06 - GetYawRotationSpeed()
		virtual void  Unk_07(void) = 0;          // 07 - GetProcessRotation(NiPoint3&)
		virtual void  Unk_08(void) = 0;          // 08 - GetMaxSpeeds(Movement::MaxSpeeds&) -> bool
		virtual void  Unk_09(void) = 0;          // 09 - GetRadius() -> float
		virtual void  Unk_0A(void) = 0;          // 0A - GetWidth() -> float
		virtual void  Unk_0B(void) = 0;          // 0B - GetLength() -> float
		virtual void  Unk_0C(void) = 0;          // 0C - GetScaledBoundSize() -> float
		virtual void  Unk_0D(void) = 0;          // 0D - GetReducedScaledBoundSize() -> float
		virtual void  Unk_0E(void) = 0;          // 0E - GetMovementParameters(BSTSmartPointer<IMovementParameters>&) -> bool
		virtual void  Unk_0F(void) = 0;          // 0F - GetMovementParametersType() -> const void*
		virtual void  Unk_10(void) = 0;          // 10 - GetMovementTypeIdleThresholds(NiPoint3&) -> bool
		virtual void  Unk_11(void) = 0;          // 11 - GetCharacterState
		virtual void  Unk_12(void) = 0;          // 12 - IsMountedByPlayer() -> bool
		virtual void  Unk_13(void) = 0;          // 13 - UsesVelocityObstacles() -> bool
	};
	static_assert(sizeof(IMovementState) == 0x8);
}

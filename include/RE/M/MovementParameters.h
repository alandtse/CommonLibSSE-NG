#pragma once

#include "RE/I/IMovementParameters.h"

namespace RE
{
	class MovementParameters : public IMovementParameters
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementParameters;
		inline static constexpr auto VTABLE = VTABLE_MovementParameters;

		~MovementParameters() override;  // 00

		// override
		float GetSpeed() override;                                // 01
		float GetInverseAcceleration() override;                  // 02
		float GetInverseDeceleration() override;                  // 03
		float GetInverseAngleAcceleration() override;             // 04
		float GetRotationSpeed() override;                        // 05
		void  Unk_06(void) override;                              // 06
		void  SaveGame(BSPathingStreamWrite& a_stream) override;  // 07
		void  LoadGame(BSPathingStreamRead& a_stream) override;   // 08

		// members
		float         speed;               // 10
		float         invAccelerate;       // 14
		float         invDecelerate;       // 18
		float         rotationSpeed;       // 1C
		float         invAngleAccelerate;  // 20
		std::uint32_t pad24;               // 24
	};
	static_assert(sizeof(MovementParameters) == 0x28);
}

#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/I/IMovementParameters.h"

namespace RE
{
	class Actor;

	class MovementParametersFixed : public IMovementParameters
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementParametersFixed;
		inline static constexpr auto VTABLE = VTABLE_MovementParametersFixed;

		~MovementParametersFixed() override;  // 00

		// override
		float GetSpeed() override;                                // 01
		float GetInverseAcceleration() override;                  // 02
		float GetInverseDeceleration() override;                  // 03
		float GetInverseAngleAcceleration() override;             // 04
		float GetParam1C() override;                              // 05
		void  Unk_06(void) override;                              // 06
		void  SaveGame(BSPathingStreamWrite& a_stream) override;  // 07
		void  LoadGame(BSPathingStreamRead& a_stream) override;   // 08

		// members
		float       speed;               // 10
		float       invAccelerate;       // 14
		float       invDecelerate;       // 18
		float       param1C;             // 1C
		float       invAngleAccelerate;  // 20
		ActorHandle actorHandle;         // 24
	};
	static_assert(sizeof(MovementParametersFixed) == 0x28);
}

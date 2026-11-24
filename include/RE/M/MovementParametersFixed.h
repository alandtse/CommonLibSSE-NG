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
		float GetParam10() override;                              // 01
		float GetParam14() override;                              // 02
		float GetParam18() override;                              // 03
		float GetParam20() override;                              // 04
		float GetParam1C() override;                              // 05
		void  Unk_06(void) override;                              // 06
		void  SaveGame(BSPathingStreamWrite& a_stream) override;  // 07
		void  LoadGame(BSPathingStreamRead& a_stream) override;   // 08

		// members
		float       param10;      // 10
		float       param14;      // 14
		float       param18;      // 18
		float       param1C;      // 1C
		float       param20;      // 20
		ActorHandle actorHandle;  // 24
	};
	static_assert(sizeof(MovementParametersFixed) == 0x28);
}

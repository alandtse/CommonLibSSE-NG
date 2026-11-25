#pragma once

#include "RE/M/MovementControllerAI.h"
#include "RE/M/MovementUpdateDeltas.h"

namespace RE
{
	// Final pipeline stage: republishes the deltas, position and angle through IMovementQueryDeltas (sub-object at 0x18).
	class MovementPostUpdateArbiter : public MovementArbiter
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPostUpdateArbiter;

		~MovementPostUpdateArbiter() override;  // 00

		// override (MovementArbiter)
		void RegisterWithController(IMovementControllerRegisterInterface& a_controller) override;  // 04 - stores the interface at 0x58 and registers the 0x18 sub-object
		void UnregisterWithController() override;                                                  // 0C - unregisters the 0x18 sub-object and clears 0x58
		void SaveGame(BSPathingStreamWrite& a_stream) override;                                    // 0D - nine floats from 0x20
		void LoadGame(BSPathingStreamRead& a_stream) override;                                     // 0E

		// members
		void*                                 queryDeltasVtbl;    // 18 - IMovementQueryDeltas sub-object vftable
		MovementUpdateDeltas                  deltas;             // 20
		NiPoint3                              position;           // 3C
		NiPoint3                              angle;              // 48
		float                                 deltaTime;          // 54
		IMovementControllerRegisterInterface* registerInterface;  // 58
	};
	static_assert(sizeof(MovementPostUpdateArbiter) == 0x60);
}

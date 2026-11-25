#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSPathingLocation.h"
#include "RE/B/BSTArray.h"
#include "RE/I/IAnimationSetCallbackFunctor.h"
#include "RE/I/IMovementDirectControl.h"
#include "RE/I/IMovementMessageInterface.h"
#include "RE/I/IMovementMotionDrivenControl.h"
#include "RE/I/IMovementPlannerDirectControl.h"
#include "RE/I/IMovementSelectIdle.h"
#include "RE/M/MovementControllerAI.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class Actor;
	class MovementMessage;
	class MovementMessagePlayIdle;

	struct MovementLocationEvent
	{
	public:
		BSPathingLocation location;      // 00
		NiPoint3          direction;     // 30
		std::uint32_t     messageIndex;  // 3C
	};
	static_assert(sizeof(MovementLocationEvent) == 0x40);

	class MovementControllerNPC :
		public MovementControllerAI,           // 000
		public IMovementMessageInterface,      // 120
		public IMovementMotionDrivenControl,   // 128
		public IMovementSelectIdle,            // 130
		public IMovementDirectControl,         // 138
		public IMovementPlannerDirectControl,  // 140
		public IAnimationSetCallbackFunctor    // 148
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementControllerNPC;
		inline static constexpr auto VTABLE = VTABLE_MovementControllerNPC;

		~MovementControllerNPC() override;  // 00

		// add
		SKYRIM_REL_VR_VIRTUAL void Unk_0A(void);         // 0A
		SKYRIM_REL_VR_VIRTUAL void Unk_0B(void);         // 0B
		SKYRIM_REL_VR_VIRTUAL void SetAIDriven();        // 0C
		SKYRIM_REL_VR_VIRTUAL void SetControlsDriven();  // 0D
		SKYRIM_REL_VR_VIRTUAL bool GetAIDriven();        // 0E - { return controlsDriven == 0; }
		SKYRIM_REL_VR_VIRTUAL bool GetControlsDriven();  // 0F - { return controlsDriven; }
		SKYRIM_REL_VR_VIRTUAL void Unk_10(void);         // 10
		SKYRIM_REL_VR_VIRTUAL void Unk_11(void);         // 11
		SKYRIM_REL_VR_VIRTUAL void Unk_12(void);         // 12
		SKYRIM_REL_VR_VIRTUAL void Unk_13(void);         // 13
		SKYRIM_REL_VR_VIRTUAL void Unk_14(void);         // 14

		// members
		BSSpinLock                      messageLock;       // 150
		BSTArray<MovementMessage*>      movementMessages;  // 158
		BSTArray<MovementLocationEvent> locationEvents;    // 170
		BSTArray<void*>                 unk188;            // 188
		BSSpinLock                      pendingIdleLock;   // 1A0 - guards unk188, unk1A8 and pendingPlayIdle
		std::uint64_t                   unk1A8;            // 1A8
		MovementMessagePlayIdle*        pendingPlayIdle;   // 1B0 - posted through IMovementMessageInterface once the idle data is ready
		Actor*                          actor;             // 1B8
		std::uint32_t                   movementMode;      // 1C0 - 0..0xE, default 2, set by small mode setters, saved
		bool                            unk1C4;            // 1C4
		bool                            controlsDriven;    // 1C5
		bool                            unk1C6;            // 1C6
		bool                            unk1C7;            // 1C7
		bool                            unk1C8;            // 1C8
		bool                            unk1C9;            // 1C9
		bool                            unk1CA;            // 1CA
		bool                            keepingOffset;     // 1CB
		std::uint32_t                   unk1CC;            // 1CC
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(MovementControllerNPC) == 0x1D0);
#endif
}

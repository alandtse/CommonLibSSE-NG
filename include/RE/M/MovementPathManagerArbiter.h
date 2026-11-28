#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/I/IMovementQueryPathingState.h"
#include "RE/I/IMovementSetGoal.h"
#include "RE/M/MovementControllerAI.h"
#include "RE/P/PathingSolutionQueue.h"

namespace RE
{
	class BSPathingRequest;
	struct BSPathingSolution;

	// pathState: 0 idle, 1 pending, 2 valid or following, 3 complete.
	class MovementPathManagerArbiter :
		public MovementArbiter,            // 00
		public IMovementSetGoal,           // 18
		public IMovementQueryPathingState  // 20
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPathManagerArbiter;
		inline static constexpr auto VTABLE = VTABLE_MovementPathManagerArbiter;

		~MovementPathManagerArbiter() override;  // 00

		void UpdatePathing(void* a_updateData)
		{
			using func_t = void(MovementPathManagerArbiter*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88448, 90873) };
			func(this, a_updateData);
		}
		void PollPendingSolution()
		{
			using func_t = void(MovementPathManagerArbiter*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88449, 90874) };
			func(this);
		}
		void ProcessFollowerEvents(MovementUpdateDataSmallDelta* a_updateData)
		{
			using func_t = void(MovementPathManagerArbiter*, MovementUpdateDataSmallDelta*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88450, 90875) };
			func(this, a_updateData);
		}
		void StartPathFollowing(void* a_solution)
		{
			using func_t = void(MovementPathManagerArbiter*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88451, 90876) };
			func(this, a_solution);
		}
		void HandlePathFollowerEvent(int a_event, char* a_outFlag)
		{
			using func_t = void(MovementPathManagerArbiter*, int, char*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88452, 90877) };
			func(this, a_event, a_outFlag);
		}
		void CompletePath()
		{
			using func_t = void(MovementPathManagerArbiter*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88454, 90879) };
			func(this);
		}
		void ClearPath(bool a_failed)
		{
			using func_t = void(MovementPathManagerArbiter*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88455, 90880) };
			func(this, a_failed);
		}

		void PostSetStaticPathMessage(bool a_staticPath)
		{
			using func_t = void(MovementPathManagerArbiter*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88453, 90878) };
			func(this, a_staticPath);
		}

		// members
		BSTArray<void*>       agents;           // 28
		void*                 controller;       // 40
		std::uint32_t         pathState;        // 48
		std::uint32_t         pad4C;            // 4C
		BSPathingRequest*     request;          // 50
		BSPathingSolution*    solution;         // 58
		PathingSolutionQueue* pendingSolution;  // 60
		std::uint8_t          lock[0x10];       // 68 - MutexRW
		void*                 dataTracker;      // 78
	};
	static_assert(sizeof(MovementPathManagerArbiter) == 0x80);
}

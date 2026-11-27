#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/M/MovementControllerAI.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSPathingRequest;
	class NiRefObject;
	struct BSPathingSolution;
	struct MovementPlayIdleHolder;
	struct PathFollowerStateUpdateData;
	struct PathFollowerTurnTarget;

	// follows a BSPathingSolution; the six secondary vtables at 18-47 belong to IMovementPlannerAgent,
	// IMovementPathManagerAgent, IMovementQueryPathFollowing, IMovementSetPathFollowing,
	// IMovementPlayIdleResult and IMovementHandlerAgent
	class MovementAgentPathFollowerStandard : public MovementAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementAgentPathFollowerStandard;
		inline static constexpr auto VTABLE = VTABLE_MovementAgentPathFollowerStandard;

		void SetStatePlayIdle_6(PathFollowerStateUpdateData* a_updateData)
		{
			using func_t = void(MovementAgentPathFollowerStandard*, PathFollowerStateUpdateData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88332, 90743) };
			func(this, a_updateData);
		}
		void SetStateTurnToAngle_7()
		{
			using func_t = void(MovementAgentPathFollowerStandard*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88333, 90744) };
			func(this);
		}
		void UpdateActionSpeed(PathFollowerStateUpdateData* a_updateData)
		{
			using func_t = void(MovementAgentPathFollowerStandard*, PathFollowerStateUpdateData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88334, 90745) };
			func(this, a_updateData);
		}
		void SetStateFollowPathToParameter_13(PathFollowerStateUpdateData* a_updateData)
		{
			using func_t = void(MovementAgentPathFollowerStandard*, PathFollowerStateUpdateData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88335, 90746) };
			func(this, a_updateData);
		}
		void SetStateFollowPathToGoal_13(PathFollowerStateUpdateData* a_updateData)
		{
			using func_t = void(MovementAgentPathFollowerStandard*, PathFollowerStateUpdateData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88336, 90747) };
			func(this, a_updateData);
		}
		void SetStateKeepLastDirection_10(PathFollowerStateUpdateData* a_updateData)
		{
			using func_t = void(MovementAgentPathFollowerStandard*, PathFollowerStateUpdateData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88337, 90748) };
			func(this, a_updateData);
		}
		void SetStateKeepLastDirection_8(PathFollowerStateUpdateData* a_updateData)
		{
			using func_t = void(MovementAgentPathFollowerStandard*, PathFollowerStateUpdateData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88338, 90749) };
			func(this, a_updateData);
		}
		void SetStatePlayIdle_2(PathFollowerStateUpdateData* a_updateData)
		{
			using func_t = void(MovementAgentPathFollowerStandard*, PathFollowerStateUpdateData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88339, 90750) };
			func(this, a_updateData);
		}
		void SetStateTurnToAngle_3(PathFollowerStateUpdateData* a_updateData)
		{
			using func_t = void(MovementAgentPathFollowerStandard*, PathFollowerStateUpdateData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88340, 90751) };
			func(this, a_updateData);
		}
		void SetStateKeepLastDirection_9(PathFollowerStateUpdateData* a_updateData)
		{
			using func_t = void(MovementAgentPathFollowerStandard*, PathFollowerStateUpdateData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88341, 90753) };
			func(this, a_updateData);
		}
		void SetStateKeepLastDirection_11(PathFollowerStateUpdateData* a_updateData)
		{
			using func_t = void(MovementAgentPathFollowerStandard*, PathFollowerStateUpdateData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88342, 90754) };
			func(this, a_updateData);
		}
		bool TrySelectPlayIdle()
		{
			using func_t = bool(MovementAgentPathFollowerStandard*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88343, 90756) };
			return func(this);
		}
		bool TrySelectPlayIdleStationary()
		{
			using func_t = bool(MovementAgentPathFollowerStandard*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88344, 90757) };
			return func(this);
		}
		bool TrySelectPlayIdleMoving()
		{
			using func_t = bool(MovementAgentPathFollowerStandard*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88345, 90758) };
			return func(this);
		}
		bool ShouldRunPlayIdle()
		{
			using func_t = bool(MovementAgentPathFollowerStandard*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88346, 90760) };
			return func(this);
		}
		bool NeedsTurnBeforeFollowing()
		{
			using func_t = bool(MovementAgentPathFollowerStandard*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88347, 90761) };
			return func(this);
		}
		bool CanSelectPlayIdle()
		{
			using func_t = bool(MovementAgentPathFollowerStandard*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88348, 90762) };
			return func(this);
		}
		float GetFinalApproachSpeed()
		{
			using func_t = float(MovementAgentPathFollowerStandard*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88352, 90766) };
			return func(this);
		}
		void PrepareActionAtPoint(PathFollowerStateUpdateData* a_updateData, std::int32_t a_pointIndex)
		{
			using func_t = void(MovementAgentPathFollowerStandard*, PathFollowerStateUpdateData*, std::int32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88353, 90769) };
			func(this, a_updateData, a_pointIndex);
		}
		void GetActionTargetPosition(PathFollowerStateUpdateData* a_updateData, std::int32_t a_pointIndex)
		{
			using func_t = void(MovementAgentPathFollowerStandard*, PathFollowerStateUpdateData*, std::int32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88354, 90770) };
			func(this, a_updateData, a_pointIndex);
		}
		void FindNextActionPointIndex()
		{
			using func_t = void(MovementAgentPathFollowerStandard*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88360, 90778) };
			func(this);
		}
		void ReleasePlayIdle()
		{
			using func_t = void(MovementAgentPathFollowerStandard*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88361, 90780) };
			func(this);
		}
		bool GetPathDistanceToPosition(float a_position, float* a_out)
		{
			using func_t = bool(MovementAgentPathFollowerStandard*, float, float*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88362, 90781) };
			return func(this, a_position, a_out);
		}

		float ComputeRemainingDistance()
		{
			using func_t = float(MovementAgentPathFollowerStandard*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88350, 90764) };
			return func(this);
		}
		bool GetEndNodeTurnTarget(PathFollowerTurnTarget* a_out)
		{
			using func_t = bool(MovementAgentPathFollowerStandard*, PathFollowerTurnTarget*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88358, 90776) };
			return func(this, a_out);
		}
		bool GetNodeFacingMotion(PathFollowerTurnTarget* a_turnTarget, void* a_arg2, void* a_arg3)
		{
			using func_t = bool(MovementAgentPathFollowerStandard*, PathFollowerTurnTarget*, void*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88359, 90777) };
			return func(this, a_turnTarget, a_arg2, a_arg3);
		}

		// members
		void*                   secondaryVtables[6];            // 18
		std::uint8_t            playIdleState[0x18];            // 48
		std::uint8_t            turnToAngleState[0x20];         // 60
		std::uint8_t            followPathState[0x20];          // 80
		std::uint8_t            keepLastDirectionState[0x20];   // A0
		std::uint8_t            parameterReachedFunctor[0x10];  // C0 - target float at C8
		std::uint8_t            goalReachedFunctor[0x10];       // D0
		std::uint8_t            stoppedMovingFunctor[0x08];     // E0
		NiPoint3                lastPosition;                   // E8
		NiPoint3                pathPoint;                      // F4
		float                   pathPosition;                   // 100
		std::uint32_t           ownerHandle;                    // 104
		void*                   messageInterface;               // 108
		BSReadWriteLock         lock;                           // 110
		std::uint32_t           state;                          // 118
		std::uint32_t           pad11C;                         // 11C
		BSPathingRequest*       request;                        // 120 - NiPointer
		BSPathingSolution*      solution;                       // 128 - NiPointer
		MovementPlayIdleHolder* playIdleData;                   // 130
		NiRefObject*            unk138;                         // 138 - only ever null
		NiRefObject*            unk140;                         // 140 - only ever null
		void*                   currentState;                   // 148
		float                   endPathPosition;                // 150
		float                   targetPathPosition;             // 154
		float                   preparedSpeed;                  // 158
		std::int32_t            actionPointIndex;               // 15C
		std::uint32_t           unk160;                         // 160
		std::uint32_t           pad164;                         // 164
	};
	static_assert(sizeof(MovementAgentPathFollowerStandard) == 0x168);
}

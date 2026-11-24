#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	class Actor;
	class BSPathingLocation;
	class TESObjectCELL;
	class TESObjectREFR;
	class TESWorldSpace;

	class ActorMover
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActorMover;
		inline static constexpr auto VTABLE = VTABLE_ActorMover;

		virtual ~ActorMover();  // 00

		// add
		virtual void Unk_01(void);  // 01 - { return; }
		virtual void Unk_02(void);  // 02 - { return 0; }
		virtual void Unk_03(void);  // 03 - { return 0; }

		bool TurnToFace(NiPoint3* a_target, float a_tolerance)
		{
			using func_t = bool(ActorMover*, NiPoint3*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(40591, 41620) };
			return func(this, a_target, a_tolerance);
		}

		bool SetGoal(void* a_request)
		{
			using func_t = bool(ActorMover*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(40578, 41607) };
			return func(this, a_request);
		}
		bool PathToLocation(NiPoint3* a_pos, TESObjectCELL* a_cell, TESWorldSpace* a_worldSpace, float a_unkFloat, void* a_unk)
		{
			using func_t = bool(ActorMover*, NiPoint3*, TESObjectCELL*, TESWorldSpace*, float, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(40579, 41608) };
			return func(this, a_pos, a_cell, a_worldSpace, a_unkFloat, a_unk);
		}
		void PathToReference(TESObjectREFR* a_ref)
		{
			using func_t = void(ActorMover*, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(40580, 41609) };
			func(this, a_ref);
		}
		void StopMoving()
		{
			using func_t = void(ActorMover*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(40584, 41613) };
			func(this);
		}
		void ClearGoal()
		{
			using func_t = void(ActorMover*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(40585, 41614) };
			func(this);
		}
		void ResetMovementState()
		{
			using func_t = void(ActorMover*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(40589, 41618) };
			func(this);
		}

		bool PathToFollowPoint(NiPoint3* a_point)
		{
			using func_t = bool(ActorMover*, NiPoint3*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(40593, 41622) };
			return func(this, a_point);
		}
		bool GetPathingDoor(std::uint32_t* a_outDoorHandle, BSPathingLocation* a_outLocation)
		{
			using func_t = bool(ActorMover*, std::uint32_t*, BSPathingLocation*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(40606, 41635) };
			return func(this, a_outDoorHandle, a_outLocation);
		}

		// members
		Actor* actor;  // 08
	};
	static_assert(sizeof(ActorMover) == 0x10);
}

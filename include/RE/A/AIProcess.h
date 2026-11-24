#pragma once

#include "RE/A/ActorPackage.h"
#include "RE/A/ActorValues.h"
#include "RE/B/BGSDefaultObjectManager.h"
#include "RE/B/BSResourceHandle.h"
#include "RE/B/BSSimpleList.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTObjectArena.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/P/ProcessType.h"

namespace RE
{
	class BSPathingLocation;
	enum class RESET_3D_FLAGS;
	class Actor;
	class ActorKnowledge;
	class bhkCharacterController;
	class BipedAnim;
	class CombatGroup;
	class InventoryEntryData;
	class NiAVObject;
	class NiPoint3;
	class TESForm;
	class TESShout;
	struct HighProcessData;
	struct MiddleHighProcessData;

	class MiddleLowProcessData
	{
	public:
		// members
		std::int32_t hourPackageEvaluated;  // 0
	};
	static_assert(sizeof(MiddleLowProcessData) == 0x4);

	struct CachedValueData
	{
	public:
		// members
		float         value;    // 0
		bool          invalid;  // 4
		std::uint8_t  pad5;     // 5
		std::uint16_t pad6;     // 6
	};
	static_assert(sizeof(CachedValueData) == 0x8);

	struct CachedValues
	{
	public:
		enum class Flags
		{
			kNone = 0,
			kRadius = 1 << 0,
			kWidth = 1 << 1,
			kLength = 1 << 2,
			kDPS = 1 << 3,
			kMedicineEffectivenessMult = 1 << 4,
			kEyeLevel = 1 << 9,
			kConditionPreventsRun = 1 << 10,
			kForwardLength = 1 << 11,
			kActorIsGhost = 1 << 20,
			kHealthDamaged = 1 << 21,
			kMagickaPointsDamaged = 1 << 22,
			kStaminaDamaged = 1 << 23,
			kOwnerIsNPC = 1 << 25,
			kOwnerIsUndead = 1 << 26,
			kOwnerIsInCombatantFaction = 1 << 27
		};

		enum class BooleanValue
		{
			kNone = 0,
			kConditionPreventsRun = 1 << 0,
			kOwnerIsNPC = 1 << 1,
			kOwnerIsUndead = 1 << 2,
			kOwnerIsInCombatantFaction = 1 << 3
		};

		float                                     cachedRadius;         // 00
		float                                     cachedWidth;          // 04
		float                                     cachedLength;         // 08
		float                                     cachedForwardLength;  // 0C
		float                                     cachedDPS;            // 10
		float                                     cachedEyeLevel;       // 14
		float                                     cachedWalkSpeed;      // 18
		float                                     cachedRunSpeed;       // 1C
		float                                     cachedJogSpeed;       // 20
		float                                     cachedFastWalkSpeed;  // 24
		REX::EnumSet<BooleanValue, std::uint32_t> booleanValues;        // 28
		REX::EnumSet<Flags, std::uint32_t>        flags;                // 2C
		BSTArray<CachedValueData>                 actorValueCache;      // 30
		BSTArray<CachedValueData>                 maxActorValueCache;   // 48
	};
	static_assert(sizeof(CachedValues) == 0x60);

	struct ObjectstoAcquire
	{
	public:
		// members
		std::uint64_t unk00;  // 00
		std::uint64_t unk08;  // 08
		std::uint64_t unk10;  // 10
		std::uint64_t unk18;  // 18
		std::uint64_t unk20;  // 20
	};
	static_assert(sizeof(ObjectstoAcquire) == 0x28);

	class AIProcess
	{
	public:
		enum class LowProcessFlags : std::uint8_t
		{
			kNone = 0,
			kTargetActivated = 1 << 0,
			kCurrentActionComplete = 1 << 1,
			kIsAggressor = 1 << 2,
			kAlert = 1 << 3,
			kFollower = 1 << 4,
			kPackageDoneOnce = 1 << 5,
			kPackageIdleDone = 1 << 6
		};

		struct Hands
		{
			enum Hand : std::uint32_t
			{
				kLeft,
				kRight,
				kTotal
			};
		};
		using Hand = Hands::Hand;

		struct EquippedObject
		{
			TESForm*      object;  // 00
			BGSEquipSlot* slot;    // 08
		};
		static_assert(sizeof(EquippedObject) == 0x10);

		void                    AddToProcedureIndexRunning(Actor* a_actor, std::uint32_t a_num);
		void                    ClearActionHeadtrackTarget(bool a_defaultHold);
		void                    ClearFurniture(Actor* a_actor);
		void                    ClearMuzzleFlashes();
		void                    ComputeLastTimeProcessed();
		float                   GetCachedHeight() const;
		bhkCharacterController* GetCharController();
		ActorHandle             GetCommandingActor() const;
		InventoryEntryData*     GetCurrentAmmo() const;
		TESShout*               GetCurrentShout();
		InventoryEntryData*     GetCurrentWeapon(bool a_leftHand);
		TESForm*                GetEquippedLeftHand();
		TESForm*                GetEquippedRightHand();
		ObjectRefHandle         GetHeadtrackTarget() const;
		[[nodiscard]] bool      GetIsSummonedCreature() const noexcept;
		NiAVObject*             GetMagicNode(const BSTSmartPointer<BipedAnim>& a_biped) const;
		ObjectRefHandle         GetOccupiedFurniture() const;
		float                   GetRegenDelay(ActorValue a_actorvalue) const;
		TESPackage*             GetRunningPackage() const;
		NiAVObject*             GetTorchNode(const BSTSmartPointer<BipedAnim>& a_biped) const;
		Actor*                  GetUserData() const;
		float                   GetVoiceRecoveryTime() const;
		NiAVObject*             GetWeaponNode(const BSTSmartPointer<BipedAnim>& a_biped) const;
		bool                    InHighProcess() const;
		bool                    InMiddleHighProcess() const;
		bool                    InMiddleLowProcess() const;
		bool                    InLowProcess() const;
		bool                    IsArrested() const;
		bool                    IsGhost() const;
		bool                    IsInCommandState() const;
		void                    SetActorRefraction(float a_refraction);
		void                    KnockExplosion(Actor* a_actor, const NiPoint3& a_location, float a_magnitude);
		void                    KnockParalyze(Actor* a_actor);
		bool                    PlayIdle(Actor* a_actor, TESIdleForm* a_idle, TESObjectREFR* a_target);
		void                    RandomlyPlaySpecialIdles(Actor* a_actor);
		void                    SetActorsDetectionEvent(Actor* a_actor, const NiPoint3& a_location, std::int32_t a_soundLevel, TESObjectREFR* a_ref);
		void                    SetArrested(bool a_arrested);
		void                    SetCachedHeight(float a_height);
		void                    SetRefraction(float a_refraction);
		void                    SetHeadtrackTarget(Actor* a_owner, NiPoint3& a_targetPosition);
		void                    Set3DUpdateFlag(RESET_3D_FLAGS a_flags);
		void                    SetRunOncePackage(TESPackage* a_package, Actor* a_actor);
		bool                    SetupSpecialIdle(Actor* a_actor, DEFAULT_OBJECT a_action, TESIdleForm* a_idle, bool a_arg5, bool a_arg6, TESObjectREFR* a_target);
		void                    StopCurrentIdle(Actor* a_actor, bool a_forceIdleStop);
		void                    Update3DModel(Actor* a_actor);
		void                    UpdateRegenDelay(ActorValue a_actorValue, float a_regenDelay);

		[[deprecated("Pass the owning actor")]] void ClearFurniture();

		void SetCurrentPackage(TESPackage* a_package, Actor* a_actor)
		{
			using func_t = void(AIProcess*, TESPackage*, Actor*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38189, 39149) };
			func(this, a_package, a_actor);
		}
		void SetHighUnk028(std::uint64_t a_value)
		{
			using func_t = void(AIProcess*, std::uint64_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38305, 39275) };
			func(this, a_value);
		}
		void StartFleeFrom(Actor* a_actor, TESObjectREFR* a_threat)
		{
			using func_t = void(AIProcess*, Actor*, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38376, 39360) };
			func(this, a_actor, a_threat);
		}
		ActorKnowledge* GetOrCreateActorKnowledge(Actor* a_owner, TESObjectREFR* a_target)
		{
			using func_t = ActorKnowledge*(AIProcess*, Actor*, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38505, 39515) };
			return func(this, a_owner, a_target);
		}
		void SetBleedoutRate(float a_rate)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38949, 40002) };
			func(this, a_rate);
		}
		void SetBleedoutParam2B0(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38951, 40004) };
			func(this, a_value);
		}
		void SetBleedoutParam2B8(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38953, 40006) };
			func(this, a_value);
		}
		void SetBleedoutAttacker(void* a_handle)
		{
			using func_t = void(AIProcess*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38954, 40007) };
			func(this, a_handle);
		}
		void* GetBleedoutAttacker(void* a_outHandle)
		{
			using func_t = void*(AIProcess*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38955, 40008) };
			return func(this, a_outHandle);
		}
		bool EnterCombat(Actor* a_actor, Actor* a_target, CombatGroup* a_group)
		{
			using func_t = bool(AIProcess*, Actor*, Actor*, CombatGroup*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(39012, 40079) };
			return func(this, a_actor, a_target, a_group);
		}
		void StartInterruptPackage(Actor* a_actor, TESPackage* a_package, TESObjectREFR* a_target)
		{
			using func_t = void(AIProcess*, Actor*, TESPackage*, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(39029, 40096) };
			func(this, a_actor, a_package, a_target);
		}

		void VisitKnowledgeEntries(void* a_visitor)
		{
			using func_t = void(AIProcess*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(27995, 27292) };
			func(this, a_visitor);
		}
		bool GetMiddleHighFlag32D()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38887, 39928) };
			return func(this);
		}
		void SetMiddleHighFlag32D(bool a_value)
		{
			using func_t = void(AIProcess*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38888, 39929) };
			func(this, a_value);
		}

		bool ApplyNewPackage(Character* a_actor)
		{
			using func_t = bool(AIProcess*, Character*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38247, 39207) };
			return func(this, a_actor);
		}

		void SetLastActivatedDoor(std::uint32_t* a_handle, bool a_flag)
		{
			using func_t = void(AIProcess*, std::uint32_t*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38412, 39407) };
			func(this, a_handle, a_flag);
		}

		void ProcessFollowHigh(Actor* a_actor, bool a_advanceProcedure, std::int32_t a_moveMode, bool a_pursue)
		{
			using func_t = void(AIProcess*, Actor*, bool, std::int32_t, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38608, 39639) };
			func(this, a_actor, a_advanceProcedure, a_moveMode, a_pursue);
		}

		void ProcessFollow(Actor* a_actor, bool a_advanceProcedure, std::int32_t a_moveMode, bool a_pursue)
		{
			using func_t = void(AIProcess*, Actor*, bool, std::int32_t, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38199, 39159) };
			func(this, a_actor, a_advanceProcedure, a_moveMode, a_pursue);
		}

		bool RequestFollowPathing(Character* a_follower, Character* a_leader, BSPathingLocation* a_goal, float a_followDistance, bool* a_outBeyondHysteresis, std::uint8_t* a_outGoalClientData, float* a_outFollowerPathLength, float* a_outLeaderPathLength)
		{
			using func_t = bool(AIProcess*, Character*, Character*, BSPathingLocation*, float, bool*, std::uint8_t*, float*, float*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38529, 39539) };
			return func(this, a_follower, a_leader, a_goal, a_followDistance, a_outBeyondHysteresis, a_outGoalClientData, a_outFollowerPathLength, a_outLeaderPathLength);
		}

		// members
		MiddleLowProcessData*                       middleLow;                      // 000
		MiddleHighProcessData*                      middleHigh;                     // 008
		HighProcessData*                            high;                           // 010
		ActorPackage                                currentPackage;                 // 018
		float                                       hourLastProcessed;              // 048
		float                                       dateLastProcessed;              // 04C
		CachedValues*                               cachedValues;                   // 050
		std::int32_t                                numberItemsActivate;            // 058
		std::uint32_t                               pad05C;                         // 05C
		BSSimpleList<ObjectstoAcquire*>             objects;                        // 060
		BSSimpleList<TESObjectREFR*>                genericLocations;               // 070
		ObjectstoAcquire*                           acquireObject;                  // 080
		ObjectstoAcquire*                           savedAcquireObject;             // 088
		float                                       essentialDownTimer;             // 090
		float                                       deathTime;                      // 094
		float                                       trackedDamage;                  // 098
		std::uint32_t                               pad09C;                         // 09C
		BSTArray<EquippedObject>                    equippedForms;                  // 0A0
		BSTHeapObjectArena<ModelDBHandle, 16>       unk0B8;                         // 0B8
		TESForm*                                    equippedObjects[Hand::kTotal];  // 0F0
		std::uint64_t                               unk100;                         // 100
		std::uint64_t                               unk108;                         // 108
		RefHandle                                   followTarget;                   // 110
		RefHandle                                   target;                         // 114
		RefHandle                                   packageObject;                  // 118
		RefHandle                                   secondPackageObject;            // 11C
		std::uint64_t                               unk120;                         // 120
		std::uint64_t                               unk128;                         // 128
		std::uint32_t                               unk130;                         // 130
		std::uint16_t                               unk134;                         // 134
		REX::EnumSet<LowProcessFlags, std::uint8_t> lowProcessFlags;                // 136
		REX::EnumSet<PROCESS_TYPE, std::uint8_t>    processLevel;                   // 137
		bool                                        skippedTimeStampForPathing;     // 138
		bool                                        ignoringCombat;                 // 139
		bool                                        endAlarmOnActor;                // 13A
		bool                                        escortingPlayer;                // 13B
		std::uint32_t                               pad13C;                         // 13C

	protected:
		void Update3DModel_Impl(Actor* a_actor);
	};
	static_assert(sizeof(AIProcess) == 0x140);
}

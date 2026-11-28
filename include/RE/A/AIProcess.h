#pragma once

#include "RE/A/ActorPackage.h"
#include "RE/A/ActorValues.h"
#include "RE/B/BGSDefaultObjectManager.h"
#include "RE/B/BSResourceHandle.h"
#include "RE/B/BSSimpleList.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTObjectArena.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/M/MagicSystem.h"
#include "RE/M/Movement.h"
#include "RE/P/ProcessType.h"

namespace RE
{
	class TESTopic;
	class TESObjectWEAP;
	class TESObjectREFR;
	class BSLightingShaderProperty;
	class BSBound;
	class ActorPackageData;
	class TESTopicInfo;
	class TESIdleForm;
	class NiNode;
	class MagicItem;
	struct Crime;
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
		void ClearSpeech(Actor* a_actor)
		{
			using func_t = void(AIProcess*, Actor*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38390, 39376) };
			func(this, a_actor);
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

		bool GetCurrentMaxSpeeds(Movement::MaxSpeeds* a_out)
		{
			using func_t = bool(AIProcess*, Movement::MaxSpeeds*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38544, 39555) };
			return func(this, a_out);
		}

		void SetVoiceSubtitle(const BSFixedString& a_subtitle)
		{
			using func_t = void(AIProcess*, const BSFixedString&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38341, 39320) };
			func(this, a_subtitle);
		}

		void ClearConversationTarget()
		{
			using func_t = void(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38303, 39273) };
			func(this);
		}

		void ClearActorsGeneratedDetectionEvent()
		{
			using func_t = void(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38312, 39287) };
			func(this);
		}

		float GetAwarePlayerTimer()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38326, 39301) };
			return func(this);
		}

		void ModAwarePlayerTimer(float a_delta)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38327, 39302) };
			func(this, a_delta);
		}

		void SetAvoidWaitTimer(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38344, 39326) };
			func(this, a_value);
		}

		float GetHeadTrackTargetTimer()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38346, 39328) };
			return func(this);
		}

		void SetHeadTrackTargetTimer(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38347, 39329) };
			func(this, a_value);
		}

		float GetActivationHeight()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38348, 39330) };
			return func(this);
		}

		void SetActivationHeight(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38349, 39331) };
			func(this, a_value);
		}

		void ClearDeathDialogue()
		{
			using func_t = void(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38353, 39336) };
			func(this);
		}

		std::uint32_t GetEmotionType()
		{
			using func_t = std::uint32_t(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38366, 39349) };
			return func(this);
		}

		void SetBreathTimer(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38368, 39351) };
			func(this, a_value);
		}

		float GetBreathTimer()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38369, 39352) };
			return func(this);
		}

		void SetSoundDelay(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38372, 39356) };
			func(this, a_value);
		}

		void SetIdleTimer(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38374, 39358) };
			func(this, a_value);
		}

		void SetPackageEvaluateTimer(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38380, 39364) };
			func(this, a_value);
		}

		bool GetPlantedExplosive()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38393, 39379) };
			return func(this);
		}

		bool GetAggroRadiusStarted()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38394, 39380) };
			return func(this);
		}

		int GetAnimAction()
		{
			using func_t = int(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38398, 39385) };
			return func(this);
		}

		float GetGreetingTimer()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38416, 39412) };
			return func(this);
		}

		void SetGreetingTimer(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38417, 39413) };
			func(this, a_value);
		}

		TESTopicInfo* GetLastGreeting()
		{
			using func_t = TESTopicInfo*(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38418, 39414) };
			return func(this);
		}

		void SetLastGreeting(TESTopicInfo* a_info)
		{
			using func_t = void(AIProcess*, TESTopicInfo*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38419, 39415) };
			func(this, a_info);
		}

		float GetExclusiveTimer()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38420, 39416) };
			return func(this);
		}

		void SetExclusiveGreetingTimer(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38421, 39417) };
			func(this, a_value);
		}

		void SetDyingTimer(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38422, 39419) };
			func(this, a_value);
		}

		void SetPCapVoiceFailsafeTimer(std::uint32_t a_value)
		{
			using func_t = void(AIProcess*, std::uint32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38427, 39424) };
			func(this, a_value);
		}

		float GetSceneHeadTrackTimer()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38439, 39437) };
			return func(this);
		}

		void SetSceneHeadTrackTimer(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38440, 39438) };
			func(this, a_value);
		}

		std::uint32_t GetNumberGuardsPursuing()
		{
			using func_t = std::uint32_t(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38441, 39439) };
			return func(this);
		}

		void ModNumberGuardsPursuing(int a_delta)
		{
			using func_t = void(AIProcess*, int);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38442, 39440) };
			func(this, a_delta);
		}

		void SetNumberGuardsPursuing(std::uint32_t a_value)
		{
			using func_t = void(AIProcess*, std::uint32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38443, 39441) };
			func(this, a_value);
		}

		float GetFadeAlpha()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38460, 39458) };
			return func(this);
		}

		void SetHeadTrackTargetOffsetTimer(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38475, 39473) };
			func(this, a_value);
		}

		void UpdateDetectionModifierTimer()
		{
			using func_t = void(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38477, 39475) };
			func(this);
		}

		float GetDeathForce()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38488, 39497) };
			return func(this);
		}

		void SetDeathForce(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38489, 39498) };
			func(this, a_value);
		}

		void ResetDeathForce()
		{
			using func_t = void(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38490, 39499) };
			func(this);
		}

		TESIdleForm* GetCurrentProcessIdle()
		{
			using func_t = TESIdleForm*(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38496, 39505) };
			return func(this);
		}

		void SetCurrentProcessIdle(TESIdleForm* a_idle)
		{
			using func_t = void(AIProcess*, TESIdleForm*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38497, 39506) };
			func(this, a_idle);
		}

		float GetLightLevel()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38499, 39509) };
			return func(this);
		}

		void SetLightLevel(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38500, 39510) };
			func(this, a_value);
		}

		void SetPathLookAtTarget(const ObjectRefHandle& a_handle)
		{
			using func_t = void(AIProcess*, const ObjectRefHandle&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38502, 39512) };
			func(this, a_handle);
		}

		void ClearPathLookAtTarget(const ObjectRefHandle& a_handle)
		{
			using func_t = void(AIProcess*, const ObjectRefHandle&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38503, 39513) };
			func(this, a_handle);
		}

		float GetVoiceTimeElapsed()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38520, 39530) };
			return func(this);
		}

		void SetVoiceTimeElapsed(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38521, 39531) };
			func(this, a_value);
		}

		void SetLastBumpDirection(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38541, 39552) };
			func(this, a_value);
		}

		float GetLastBumpDirection()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38542, 39553) };
			return func(this);
		}

		void SetCrimeToReactTo(Crime* a_crime)
		{
			using func_t = void(AIProcess*, Crime*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38546, 39557) };
			func(this, a_crime);
		}

		Crime* GetCrimeToReactTo()
		{
			using func_t = Crime*(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38547, 39558) };
			return func(this);
		}

		bool GetAnimationDrivenMotion()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38548, 39559) };
			return func(this);
		}

		bool GetAllowRotation()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38551, 39563) };
			return func(this);
		}

		float GetAbsorbTimer()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38553, 39565) };
			return func(this);
		}

		void SetAbsorbTimer(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38554, 39566) };
			func(this, a_value);
		}

		MagicItem* GetReanimationSpell()
		{
			using func_t = MagicItem*(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38558, 39576) };
			return func(this);
		}

		float GetCachedActorHeight()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38567, 39587) };
			return func(this);
		}

		void ResetBumpTimer()
		{
			using func_t = void(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38575, 39599) };
			func(this);
		}

		void SetVoiceTimer(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38577, 39602) };
			func(this, a_value);
		}

		float GetVoiceTimer()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38578, 39603) };
			return func(this);
		}

		void SetMaxAlpha(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38584, 39611) };
			func(this, a_value);
		}

		float GetMaxAlpha()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38585, 39612) };
			return func(this);
		}

		bool GetApproachingAutoTeleportDoor()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38594, 39623) };
			return func(this);
		}

		MagicItem* GetCurrentPackageSpell()
		{
			using func_t = MagicItem*(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38769, 39793) };
			return func(this);
		}

		void SetCurrentPackageSpell(MagicItem* a_spell)
		{
			using func_t = void(AIProcess*, MagicItem*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38770, 39794) };
			func(this, a_spell);
		}

		void ClearFaceAnimationData()
		{
			using func_t = void(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38771, 39795) };
			func(this);
		}

		void SetPickPocketed(bool a_value)
		{
			using func_t = void(AIProcess*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38777, 39802) };
			func(this, a_value);
		}

		InventoryEntryData* GetLeftHand()
		{
			using func_t = InventoryEntryData*(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38784, 39809) };
			return func(this);
		}

		InventoryEntryData* GetRightHand()
		{
			using func_t = InventoryEntryData*(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38785, 39810) };
			return func(this);
		}

		bool HasItemsToEquipUnequip()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38790, 39820) };
			return func(this);
		}

		NiNode* GetWeaponBone()
		{
			using func_t = NiNode*(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38795, 39825) };
			return func(this);
		}

		void SetWeaponBone(NiNode* a_node)
		{
			using func_t = void(AIProcess*, NiNode*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38796, 39826) };
			func(this, a_node);
		}

		TESIdleForm* GetLastIdlePlayed()
		{
			using func_t = TESIdleForm*(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38839, 39869) };
			return func(this);
		}

		float GetCurrentMovementSpeed()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38840, 39872) };
			return func(this);
		}

		void SetCurrentMovementSpeed(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38841, 39873) };
			func(this, a_value);
		}

		void SetIsFleeing(bool a_value)
		{
			using func_t = void(AIProcess*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38855, 39892) };
			func(this, a_value);
		}

		void ClearUpdate3DModelFlags()
		{
			using func_t = void(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38868, 39909) };
			func(this);
		}

		bool HasUpdate3DModelFlag(std::uint8_t a_flag)
		{
			using func_t = bool(AIProcess*, std::uint8_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38869, 39910) };
			return func(this, a_flag);
		}

		std::uint8_t GetUpdate3DModelFlags()
		{
			using func_t = std::uint8_t(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38870, 39911) };
			return func(this);
		}

		void SetTorchEvaluationTimer(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38894, 39940) };
			func(this, a_value);
		}

		float GetAlphaMult()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38913, 39960) };
			return func(this);
		}

		float GetScriptRefractPower()
		{
			using func_t = float(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38915, 39962) };
			return func(this);
		}

		void SetForceNextUpdate(bool a_value)
		{
			using func_t = void(AIProcess*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38921, 39968) };
			func(this, a_value);
		}

		bool GetForceNextUpdate()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38922, 39969) };
			return func(this);
		}

		void SetSummonedCreature(bool a_value)
		{
			using func_t = void(AIProcess*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38923, 39970) };
			func(this, a_value);
		}

		bool GetSummonedCreature()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38924, 39971) };
			return func(this);
		}

		NiAVObject* GetTorsoNode()
		{
			using func_t = NiAVObject*(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38929, 39976) };
			return func(this);
		}

		bool GetAlwaysHit()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38942, 39994) };
			return func(this);
		}

		void SetAlwaysHit(bool a_value)
		{
			using func_t = void(AIProcess*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38943, 39995) };
			func(this, a_value);
		}

		bool GetDoNoDamage()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38944, 39996) };
			return func(this);
		}

		void SetDoNoDamage(bool a_value)
		{
			using func_t = void(AIProcess*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38945, 39997) };
			func(this, a_value);
		}

		bool GetPreventCombat()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38946, 39998) };
			return func(this);
		}

		void SetPreventCombat(bool a_value)
		{
			using func_t = void(AIProcess*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38947, 39999) };
			func(this, a_value);
		}

		bool GetKillQueued()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38958, 40011) };
			return func(this);
		}

		void SetKillQueued(bool a_value)
		{
			using func_t = void(AIProcess*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38959, 40012) };
			func(this, a_value);
		}

		void SetWardState(MagicSystem::WardState a_state)
		{
			using func_t = void(AIProcess*, MagicSystem::WardState);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38960, 40013) };
			func(this, a_state);
		}

		void SetSoulTrapped()
		{
			using func_t = void(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38971, 40031) };
			func(this);
		}

		bool GetSoulTrapped()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38972, 40032) };
			return func(this);
		}

		void ResetHeadHeightOffset()
		{
			using func_t = void(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38978, 40041) };
			func(this);
		}

		NiAVObject* GetFaceTargetSourceNode()
		{
			using func_t = NiAVObject*(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38983, 40046) };
			return func(this);
		}

		void SetFaceTargetSourceNode(NiAVObject* a_node)
		{
			using func_t = void(AIProcess*, NiAVObject*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38984, 40047) };
			func(this, a_node);
		}

		void SayDeathDialogue(Actor* a_actor)
		{
			using func_t = void(AIProcess*, Actor*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38352, 39335) };
			func(this, a_actor);
		}

		void QueueDialogue(Actor* a_target, int a_type, int a_subtype, TESTopic* a_topic)
		{
			using func_t = void(AIProcess*, Actor*, int, int, TESTopic*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38354, 39337) };
			func(this, a_target, a_type, a_subtype, a_topic);
		}

		bool HasQueuedGreetings()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38357, 39340) };
			return func(this);
		}

		void StopSoundHandle(int a_index)
		{
			using func_t = void(AIProcess*, int);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38408, 39401) };
			func(this, a_index);
		}

		void SetPackDuration(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38428, 39425) };
			func(this, a_value);
		}

		void FinishFadeIn(TESObjectREFR* a_ref)
		{
			using func_t = void(AIProcess*, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38461, 39459) };
			func(this, a_ref);
		}

		void SetDefaultHeadtrackTarget(TESObjectREFR* a_target)
		{
			using func_t = void(AIProcess*, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38463, 39461) };
			func(this, a_target);
		}

		void SetActionHeadtrackTarget(TESObjectREFR* a_target)
		{
			using func_t = void(AIProcess*, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38464, 39462) };
			func(this, a_target);
		}

		void SetScriptHeadtrackTarget(TESObjectREFR* a_target)
		{
			using func_t = void(AIProcess*, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38465, 39463) };
			func(this, a_target);
		}

		void SetCombatHeadtrackTarget(TESObjectREFR* a_target)
		{
			using func_t = void(AIProcess*, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38466, 39464) };
			func(this, a_target);
		}

		void SetDialogueHeadtrackTarget(TESObjectREFR* a_target)
		{
			using func_t = void(AIProcess*, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38467, 39465) };
			func(this, a_target);
		}

		void SetProcedureHeadtrackTarget(TESObjectREFR* a_target)
		{
			using func_t = void(AIProcess*, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38468, 39466) };
			func(this, a_target);
		}

		void ClearScriptHeadtrackTarget(bool a_keepAsDefault)
		{
			using func_t = void(AIProcess*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38471, 39469) };
			func(this, a_keepAsDefault);
		}

		void ClearDialogueHeadtrackTarget(bool a_keepAsDefault)
		{
			using func_t = void(AIProcess*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38473, 39471) };
			func(this, a_keepAsDefault);
		}

		void ClearProcedureHeadtrackTarget(bool a_keepAsDefault)
		{
			using func_t = void(AIProcess*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38474, 39472) };
			func(this, a_keepAsDefault);
		}

		int GetReplacedItemType(std::uint32_t a_hand)
		{
			using func_t = int(AIProcess*, std::uint32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38510, 39520) };
			return func(this, a_hand);
		}

		void SetReplacedItemType(std::uint32_t a_hand, std::uint16_t a_type)
		{
			using func_t = void(AIProcess*, std::uint32_t, std::uint16_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38511, 39521) };
			func(this, a_hand, a_type);
		}

		void ClearReplacedItemTypes()
		{
			using func_t = void(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38512, 39522) };
			func(this);
		}

		void ClearAttackData()
		{
			using func_t = void(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38532, 39542) };
			func(this);
		}

		bool HasNoQueuedGreetings()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38536, 39547) };
			return func(this);
		}

		void ClearReanimationData()
		{
			using func_t = void(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38556, 39574) };
			func(this);
		}

		void SetAnimationAngleModZ(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38571, 39592) };
			func(this, a_value);
		}

		void SetAnimationAngleModX(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38572, 39594) };
			func(this, a_value);
		}

		bool GetIdleDoneOnce()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38772, 39796) };
			return func(this);
		}

		InventoryEntryData* GetEquippedLightEntry(bool a_leftHand)
		{
			using func_t = InventoryEntryData*(AIProcess*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38783, 39808) };
			return func(this, a_leftHand);
		}

		void SetRunOnceProcedureIndex(int a_index)
		{
			using func_t = void(AIProcess*, int);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38821, 39851) };
			func(this, a_index);
		}

		int GetRunOnceProcedureIndex()
		{
			using func_t = int(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38822, 39852) };
			return func(this);
		}

		void ModRunOnceProcedureIndex(int a_delta)
		{
			using func_t = void(AIProcess*, int);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38823, 39853) };
			func(this, a_delta);
		}

		ActorPackageData* GetRunOncePackageData()
		{
			using func_t = ActorPackageData*(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38824, 39854) };
			return func(this);
		}

		void SetRotationZ(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38845, 39878) };
			func(this, a_value);
		}

		void SetRotationX(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38846, 39880) };
			func(this, a_value);
		}

		void SetRotationY(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38847, 39882) };
			func(this, a_value);
		}

		void SetRotationSpeedZ(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38848, 39884) };
			func(this, a_value);
		}

		void SetRotationSpeedX(float a_value)
		{
			using func_t = void(AIProcess*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38849, 39886) };
			func(this, a_value);
		}

		bool GetExitingInstant()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38885, 39926) };
			return func(this);
		}

		void SetExitingInstant(bool a_value)
		{
			using func_t = void(AIProcess*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38886, 39927) };
			func(this, a_value);
		}

		void SetLightingProperty(BSLightingShaderProperty* a_property)
		{
			using func_t = void(AIProcess*, BSLightingShaderProperty*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38899, 39945) };
			func(this, a_property);
		}

		void SetBoundWeapon(TESObjectWEAP* a_weapon)
		{
			using func_t = void(AIProcess*, TESObjectWEAP*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38907, 39953) };
			func(this, a_weapon);
		}

		TESObjectWEAP* GetBoundWeapon()
		{
			using func_t = TESObjectWEAP*(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38908, 39954) };
			return func(this);
		}

		void SetOccupiedFurniture(Actor* a_actor, const ObjectRefHandle& a_handle)
		{
			using func_t = void(AIProcess*, Actor*, const ObjectRefHandle&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38909, 39955) };
			func(this, a_actor, a_handle);
		}

		BSBound* GetBound()
		{
			using func_t = BSBound*(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38919, 39966) };
			return func(this);
		}

		void SetBound(BSBound* a_bound)
		{
			using func_t = void(AIProcess*, BSBound*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38920, 39967) };
			func(this, a_bound);
		}

		bool GetBleedingOut()
		{
			using func_t = bool(AIProcess*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38956, 40009) };
			return func(this);
		}

		void SetBleedingOut(bool a_value)
		{
			using func_t = void(AIProcess*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38957, 40010) };
			func(this, a_value);
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

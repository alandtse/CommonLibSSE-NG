#pragma once

#include "RE/A/Actor.h"

namespace RE
{
	class MovementMessage;
	class BGSAIWorldLocation;
	class BSPathingLocation;
	class PackageTarget;
	class PathingRequestClosePoint;
	class DetectionListener;

	class Character : public Actor
	{
	public:
		inline static constexpr auto RTTI = RTTI_Character;
		inline static constexpr auto VTABLE = VTABLE_Character;
		inline static constexpr auto FORMTYPE = FormType::ActorCharacter;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kStartsDead = 1 << 9,
				kPersistent = 1 << 10,
				kInitiallyDisabled = 1 << 11,
				kIgnored = 1 << 12,
				kNoAIAcquire = 1 << 25,
				kDontHavokSettle = 1 << 29
			};
		};

		~Character() override;  // 000

		// override (Actor)
		void                                  SaveGame(BGSSaveFormBuffer* a_buf) override;                   // 00E - { Actor::SaveBuffer(a_buf); }
		void                                  LoadGame(BGSLoadFormBuffer* a_buf) override;                   // 00F - { Actor::LoadBuffer(a_buf); }
		void                                  InitLoadGame(BGSLoadFormBuffer* a_buf) override;               // 010 - { Actor::InitLoadGame(a_arg1); }
		void                                  FinishLoadGame(BGSLoadFormBuffer* a_buf) override;             // 011 - { Actor::FinishLoadGame(a_arg1); }
		void                                  Revert(BGSLoadFormBuffer* a_buf) override;                     // 012 - { return; }
		void                                  Predestroy(void) override;                                     // 03B
		[[nodiscard]] bool                    IsChild() const override;                                      // 05E - { return race ? (race->data.flags & Flag::kChild) != Flag::kNone : false; }
		[[nodiscard]] BSFaceGenNiNode*        GetFaceNodeSkinned() override;                                 // 061
		[[nodiscard]] BSFaceGenAnimationData* GetFaceGenAnimationData() override;                            // 063
		void                                  SetBiped(const BSTSmartPointer<BipedAnim>& a_biped) override;  // 081
#ifndef SKYRIM_CROSS_VR
		void         InitiateVampireFeedPackage(Actor* a_arg1, TESObjectREFR* a_arg2) override;  // 0C0
		void         Unk_C4(void) override;                                                      // 0C4 - { unk272 = a_arg1; }
		void         Unk_C5(void) override;                                                      // 0C5 - { return unk272; }
		void         Unk_C6(void) override;                                                      // 0C6 - { return 1; }
		void         OnArmorActorValueChanged() override;                                        // 0CA
		bool         InitiateTresPassPackage(TrespassPackage* a_trespassPackage) override;       // 0D7
		void         SetSize(float a_size) override;                                             // 0D9
		float        CalcArmorRating() override;                                                 // 0E6
		float        GetArmorBaseFactorSum() override;                                           // 0E7
		std::int32_t CalcUnarmedDamage() override;                                               // 0E8
		void         PrecacheData(void) override;                                                // 120
#endif

		// add
		SKYRIM_REL_VR_VIRTUAL void Unk_128(void);  // 128
		SKYRIM_REL_VR_VIRTUAL void Unk_129(void);  // 129 - { return 1; }

		void SetAnimationDrivenMotion(bool a_active);

		float GetSpeedMultScale()
		{
			using func_t = float(Character*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36355, 37346) };
			return func(this);
		}
		bool RefreshKnowledgeOf(TESObjectREFR* a_target, DetectionListener* a_listener, int a_level)
		{
			using func_t = bool(Character*, TESObjectREFR*, DetectionListener*, int);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36743, 37759) };
			return func(this, a_target, a_listener, a_level);
		}

		std::int32_t GetInitialDataType(std::uint32_t a_changeFlags)
		{
			using func_t = std::int32_t(Character*, std::uint32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(34799, 35708) };
			return func(this, a_changeFlags);
		}
		void ObserveCorpse(TESObjectREFR* a_corpse)
		{
			using func_t = void(Character*, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36423, 37417) };
			func(this, a_corpse);
		}
		void MoveToPackageLocation(bool a_useSavedPackage)
		{
			using func_t = void(Character*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36472, 37471) };
			func(this, a_useSavedPackage);
		}
		bool UpdateBleedoutOrKill(TESObjectREFR* a_attacker, float a_health)
		{
			using func_t = bool(Character*, TESObjectREFR*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(37677, 38631) };
			return func(this, a_attacker, a_health);
		}

		void ReleaseOccupiedFurniture()
		{
			using func_t = void(Character*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36341, 37331) };
			func(this);
		}
		void ResumeOccupiedFurniture()
		{
			using func_t = void(Character*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36342, 37332) };
			func(this);
		}
		void StartGuardWarnPackage(void* a_targetInfo, BGSAIWorldLocation* a_location, std::uint32_t* a_handle, float a_radiusSlot2, float a_locationRadius, float a_radiusSlot3, PackageTarget* a_packageTarget)
		{
			using func_t = void(Character*, void*, void*, std::uint32_t*, float, float, float, PackageTarget*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36412, 37406) };
			func(this, a_targetInfo, a_location, a_handle, a_radiusSlot2, a_locationRadius, a_radiusSlot3, a_packageTarget);
		}
		void MoveToPackageLocationEx(bool a_useSavedPackage, PathingRequestClosePoint** a_outRequest)
		{
			using func_t = void(Character*, bool, PathingRequestClosePoint**);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36473, 37472) };
			func(this, a_useSavedPackage, a_outRequest);
		}
		void UpdatePackageStartLocationIfCurrentLoc()
		{
			using func_t = void(Character*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36739, 37753) };
			func(this);
		}
		void RefreshPackageStartLocation()
		{
			using func_t = void(Character*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36740, 37754) };
			func(this);
		}
		// True when the target's detection level against this character is above zero.
		bool IsTargetDetected(TESObjectREFR* a_target)
		{
			using func_t = bool(Character*, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36750, 37766) };
			return func(this, a_target);
		}
		bool IsTalkingToPC()
		{
			using func_t = bool(Character*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36219, 37199) };
			return func(this);
		}
		bool CastShoutWord(TESShout* a_shout, std::uint32_t a_wordIndex, TESObjectREFR* a_target)
		{
			using func_t = bool(Character*, TESShout*, std::uint32_t, TESObjectREFR*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(37850, 38804) };
			return func(this, a_shout, a_wordIndex, a_target);
		}
		float GetCombatHoverDuration()
		{
			using func_t = float(Character*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(49734, 50661) };
			return func(this);
		}
		float GetCombatGroundAttackDuration()
		{
			using func_t = float(Character*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(49736, 50663) };
			return func(this);
		}
		float GetCombatPerchAttackDuration()
		{
			using func_t = float(Character*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(49738, 50665) };
			return func(this);
		}

		void AppendSpeakerAvoidNodeToRequest(void* a_request)
		{
			using func_t = void(Character*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36785, 37801) };
			func(this, a_request);
		}
		void SubmitPathRequest(void* a_request, void* a_location, float a_unkFloat, void* a_unk)
		{
			using func_t = void(Character*, void*, void*, float, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(40612, 41642) };
			func(this, a_request, a_location, a_unkFloat, a_unk);
		}

		bool TurnToFace(NiPoint3* a_target, float a_tolerance)
		{
			using func_t = bool(Character*, NiPoint3*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36795, 37811) };
			return func(this, a_target, a_tolerance);
		}

		float GetLookAtHeadingMaxAngle()
		{
			using func_t = float(Character*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36760, 37776) };
			return func(this);
		}

		void PathToPathingLocation(BSPathingLocation* a_location, float a_distance, void* a_avoid)
		{
			using func_t = void(Character*, BSPathingLocation*, float, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36784, 37800) };
			func(this, a_location, a_distance, a_avoid);
		}
		void PathToLocation(NiPoint3* a_point, TESObjectCELL* a_cell, TESWorldSpace* a_worldSpace, float a_distance, void* a_avoid)
		{
			using func_t = void(Character*, NiPoint3*, TESObjectCELL*, TESWorldSpace*, float, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36786, 37802) };
			func(this, a_point, a_cell, a_worldSpace, a_distance, a_avoid);
		}
		bool PathToFollowPoint(NiPoint3* a_point, float a_arg2, void* a_arg3)
		{
			using func_t = bool(Character*, NiPoint3*, float, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36797, 37813) };
			return func(this, a_point, a_arg2, a_arg3);
		}

		void MoveFollowersToPosition(NiPoint3* a_pos, float a_rotZ, float a_rotX, TESObjectCELL* a_cell, TESWorldSpace* a_worldSpace, bool a_atDoor, bool a_ignoreSleep)
		{
			using func_t = void(Character*, NiPoint3*, float, float, TESObjectCELL*, TESWorldSpace*, bool, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36439, 37434) };
			func(this, a_pos, a_rotZ, a_rotX, a_cell, a_worldSpace, a_atDoor, a_ignoreSleep);
		}
		bool CollectFollowers(void* a_out)
		{
			using func_t = bool(Character*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36440, 37435) };
			return func(this, a_out);
		}
		float GetFollowersSpacing()
		{
			using func_t = float(Character*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36441, 37436) };
			return func(this);
		}
		float GetFollowersTotalSpacing(void* a_followers, float a_spacing)
		{
			using func_t = float(Character*, void*, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36442, 37437) };
			return func(this, a_followers, a_spacing);
		}
		void TeleportToPackageLocation(NiPoint3* a_pos, TESObjectCELL* a_cell, TESWorldSpace* a_worldSpace)
		{
			using func_t = void(Character*, NiPoint3*, TESObjectCELL*, TESWorldSpace*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36474, 37473) };
			func(this, a_pos, a_cell, a_worldSpace);
		}
		float CalculateRadius()
		{
			using func_t = float(Character*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36841, 37865) };
			return func(this);
		}

		void ActivatePathingDoor(void* a_doorInfo)
		{
			using func_t = void(Character*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36854, 37878) };
			func(this, a_doorInfo);
		}

		void RefreshCachedValues()
		{
			using func_t = void(Character*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36850, 37874) };
			func(this);
		}

		bool DispatchMovementMessage(MovementMessage* a_message)
		{
			using func_t = bool(Character*, MovementMessage*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(36868, 37892) };
			return func(this, a_message);
		}

		void GetAnticipatedLocation(float a_time, NiPoint3* a_outLocation)
		{
			using func_t = void(Character*, float, NiPoint3*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(46045, 47309) };
			func(this, a_time, a_outLocation);
		}
	};
	STATIC_ASSERT_SIZE(Character, 0x2B0, 0x2B8, 0x2B0, 0xC0, 0xC8);
}

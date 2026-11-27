#pragma once

#include "RE/B/BSPathing.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/C/CombatPathingGoalPolicy.h"
#include "RE/C/CombatPathingSearchPolicy.h"

namespace RE
{
	class CombatPathingRequestAdapter;
	class CombatPathingRequestStandard;
	class CombatPathingRequestMultiGoal;
	class PathingRequestFly;
	class PathingRequestFlyAction;
	class PathingRequestFlyHover;
	class PathingRequestFlyLand;
	class PathingRequestFlyOrbit;

	template <class Goal, class Search>
	class CombatPathingRequestGeneric;

	template <class T>
	class CombatPathRequest
	{
	public:
		// members
		BSTSmartPointer<T> request;  // 00
	};

	template <class T>
	class CombatPathRequestAdapter : public CombatPathRequest<CombatPathingRequestAdapter>
	{
	public:
	};

	class CombatPathRequestStandard : public CombatPathRequest<CombatPathingRequestStandard>
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathRequestStandard;

		// members
		std::uint64_t unk08;  // 08
	};
	static_assert(sizeof(CombatPathRequestStandard) == 0x10);

	class CombatPathRequestFlight : public CombatPathRequestAdapter<PathingRequestFly>
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathRequestFlight;

		// members
		std::uint64_t unk08;  // 08
	};
	static_assert(sizeof(CombatPathRequestFlight) == 0x10);

	class CombatPathRequestStraightPath : public CombatPathRequest<CombatPathingRequestStandard>
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathRequestStraightPath;

		// members
		std::uint64_t unk08;  // 08
	};
	static_assert(sizeof(CombatPathRequestStraightPath) == 0x10);

	class CombatPathRequestRotatePath : public CombatPathRequestStraightPath
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathRequestRotatePath;
	};
	static_assert(sizeof(CombatPathRequestRotatePath) == 0x10);

	class CombatPathRequestMultiGoal : public CombatPathRequest<CombatPathingRequestMultiGoal>
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathRequestMultiGoal;

		// members
		std::uint64_t unk08;  // 08
	};
	static_assert(sizeof(CombatPathRequestMultiGoal) == 0x10);

	class CombatPathRequestFlyingAttack : public CombatPathRequestAdapter<PathingRequestFlyAction>
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathRequestFlyingAttack;

		// members
		ObjectRefHandle target;  // 08
	};
	static_assert(sizeof(CombatPathRequestFlyingAttack) == 0x10);

	class CombatPathRequestHover : public CombatPathRequestAdapter<PathingRequestFlyHover>
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathRequestHover;

		// members
		BSTArray<BSPathingGoal> goals;  // 08
	};
	static_assert(sizeof(CombatPathRequestHover) == 0x20);

	class CombatPathRequestOrbit : public CombatPathRequestAdapter<PathingRequestFlyOrbit>
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathRequestOrbit;

		// members
		float     radius;      // 08
		std::byte pad0C[0xC];  // 0C
	};
	static_assert(sizeof(CombatPathRequestOrbit) == 0x18);

	class CombatPathRequestLanding : public CombatPathRequestAdapter<PathingRequestFlyLand>
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatPathRequestLanding;

		// members
		ObjectRefHandle landTarget;  // 08
		float           unk0C;       // 0C
		std::uint32_t   unk10;       // 10
		float           unk14;       // 14
	};
	static_assert(sizeof(CombatPathRequestLanding) == 0x18);

	template <class Goal, class Search>
	class CombatPathRequestGeneric : public CombatPathRequest<CombatPathingRequestGeneric<Goal, Search>>
	{
	public:
		// members
		Goal   goalPolicy;    // 08
		Search searchPolicy;  // 08 + sizeof(Goal)
	};

	static_assert(sizeof(CombatPathRequestGeneric<CombatPathingGoalPolicyExitWater, CombatPathingSearchPolicyStandard>) == 0x30);
	static_assert(sizeof(CombatPathRequestGeneric<CombatPathingGoalPolicyFindAttackLocation, CombatPathingSearchPolicyStandard>) == 0x60);
	static_assert(sizeof(CombatPathRequestGeneric<CombatPathingGoalPolicyFindCover, CombatPathingSearchPolicyStandard>) == 0x20);
	static_assert(sizeof(CombatPathRequestGeneric<CombatPathingGoalPolicyFindHideCover, CombatPathingSearchPolicyStandard>) == 0x20);
	static_assert(sizeof(CombatPathRequestGeneric<CombatPathingGoalPolicyFindTargetLocation, CombatPathingSearchPolicyStandard>) == 0x48);
	static_assert(sizeof(CombatPathRequestGeneric<CombatPathingGoalPolicyFlankDistant, CombatPathingSearchPolicyStandard>) == 0x38);
	static_assert(sizeof(CombatPathRequestGeneric<CombatPathingGoalPolicyFlank, CombatPathingSearchPolicyFlank>) == 0x98);
	static_assert(sizeof(CombatPathRequestGeneric<CombatPathingGoalPolicyFlee, CombatPathingSearchPolicyStandard>) == 0x30);
	static_assert(sizeof(CombatPathRequestGeneric<CombatPathingGoalPolicyRetreat, CombatPathingSearchPolicyStandard>) == 0x28);
	static_assert(sizeof(CombatPathRequestGeneric<CombatPathingGoalPolicyReturnToCombatArea, CombatPathingSearchPolicyStandard>) == 0x50);
	static_assert(sizeof(CombatPathRequestGeneric<CombatPathingGoalPolicySearchWander, CombatPathingSearchPolicyStandard>) == 0x48);
	static_assert(sizeof(CombatPathRequestGeneric<CombatPathingGoalPolicySearch, CombatPathingSearchPolicyStandard>) == 0x58);
}

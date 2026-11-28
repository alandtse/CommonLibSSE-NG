#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSPointerHandle.h"

namespace RE
{
	class ActorPackageData;
	class TESPackage;

	class ActorPackage
	{
	public:
		enum class ACTOR_PACKAGE_FLAG
		{
			kNone = 0,
			kSaveLoadSharedPackage = 1 << 0
		};

		void SetPackage(TESPackage* a_package, TESObjectREFR* a_target, Actor* a_actor)
		{
			using func_t = void(ActorPackage*, TESPackage*, TESObjectREFR*, Actor*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38005, 38959) };
			func(this, a_package, a_target, a_actor);
		}
		void ReleasePackage(void* a_handler, void* a_args)
		{
			using func_t = void(ActorPackage*, void*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38017, 38972) };
			func(this, a_handler, a_args);
		}
		void SetData(ActorPackageData* a_data)
		{
			using func_t = void(ActorPackage*, ActorPackageData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38018, 38973) };
			func(this, a_data);
		}

		void Reset(Actor* a_actor)
		{
			using func_t = void(ActorPackage*, Actor*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(38003, 38957) };
			func(this, a_actor);
		}

		// members
		mutable BSSpinLock                            packageLock;            // 00
		TESPackage*                                   package;                // 08
		ActorPackageData*                             data;                   // 10
		ObjectRefHandle                               target;                 // 18
		std::int32_t                                  currentProcedureIndex;  // 1C
		float                                         packageStartTime;       // 20
		std::uint32_t                                 modifiedPackageFlag;    // 24
		std::uint16_t                                 modifiedInterruptFlag;  // 28
		REX::EnumSet<ACTOR_PACKAGE_FLAG, std::int8_t> actorPackageFlags;      // 2A
		std::int8_t                                   preferredSpeed;         // 2B
		std::uint32_t                                 pad2C;                  // 2C
	};
	static_assert(sizeof(ActorPackage) == 0x30);
}

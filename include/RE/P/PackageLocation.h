#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/I/IAIWorldLocationHandle.h"

namespace RE
{
	class TESForm;
	class TESPackage;

	class PackageLocation : public IAIWorldLocationHandle
	{
	public:
		inline static constexpr auto RTTI = RTTI_PackageLocation;
		inline static constexpr auto VTABLE = VTABLE_PackageLocation;

		enum class Type
		{
			kNone = static_cast<std::underlying_type_t<Type>>(-1),
			kNearReference = 0,
			kInCell = 1,
			kNearPackageStartLocation = 2,
			kNearEditorLocation = 3,
			kObjectID = 4,
			kObjectType = 5,
			kNearLinkedReference = 6,
			kAtPackagelocation = 7,
			kAlias_Reference = 8,
			kAlias_Location = 9,
			kNearSelf = 12,
		};

		union Data
		{
			~Data() {}

			TESForm*        object;
			ObjectRefHandle refHandle;
		};
		static_assert(sizeof(Data) == 0x8);

		~PackageLocation() override;  // 00

		// override (IAIWorldLocationHandle)
		const IAIWorldLocation* AllocateLocation(AIWorldLocationContext* a_context) override;                       // 01
		PackageLocation*        GetAsPackageLocation() override;                                                    // 02 - { return this; }
		bool                    IsRefAtLocation(AIWorldLocationContext* a_context, TESObjectREFR* a_ref) override;  // 03

		void SetRadius(std::uint32_t a_rad)
		{
			using func_t = void(PackageLocation*, std::uint32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(28999, 29801) };
			func(this, a_rad);
		}
		bool Equals(PackageLocation* a_other)
		{
			using func_t = bool(PackageLocation*, PackageLocation*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29008, 29816) };
			return func(this, a_other);
		}
		void InitializeAfterAllFormsAreRead(TESPackage* a_package)
		{
			using func_t = void(PackageLocation*, TESPackage*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29009, 29817) };
			func(this, a_package);
		}

		bool TestActivatorTrigger(Actor* a_actor, TESObjectREFR* a_other, bool* a_outInside)
		{
			using func_t = bool(PackageLocation*, Actor*, TESObjectREFR*, bool*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29016, 29824) };
			return func(this, a_actor, a_other, a_outInside);
		}
		bool IsRefWithinRadius(TESObjectREFR* a_ref, std::uint32_t a_radius)
		{
			using func_t = bool(PackageLocation*, TESObjectREFR*, std::uint32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29017, 29825) };
			return func(this, a_ref, a_radius);
		}

		// members
		REX::EnumSet<Type, std::uint8_t> locType;  // 08
		std::uint8_t                     pad09;    // 09
		std::uint16_t                    pad0A;    // 0A
		std::uint32_t                    rad;      // 0C
		Data                             data;     // 10
	};
	static_assert(sizeof(PackageLocation) == 0x18);
}

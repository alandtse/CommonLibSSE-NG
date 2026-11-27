#pragma once

#include "RE/B/BaseFormComponent.h"
#include "RE/M/MagicSystem.h"

namespace RE
{
	class TESForm;
	class EnchantmentItem;

	class TESEnchantableForm : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESEnchantableForm;
		inline static constexpr auto VTABLE = VTABLE_TESEnchantableForm;

		~TESEnchantableForm() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01
		void ClearDataComponent() override;                     // 02
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// add
		[[nodiscard]] virtual MagicSystem::CastingType GetCastingType() const;  // 04 - { return castingType; }

		void InitComponent(TESForm* a_owner)
		{
			using func_t = void(TESEnchantableForm*, TESForm*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(14409, 14561) };
			func(this, a_owner);
		}

		// members
		EnchantmentItem*                                      formEnchanting;       // 08 - EITM
		REX::EnumSet<MagicSystem::CastingType, std::uint16_t> castingType;          // 10
		std::uint16_t                                         amountofEnchantment;  // 12 - EAMT
		std::uint32_t                                         pad14;                // 14
	};
	static_assert(sizeof(TESEnchantableForm) == 0x18);
}

#pragma once

#include "RE/B/BaseFormComponent.h"

namespace RE
{
	class TESForm;
	class TESImageSpaceModifier;

	class TESImageSpaceModifiableForm : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESImageSpaceModifiableForm;
		inline static constexpr auto VTABLE = VTABLE_TESImageSpaceModifiableForm;

		~TESImageSpaceModifiableForm() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01 - { imageSpaceModifying = 0; }
		void ClearDataComponent() override;                     // 02 - { return; }
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		void InitComponent(TESForm* a_owner)
		{
			using func_t = void(TESImageSpaceModifiableForm*, TESForm*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(14563, 14735) };
			func(this, a_owner);
		}

		// members
		TESImageSpaceModifier* imageSpaceModifying;  // 08 - MNAM
	};
	static_assert(sizeof(TESImageSpaceModifiableForm) == 0x10);
}

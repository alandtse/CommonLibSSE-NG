#pragma once

#include "RE/B/BaseFormComponent.h"

namespace RE
{
	class TESForm;
	class TESRace;

	class TESRaceForm : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESRaceForm;
		inline static constexpr auto VTABLE = VTABLE_TESRaceForm;

		~TESRaceForm() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01 - { race = 0; }
		void ClearDataComponent() override;                     // 02 - { return; }
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		void InitComponent(TESForm* a_owner)
		{
			using func_t = void(TESRaceForm*, TESForm*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(14720, 14894) };
			func(this, a_owner);
		}

		// members
		TESRace* race;  // 08 - RNAM
	};
	static_assert(sizeof(TESRaceForm) == 0x10);
}

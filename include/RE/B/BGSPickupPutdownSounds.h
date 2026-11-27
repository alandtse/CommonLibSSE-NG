#pragma once

#include "RE/B/BaseFormComponent.h"

namespace RE
{
	class TESForm;
	class BGSSoundDescriptorForm;

	class BGSPickupPutdownSounds : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSPickupPutdownSounds;
		inline static constexpr auto VTABLE = VTABLE_BGSPickupPutdownSounds;

		~BGSPickupPutdownSounds() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01
		void ClearDataComponent() override;                     // 02 - { return; }
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		void InitComponent(TESForm* a_owner)
		{
			using func_t = void(BGSPickupPutdownSounds*, TESForm*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(14221, 14333) };
			func(this, a_owner);
		}

		// members
		BGSSoundDescriptorForm* pickupSound;   // 08 - YNAM
		BGSSoundDescriptorForm* putdownSound;  // 10 - ZNAM
	};
	static_assert(sizeof(BGSPickupPutdownSounds) == 0x18);
}

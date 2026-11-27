#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSString.h"
#include "RE/B/BaseFormComponent.h"

namespace RE
{
	class TESFile;
	class TESTexture : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESTexture;
		inline static constexpr auto VTABLE = VTABLE_TESTexture;

		~TESTexture() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01
		void ClearDataComponent() override;                     // 02
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// add
		virtual std::uint32_t             GetMaxAllowedSize();                     // 04 - { return 0; }
		virtual const char*               GetAsNormalFile(BSString& a_out) const;  // 05
		[[nodiscard]] virtual const char* GetDefaultPath() const;                  // 06 - { return "Textures\\"; }

		void LoadTextureChunk(TESFile* a_file)
		{
			using func_t = void(TESTexture*, TESFile*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(14787, 14965) };
			func(this, a_file);
		}

		// members
		BSFixedString textureName;  // 08 - ICON
	};
	static_assert(sizeof(TESTexture) == 0x10);
}

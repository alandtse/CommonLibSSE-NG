#pragma once

#include "RE/B/BGSSceneAction.h"
#include "RE/B/BSTArray.h"

namespace RE
{
	class TESPackage;

	class BGSSceneActionPackage : public BGSSceneAction
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSSceneActionPackage;
		inline static constexpr auto VTABLE = VTABLE_BGSSceneActionPackage;
		inline static constexpr auto TYPE = Type::kPackage;

		~BGSSceneActionPackage() override;  // 00

		// override (BGSSceneAction)
		bool LoadSceneAction(TESFile* a_mod) override;                     // 01
		void Unk_02(void) override;                                        // 02
		Type GetType() const override;                                     // 07 - { return kPackage; }
		void Unk_08(void) override;                                        // 08
		void LoadBuffer(void* a_arg1, BGSLoadGameBuffer* a_buf) override;  // 09
		void SaveBuffer(BGSSaveFormBuffer* a_buf) override;                // 0A
		void ClearActiveFlags() override;                                  // 0B
		void Unk_10(void) override;                                        // 10
		void Unk_11(void) override;                                        // 11
		void Unk_12(void) override;                                        // 12
		void Unk_13(void) override;                                        // 13

		bool TryStartPackage(void* a_context, TESPackage* a_package)
		{
			using func_t = bool(BGSSceneActionPackage*, void*, TESPackage*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(23801, 24253) };
			return func(this, a_context, a_package);
		}
		bool StartFirstValidPackage(void* a_packages, void* a_context)
		{
			using func_t = bool(BGSSceneActionPackage*, void*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(23802, 24252) };
			return func(this, a_packages, a_context);
		}

		// members
		std::uint64_t         unk20;     // 20
		BSTArray<TESPackage*> packages;  // 28 - PNAM
	};
	static_assert(sizeof(BGSSceneActionPackage) == 0x40);
}

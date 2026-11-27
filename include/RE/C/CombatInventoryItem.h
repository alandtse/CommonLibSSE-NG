#pragma once

#include "RE/A/ActorValues.h"
#include "RE/C/CombatObject.h"

namespace RE
{
	class BGSLoadGameBuffer;
	class BGSSaveGameBuffer;
	class CombatController;
	class TESBoundObject;
	class TESForm;
	class BGSEquipSlot;

	struct CombatInventoryItemResource
	{
	public:
		// members
		ActorValue actorValue;  // 00
		float      value;       // 04
	};
	static_assert(sizeof(CombatInventoryItemResource) == 0x8);

	class CombatInventoryItemSlot
	{
	public:
		// members
		BGSEquipSlot* equipSlot;  // 00
		std::uint32_t slot;       // 08
	};
	static_assert(sizeof(CombatInventoryItemSlot) == 0x10);

	class CombatInventoryItem : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatInventoryItem;
		inline static constexpr auto VTABLE = VTABLE_CombatInventoryItem;

		enum class TYPE
		{
			kNone = 0,
			kMelee,
			kRanged,
			kShield,
			kOneHandedBlock = kShield,
			kMagic,
			kShout,
			kStaff,
			kPotion,
			kScroll,
			kTorch
		};

		enum class CATEGORY
		{
			kTotal = 7
		};

		~CombatInventoryItem() override;  // 00

		// override (CombatObject)
		void SaveGame(BGSSaveGameBuffer* a_buf) override;  // 03
		void LoadGame(BGSLoadGameBuffer* a_buf) override;  // 04

		// add
		virtual float                GetMinRange();                                             // 05 - { return 0.0; }
		virtual float                GetMaxRange();                                             // 06 - { return 0.0; }
		virtual float                GetOptimalRange();                                         // 07 - { return 0.0; }
		virtual float                GetEquipRange();                                           // 08 - { return FLT_MAX; }
		virtual TYPE                 GetType();                                                 // 09
		virtual TYPE                 GetEquipType(BGSEquipSlot* a_slot);                        // 0A - { return GetType(); }
		virtual CATEGORY             GetCategory() = 0;                                         // 0B
		virtual float                CalculateScore(CombatController* a_controller) = 0;        // 0C
		virtual CombatInventoryItem* Clone() = 0;                                               // 0D
		virtual bool                 CheckBusy(CombatController* a_controller);                 // 0E
		virtual bool                 CheckShouldEquip(CombatController* a_controller);          // 0F - { return !a_controller->state->isFleeing; }
		virtual bool                 GetResource(CombatInventoryItemResource& a_resource);      // 10
		virtual void                 Equip(CombatController* a_controller);                     // 11
		virtual void                 Unequip(CombatController* a_controller);                   // 12
		virtual bool                 IsValid();                                                 // 13 - { return item != nullptr; }
		virtual void                 GetDescription(const char* a_dest, std::uint32_t a_size);  // 14

		// members
		TESForm*                item;       // 10
		float                   itemScore;  // 18
		std::uint32_t           unk1C;      // 1C
		CombatInventoryItemSlot itemSlot;   // 20
	};
	static_assert(sizeof(CombatInventoryItem) == 0x30);

	class CombatInventoryItemComposite : public CombatInventoryItem
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatInventoryItemComposite;
		inline static constexpr auto VTABLE = VTABLE_CombatInventoryItemComposite;

		~CombatInventoryItemComposite() override;  // 00

		// members
		TESForm* unk30;  // 30
	};
	static_assert(sizeof(CombatInventoryItemComposite) == 0x38);

	class CombatInventoryItemMelee : public CombatInventoryItem
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatInventoryItemMelee;
		inline static constexpr auto VTABLE = VTABLE_CombatInventoryItemMelee;

		~CombatInventoryItemMelee() override;  // 00

		// members
		std::uint32_t unk30;  // 30
	};
	static_assert(sizeof(CombatInventoryItemMelee) == 0x38);

	class CombatInventoryItemShield : public CombatInventoryItem
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatInventoryItemShield;
		inline static constexpr auto VTABLE = VTABLE_CombatInventoryItemShield;

		~CombatInventoryItemShield() override;  // 00

		// members
		std::uint32_t unk30;  // 30
	};
	static_assert(sizeof(CombatInventoryItemShield) == 0x38);

	class CombatInventoryItemTorch : public CombatInventoryItem
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatInventoryItemTorch;
		inline static constexpr auto VTABLE = VTABLE_CombatInventoryItemTorch;

		~CombatInventoryItemTorch() override;  // 00

		// members
		std::uint32_t unk30;  // 30
	};
	static_assert(sizeof(CombatInventoryItemTorch) == 0x38);

	class CombatInventoryItemOneHandedBlock : public CombatInventoryItemShield
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatInventoryItemOneHandedBlock;
		inline static constexpr auto VTABLE = VTABLE_CombatInventoryItemOneHandedBlock;

		~CombatInventoryItemOneHandedBlock() override;  // 00
	};
	static_assert(sizeof(CombatInventoryItemOneHandedBlock) == 0x38);

	class CombatInventoryItemRanged : public CombatInventoryItemComposite
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatInventoryItemRanged;
		inline static constexpr auto VTABLE = VTABLE_CombatInventoryItemRanged;

		~CombatInventoryItemRanged() override;  // 00

		// members
		std::uint32_t unk38;  // 38
		std::uint32_t unk3C;  // 3C
	};
	static_assert(sizeof(CombatInventoryItemRanged) == 0x40);
}

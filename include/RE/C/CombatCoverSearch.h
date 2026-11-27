#pragma once

#include "RE/C/CombatObject.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class CombatCoverSearchResult;

	class CombatCoverSearch : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatCoverSearch;
		inline static constexpr auto VTABLE = VTABLE_CombatCoverSearch;

		class Params
		{
		public:
			// members
			std::uint32_t handle00;     // 00
			std::uint32_t unk04;        // 04
			std::uint32_t unk08;        // 08
			std::uint32_t unk0C;        // 0C
			std::uint8_t  unk10;        // 10
			std::uint8_t  unk11;        // 11
			std::byte     pad12[0x2];   // 12
			std::uint32_t unk14;        // 14
			std::uint32_t unk18;        // 18
			NiPoint3      unk1C;        // 1C
			NiPoint3      unk28;        // 28
			std::byte     unk38[0x18];  // 38
			CombatObject* unk50;        // 50
		};
		static_assert(sizeof(Params) == 0x58);

		~CombatCoverSearch() override;  // 00

		// members
		Params                   params;  // 10
		CombatCoverSearchResult* result;  // 68
		std::uint32_t            unk70;   // 70
		NiPoint3                 unk74;   // 74
		void*                    unk80;   // 80
	};
	static_assert(sizeof(CombatCoverSearch) == 0x88);

	class CombatCoverSearchResult : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatCoverSearchResult;
		inline static constexpr auto VTABLE = VTABLE_CombatCoverSearchResult;

		~CombatCoverSearchResult() override;  // 00

		// members
		CombatCoverSearch* coverSearch;  // 10
		CombatObject*      unk18;        // 18
	};
	static_assert(sizeof(CombatCoverSearchResult) == 0x20);
}

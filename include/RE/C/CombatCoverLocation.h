#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSNavmesh;

	class CombatCoverLocation : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatCoverLocation;
		inline static constexpr auto VTABLE = VTABLE_CombatCoverLocation;

		struct CoverData
		{
		public:
			// members
			std::uint8_t  unk00;       // 00
			std::uint8_t  unk01;       // 01
			std::uint8_t  unk02;       // 02
			std::uint8_t  unk03;       // 03
			std::byte     pad04[0x4];  // 04
			BSNavmesh*    navmesh;     // 08
			std::uint16_t triangle;    // 10
			std::byte     pad12[0x6];  // 12
			std::int32_t  unk18;       // 18
			std::byte     pad1C[0x4];  // 1C
			std::uint32_t mapKey;      // 20
			NiPoint3      unk24;       // 24
			NiPoint3      unk30;       // 30
			NiPoint3      unk3C;       // 3C
			NiPoint3      unk48;       // 48
			float         length;      // 54
		};
		static_assert(sizeof(CoverData) == 0x58);

		~CombatCoverLocation() override;  // 00

		// members
		CoverData     data;               // 10
		ActorHandle   attackerHandle;     // 68
		NiPoint3      coverPosition;      // 6C
		NiPoint3      secondaryPosition;  // 78
		NiPoint3      targetPosition;     // 84
		std::uint32_t mapKey;             // 90
		std::uint32_t flags;              // 94
		float         width;              // 98
	};
	static_assert(sizeof(CombatCoverLocation) == 0xA0);
}

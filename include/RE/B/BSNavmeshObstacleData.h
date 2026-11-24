#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiRefObject.h"

namespace RE
{
	class BSNavmeshInfo;

	// Layout beyond the reference count and navmeshInfos is unresolved.
	class BSNavmeshObstacleData : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSNavmeshObstacleData;
		inline static constexpr auto VTABLE = VTABLE_BSNavmeshObstacleData;

		~BSNavmeshObstacleData() override;  // 00

		// members
		std::uint8_t             unk10[0x90];   // 10
		BSTArray<BSNavmeshInfo*> navmeshInfos;  // A0
		std::uint8_t             padB8[8];      // B8
	};
	static_assert(sizeof(BSNavmeshObstacleData) == 0xC0);
}

#pragma once

#include "RE/B/BGSQueuedTerrainUpdate.h"

namespace RE
{
	class BGSQueuedTerrainUpgrade : public BGSQueuedTerrainUpdate
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSQueuedTerrainUpgrade;
		inline static constexpr auto VTABLE = VTABLE_BGSQueuedTerrainUpgrade;

		~BGSQueuedTerrainUpgrade() override;  // 00

		// override (BGSQueuedTerrainUpdate)
		bool          IsReady() override;        // 01
		void          Apply() override;          // 02
		bool          IsStillValid() override;   // 03
		void          Cancel() override;         // 04
		std::uint32_t GetUpdateType() override;  // 05
	};
}

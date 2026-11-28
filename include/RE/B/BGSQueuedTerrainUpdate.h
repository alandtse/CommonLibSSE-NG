#pragma once

namespace RE
{
	class BGSQueuedTerrainUpdate
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSQueuedTerrainUpdate;
		inline static constexpr auto VTABLE = VTABLE_BGSQueuedTerrainUpdate;

		virtual ~BGSQueuedTerrainUpdate();  // 00

		// add
		virtual bool          IsReady();        // 01 - polled by BGSTerrainUpdateManager::Update before Apply
		virtual void          Apply();          // 02
		virtual bool          IsStillValid();   // 03 - false cancels and deletes the task
		virtual void          Cancel();         // 04
		virtual std::uint32_t GetUpdateType();  // 05
	};
	static_assert(sizeof(BGSQueuedTerrainUpdate) == 0x8);
}

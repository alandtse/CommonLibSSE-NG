#pragma once

#include "RE/B/BSTArray.h"
#include "RE/D/DetectionListener.h"

namespace RE
{
	class ActorKnowledge;

	// Collects the knowledge entries an actor's detection pass queues until the pass completes.
	class DetectionCollector : public DetectionListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_DetectionCollector;
		inline static constexpr auto VTABLE = VTABLE_DetectionCollector;

		~DetectionCollector() override;  // 00

		// override (DetectionListener)
		void Unk_02(void) override;  // 02 - UpdateKnowledge(ActorKnowledge*)

		// add
		virtual void Unk_05(void) = 0;  // 05 - OnComplete

		// members
		BSTArray<void*> recorded;     // 10
		std::uint32_t   queuedCount;  // 28
		std::uint32_t   flags;        // 2C - 1 all queued, 2 completed, 4 someone detected, 8 constructor argument
	};
	static_assert(sizeof(DetectionCollector) == 0x30);
}

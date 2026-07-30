#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/I/IMemoryHeap.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSTask;

	// Real event-sink payload type is unresolved; only used here as the template
	// argument for the embedded BSTEventSource, never dereferenced.
	class BSTaskManagerWaitAction;

	// Global io-task scheduler; owns the resubmit/notify dispatch called by
	// BSQueuedResourceCollectionBase::Unk_09/Unk_11. Real inheritance is
	// SynchronizedMap<int64,NiPointer<BSTask>> -> BSTaskManager -> IOManager,
	// modeled flatly since BSTaskManager adds no fields of its own.
	class IOManager
	{
	public:
		static IOManager* GetSingleton()
		{
			static REL::Relocation<IOManager**> singleton{ RELOCATION_ID(524542, 411121) };
			return *singleton;
		}

		virtual ~IOManager();  // 00

		// add (SynchronizedMap<std::int64_t, NiPointer<BSTask>> base)
		virtual void Unk_01() { return; }  // 01
		virtual void Unk_02() { return; }  // 02

		// add (SynchronizedMap base; not overridden by IOManager)
		virtual bool          FindOrInsert(std::int64_t a_key, NiPointer<BSTask>& a_value, IMemoryHeap* a_heap, bool a_skipDuplicates);        // 03
		virtual bool          FindOrInsertByHash(std::int64_t a_key, NiPointer<BSTask>& a_value, IMemoryHeap* a_heap, bool a_skipDuplicates);  // 04 - like 03, but hashes the key itself
		virtual bool          Unk_05(BSTask* a_task);                                                                                          // 05 - predicate gating NotifyTaskComplete's decrement; real signature may take more args than modeled here
		virtual bool          Erase(std::int64_t a_key, NiPointer<BSTask>& a_valueOut);                                                        // 06
		virtual bool          FindFirstMatching(NiPointer<BSTask>& a_valueOut);                                                                // 07 - calls 06 with increasing indices until it returns true
		virtual std::uint32_t Unk_08(std::uint64_t a_packed);                                                                                  // 08 - bucket index = byte0 + byte1*4 of a packed 2-byte key (base class instead does key % bucketCount)

		// add (SynchronizedMap base)
		virtual void Unk_09() { return; }  // 09
		virtual void Unk_10() { return; }  // 10 - real signature takes unmodeled args; not yet reconstructed
		virtual void Unk_11() { return; }  // 11 - real signature takes unmodeled args; not yet reconstructed
		virtual void Unk_12() { return; }  // 12 - real signature takes unmodeled args; not yet reconstructed
		virtual void Unk_13() { return; }  // 13 - real signature takes unmodeled args; not yet reconstructed
		virtual void Unk_14() { return; }  // 14 - increments the counter at +0x30
		virtual void Unk_15() { return; }  // 15 - decrements the counter at +0x30
		virtual void Unk_16() { return; }  // 16 - reads the counter at +0x30

		// add (BSTaskManager base)
		virtual void ResubmitTask(BSTask* a_task);  // 17 - called by BSQueuedResourceCollectionBase::Unk_09

		// add (BSTaskManager base; slot 24 is IOManager's own, BSTaskManager has no slot 24)
		virtual void Unk_18() { return; }  // 18 - real signature takes unmodeled args; not yet reconstructed
		virtual void Unk_19() { return; }  // 19 - real signature takes unmodeled args; not yet reconstructed
		virtual void Unk_20() { return; }  // 20 - drains pending tasks synchronously; IOManager runs extra work after the base drain
		virtual void Unk_21() { return; }  // 21 - drains and finalizes a list of BSResource::EntryDB entries
		virtual void Unk_22() { return; }  // 22 - clears a shared flag when not the primary loading thread
		virtual void Unk_23() { return; }  // 23
		virtual void Unk_24() { return; }  // 24 - sets the same shared flag slot 22 clears

		// members
		void NotifyTaskComplete(BSTask* a_task);  // non-virtual; dispatches Unk_08 then Unk_05 to gate a per-bucket decrement

		// SynchronizedMap<std::int64_t, NiPointer<BSTask>> base fields (08-40);
		// BSTaskManager itself adds no further fields of its own.
		void*                                   nodePool;         // 08 - pool of preallocated 24-byte nodes (next/key/value), sized threadCount+16
		std::uint32_t                           bucketCount;      // 10 - 24 in this instantiation
		std::uint32_t                           unk14;            // 14
		void*                                   bucketHeads;      // 18 - bucketCount head pointers
		std::uint32_t                           unk20;            // 20 - per-bucket capacity
		std::uint32_t                           pad24;            // 24
		std::uint8_t                            threadCache[24];  // 28 - per-thread lookup cache; contains a Mutex at +0xC guarding all mutating ops
		BSTEventSource<BSTaskManagerWaitAction> events;           // 40
		std::uint8_t                            unk98[144];       // 98 - includes a per-bucket int32 array + counter (+0xB0/+0xB8), a BSTArrayHeapAllocator (+0xC0), and a thread-pool-size constant = 6 (+0xE8)
	};
	static_assert(sizeof(IOManager) == 0x128);
}

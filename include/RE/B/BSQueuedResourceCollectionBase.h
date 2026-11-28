#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSResourceEntryDB.h"
#include "RE/B/BSTArray.h"
#include "RE/Q/QueuedFile.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	struct QueuedResourceEntry
	{
		void*         resourceHandle;  // 00 - freed via FreeRequestedModel on removal
		BSFixedString path;            // 08
	};
	static_assert(sizeof(QueuedResourceEntry) == 0x10);

	// Base of TESModelDB::TESQueuedHandles and the BSQueuedResourceCollection<Traits,N>
	// instantiations; multiply-inherits QueuedFile (primary) and
	// BSResource::IEntryDB::PostFlushNotify (secondary).
	class BSQueuedResourceCollectionBase :
#ifndef SKYRIM_CROSS_VR
		public QueuedFile,                            // 00
		public BSResource::IEntryDB::PostFlushNotify  // 38 (SE/AE) / 40 (VR)
#else
		public QueuedFile  // 00
#endif
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSQueuedResourceCollectionBase;
		inline static constexpr auto VTABLE = VTABLE_BSQueuedResourceCollectionBase;

		~BSQueuedResourceCollectionBase() override;  // 00

		// override (BSTask)
		void Cancel(std::uint32_t a_previousState, void* a_unk) override;      // 03 - CAS-guards on PostFlushNotify::TryAbort; on success releases the parent, calls BSTask's own slots 1/2, then PostFlushNotify::Aborted
		bool GetDescription(char* a_dest, std::uint32_t a_maxCount) override;  // 04 - debug type name, "Queued resource collection"

		// override (QueuedFile)
		void DoOnQueueMe() override;           // 09 - if pendingCount is nonzero, bumps refCount, calls Unk_15, and resubmits `this` to the global IOManager; else sets BSTask::unk0C (abort-state) to 5
		void DoOnChildrenFinished() override;  // 0A - if pendingCount==0 and abort-state is 0/1, CASes abort-state to 4 and records needNotifyFlag
		void DoOnTaskFinished() override;      // 0B - calls Unk_13; if needNotifyFlag is set, notifies the global IOManager and clears it

		// add
		virtual void Unk_12() { return; }  // 12
		virtual void Unk_13() { return; }  // 13
		virtual void Unk_14() { return; }  // 14

		RUNTIME_CAST_ACCESSOR(BSResource::IEntryDB::PostFlushNotify, AsPostFlushNotify, 0x38, 0x40);

		struct COLLECTION_RUNTIME_DATA
		{
#define COLLECTION_RUNTIME_DATA_CONTENT                                                                                  \
	std::uint32_t                         pendingCount;   /* 50 (VR 58) - nonzero while entries are outstanding */       \
	bool                                  needNotifyFlag; /* 54 (VR 5C) - set by Unk_10, consumed by Unk_11 */           \
	bool                                  unk55;          /* 55 (VR 5D) - nonzero at construction; purpose unresolved */ \
	std::uint16_t                         pad56;          /* 56 (VR 5E) */                                               \
	BSTSmallArray<QueuedResourceEntry, 2> queue;          /* 58 (VR 60) */

			COLLECTION_RUNTIME_DATA_CONTENT
		};

		RUNTIME_DATA_ACCESSOR_EX(COLLECTION_RUNTIME_DATA, GetCollectionRuntimeData, 0x50, 0x58);
		// members
#ifndef SKYRIM_CROSS_VR
		COLLECTION_RUNTIME_DATA_CONTENT;  // 50 (VR 58)
#endif
	};
	STATIC_ASSERT_SIZE(BSQueuedResourceCollectionBase, 0x88, 0x90);
}
#undef COLLECTION_RUNTIME_DATA_CONTENT

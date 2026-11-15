#pragma once
#include "RE/B/BSStorage.h"
#include "RE/C/CodeTasklet.h"
#include "RE/L/LoadStorageWrapper.h"
#include "RE/O/Object.h"
#include "RE/S/SaveFileHandleReaderWriter.h"

namespace RE
{
	class ScrapHeap;

	namespace BSScript
	{
		enum class StringIndexSize
		{
			kSmall,
			kLarge
		};

		template <class T, std::size_t N>
		struct ScrapChunkQueue
		{
			struct Chunk
			{
				T      items[N];  // 00
				Chunk* next;      // N * sizeof(T)
			};

			ScrapHeap*    heap;           // 00
			Chunk*        firstChunk;     // 08
			Chunk**       lastChunkLink;  // 10 - init &firstChunk
			Chunk*        lastChunk;      // 18
			Chunk*        freeList;       // 20
			T*            writePos;       // 28
			T*            readPos;        // 30
			std::uint32_t count;          // 38
			std::uint32_t pad3C;          // 3C
		};

		struct StringPage
		{
			char  chars[0x1000];  // 0000
			char* cursor;         // 1000 - next free byte, set by ReadableStringTable::Init
			char* limit;          // 1008 - end of chars
		};
		static_assert(sizeof(StringPage) == 0x1010);

		class ReadableStringTable
		{
		public:
			class StringEntry
			{
			public:
				// members
				const char*   originalData;     // 00
				BSFixedString convertedString;  // 08
			};
			static_assert(sizeof(StringEntry) == 0x10);

			// members
			ScrapChunkQueue<StringPage, 1>*             pages;      // 00
			BSScrapArray<StringEntry>*                  entries;    // 08
			REX::EnumSet<StringIndexSize, std::int32_t> indexSize;  // 10
		};

		static_assert(sizeof(ReadableStringTable) == 0x18);

		class WritableStringTable
		{
		public:
			// members
			ScrapChunkQueue<BSFixedString, 32>*            stringArray;   // 00
			BSTScrapHashMap<BSFixedString, std::uint32_t>* referenceMap;  // 08
			REX::EnumSet<StringIndexSize, std::int32_t>    indexSize;     // 10
		};
		static_assert(sizeof(WritableStringTable) == 0x18);

		class WritableTypeTable
		{
		public:
			WritableTypeTable() :
				typeTable(nullptr) {}
			BSTScrapHashMap<BSFixedString, BSTSmartPointer<ObjectTypeInfo>>* typeTable;
		};
		static_assert(sizeof(WritableTypeTable) == 0x8);

		struct ReadableTypeInfo : BSIntrusiveRefCounted
		{
			BSFixedString               parentName;   // 08
			BSScrapArray<std::uint32_t> variableMap;  // 10
		};

		static_assert(sizeof(ReadableTypeInfo) == 0x30);
		static_assert(offsetof(ReadableTypeInfo, parentName) == 0x8);

		class ReadableTypeTable
		{
		public:
			ReadableTypeTable() :
				typeTable(nullptr) {}
			BSTScrapHashMap<BSFixedString, BSTSmartPointer<ReadableTypeInfo>>* typeTable;
		};
		static_assert(sizeof(ReadableTypeTable) == 0x8);

		class IVMSaveLoadInterface
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSScript__IVMSaveLoadInterface;
			inline static constexpr auto VTABLE = VTABLE_BSScript__IVMSaveLoadInterface;

			virtual ~IVMSaveLoadInterface();  // 00

			// add
			virtual bool                       SaveGame(SaveStorageWrapper* a_wrapper, SkyrimScript::SaveFileHandleReaderWriter* a_handle, bool a_bForceResetState) = 0;              // 01
			virtual bool                       LoadGame(LoadStorageWrapper* a_wrapper, SkyrimScript::SaveFileHandleReaderWriter* a_handle, bool* a_loadOk, bool* a_saveInvalid) = 0;  // 02
			virtual void                       MarkSaveInvalid(BSStorage* a_storage) = 0;                                                                                             // 03
			virtual std::uint16_t              GetSaveGameVersion() = 0;                                                                                                              // 04
			virtual void                       CleanupSave() = 0;                                                                                                                     // 05
			virtual void                       CleanupObjects() = 0;                                                                                                                  // 06
			virtual void                       DropAllRunningData() = 0;                                                                                                              // 07
			virtual std::uint64_t              GetObjectSaveID(Object* a_obj) = 0;                                                                                                    // 08
			virtual void                       Unk_09(void) = 0;                                                                                                                      // 09
			virtual bool                       GetSavedObject(VMHandle a_handle, BSTSmartPointer<Object>& a_out) = 0;                                                                 // 0A
			virtual std::uint64_t              GetArraySaveID(Array* a_array) = 0;                                                                                                    // 0B
			virtual void                       Unk_0C(void) = 0;                                                                                                                      // 0C
			virtual bool                       GetSavedArray(VMHandle a_handle, BSTSmartPointer<Array>& a_out) = 0;                                                                   // 0D
			virtual bool                       ReadVMHandle(LoadStorageWrapper* a_wrapper, VMHandle& a_outHandle) = 0;                                                                // 0E
			virtual bool                       GetStackByID(VMStackID a_stackID, BSTSmartPointer<Stack>& a_out) = 0;                                                                  // 0F
			virtual WritableStringTable*       GetWritableStringTable() = 0;                                                                                                          // 10
			virtual const WritableStringTable* GetWritableStringTable2() = 0;                                                                                                         // 11
			virtual ReadableStringTable*       GetReadableStringTable() = 0;                                                                                                          // 12
			virtual WritableTypeTable*         GetWritableTypeTable() = 0;                                                                                                            // 13
			virtual const WritableTypeTable*   GetWritableTypeTable2() = 0;                                                                                                           // 14
			virtual ReadableTypeTable*         GetReadableTypeTable() = 0;                                                                                                            // 15
			virtual bool                       CreateEmptyTasklet(Stack* a_stack, BSTSmartPointer<Internal::CodeTasklet>& a_outTasklet) = 0;                                          // 16
		};

		static_assert(sizeof(IVMSaveLoadInterface) == 0x8);
	}
}

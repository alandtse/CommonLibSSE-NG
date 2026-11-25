#pragma once

namespace RE
{
	struct BSPathingSolution;

	struct PathingSolutionEntry
	{
	public:
		std::int32_t       status;    // 00 - -1 default, 0 start following
		std::uint32_t      pad04;     // 04
		BSPathingSolution* solution;  // 08 - NiPointer
	};
	static_assert(sizeof(PathingSolutionEntry) == 0x10);

	// Re-entrant try-locked queue of pending path solutions.
	struct PathingSolutionQueue
	{
	public:
		std::uint32_t refCount;       // 00
		std::uint32_t pad04;          // 04
		std::uint32_t capacity;       // 08 - bit 31 set means inline storage
		std::uint32_t pad0C;          // 0C
		std::uint8_t  storage[0x10];  // 10 - inline entry or data pointer
		std::uint32_t size;           // 20
		std::uint32_t pad24;          // 24
		std::uint32_t ownerThreadId;  // 28
		std::uint32_t lockDepth;      // 2C

		bool PushBack(void* a_entry)
		{
			using func_t = bool(PathingSolutionQueue*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88932, 91386) };
			return func(this, a_entry);
		}
		bool TryPushBack(void* a_entry)
		{
			using func_t = bool(PathingSolutionQueue*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88933, 91387) };
			return func(this, a_entry);
		}
		bool PopFront(void* a_out)
		{
			using func_t = bool(PathingSolutionQueue*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88934, 91388) };
			return func(this, a_out);
		}
		bool TryPopFront(void* a_out)
		{
			using func_t = bool(PathingSolutionQueue*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88935, 91389) };
			return func(this, a_out);
		}
	};
	static_assert(sizeof(PathingSolutionQueue) == 0x30);
}

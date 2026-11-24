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
	};
	static_assert(sizeof(PathingSolutionQueue) == 0x30);
}

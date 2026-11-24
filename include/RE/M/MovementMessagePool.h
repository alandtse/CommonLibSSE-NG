#pragma once

namespace RE
{
	class Character;
	class MovementMessage;

	// Per-process pool of message functor nodes and the table of registered message handlers.
	class MovementMessagePool
	{
	public:
		bool Dispatch(Character* a_character, MovementMessage* a_message)
		{
			using func_t = bool(MovementMessagePool*, Character*, MovementMessage*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(37388, 37892) };
			return func(this, a_character, a_message);
		}

		// members
		std::uint64_t unk00;                // 000
		std::uint32_t freeListLock;         // 008 - spin flag
		std::uint32_t pad0C;                // 00C
		void*         freeListHead;         // 010 - 0x20-byte functor node free list
		std::uint8_t  unk18[0x8];           // 018
		std::uint8_t  nodes[0x200];         // 020 - 16 nodes {vtable, object, memberData, nextFree}
		std::uint8_t  handlerTable[0x1A0];  // 220 - scatter table keyed by message type crc32
	};
	static_assert(sizeof(MovementMessagePool) == 0x3C0);
}

#pragma once

namespace RE
{
	class hkpShape;

	// source: activeragdoll; not independently Ghidra-verified (no consumer found)
	class bhkRigidBodyCinfo
	{
	public:
		// members
		std::uint32_t collisionFilterInfo;  // 00
		hkpShape*     shape;                // 08
		std::uint8_t  unk10;                // 10
		std::uint8_t  pad11[7];             // 11
		std::uint64_t unk18;                // 18
		std::uint32_t unk20;                // 20
		float         unk24;                // 24
		std::uint8_t  unk28;                // 28
		std::uint16_t unk2A;                // 2A - quality type?
		std::uint8_t  pad2C[4];             // 2C
		std::uint8_t  hkCinfo[0xE0];        // 30 - hkpRigidBodyCinfo (raw Havok SDK type, not RE'd)
	};
	static_assert(offsetof(bhkRigidBodyCinfo, shape) == 0x08);
	static_assert(offsetof(bhkRigidBodyCinfo, hkCinfo) == 0x30);
	static_assert(sizeof(bhkRigidBodyCinfo) == 0x110);
}

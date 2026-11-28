#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	// low-poly hull mesh of a navmesh; the compressed form (heap) is stored in BSNavmeshInfo::bounds,
	// the expanded form (scrap heap, u16 counts at 28/2A) is used for file I/O
	struct BSCompressedNavmeshBounds
	{
	public:
		void FreeScrapArrays()
		{
			using func_t = void(BSCompressedNavmeshBounds*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(88833, 91282) };
			func(this);
		}

		// members
		NiPoint3      boundsMin;      // 00
		NiPoint3      boundsMax;      // 0C
		void*         triangles;      // 18 - compressed: u8[3] vertex indices, expanded: u16[3]
		void*         vertices;       // 20 - compressed: u8[3] quantized 0..250 across bounds, expanded: NiPoint3
		std::uint8_t  triangleCount;  // 28 - u16 in the expanded form
		std::uint8_t  vertexCount;    // 29 - compressed form only
		std::uint16_t pad2A;          // 2A - vertex count in the expanded form
		std::uint32_t pad2C;          // 2C
	};
	static_assert(sizeof(BSCompressedNavmeshBounds) == 0x30);
}

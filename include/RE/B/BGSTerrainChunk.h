#pragma once

#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BGSTerrainNode;
	class BSGeometry;
	class BSMultiBoundNode;

	class BGSTerrainChunk
	{
	public:
		BGSTerrainNode*             terrainNode;    // 00
		NiPointer<BSGeometry>       landMesh;       // 08
		NiPointer<BSMultiBoundNode> waterNode;      // 10
		NiPointer<BSMultiBoundNode> node;           // 18
		bool                        doneLoading;    // 20
		bool                        attached;       // 21
		bool                        waterAttached;  // 22
		bool                        prepared;       // 23
		std::uint32_t               pad24;          // 24
	};
	static_assert(sizeof(BGSTerrainChunk) == 0x28);
}

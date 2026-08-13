#pragma once

#include <cstdint>

namespace RE
{
	// The engine's landscape collision descriptor, built on the stack by the land geometry init
	// and handed to CellMopp::BuildLandCollision, which walks it into one HeightFieldCInfo per
	// quadrant. Not a Havok reference-counted type - stack-only, no vtable.
	class LandCollisionDesc
	{
	public:
		const float*  heights;      // 00 - &LoadedLandData::heights[0][0]; quadrant q starts 289 floats in
		float         xSpacing;     // 08 - world units between grid columns (128)
		float         heightScale;  // 0C - world units per stored height unit (1)
		float         ySpacing;     // 10 - world units between grid rows (128)
		std::uint32_t pad14;        // 14
		void**        quadShapes;   // 18 - the quadrant render shapes the bodies are linked to
		std::uint32_t quadCount;    // 20 - 4
		float         baseHeight;   // 24 - the per-land height base the stored heights are relative to
		std::uint32_t gridDim;      // 28 - 17
		std::uint32_t material;     // 2C
		std::uint32_t filterInfo;   // 30
		std::uint32_t pad34;        // 34
	};
	static_assert(sizeof(LandCollisionDesc) == 0x38);
}

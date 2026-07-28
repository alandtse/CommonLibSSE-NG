#pragma once

namespace RE
{
	class NiAVObject;

	struct BSProceduralGeomEvent
	{
	public:
		// members
		NiAVObject* geometry;  // 00
	};
	static_assert(sizeof(BSProceduralGeomEvent) == 0x8);
}

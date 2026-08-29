#pragma once

#include "RE/N/NiExtraData.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	// CommonLib only provides RTTI/VTABLE for this class. Verified against SkyrimSE.exe:
	// the resize helper reads count from +0x20, allocates count * sizeof(NiPoint3) and
	// stores the result at +0x18; a separate consumer reads +0x24 alongside +0x18 as a
	// (data, count) pair.
	class BSFaceGenBaseMorphExtraData : public NiExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSFaceGenBaseMorphExtraData;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSFaceGenBaseMorphExtraData;
		inline static constexpr auto VTABLE = VTABLE_BSFaceGenBaseMorphExtraData;

		NiPoint3*     vertexData;        // 18
		std::uint32_t modelVertexCount;  // 20
		std::uint32_t vertexCount;       // 24
	};
	static_assert(sizeof(BSFaceGenBaseMorphExtraData) == 0x28);
}

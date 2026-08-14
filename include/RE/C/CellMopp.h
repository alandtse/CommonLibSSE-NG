#pragma once

#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTArray.h"

namespace RE
{
	class bhkRigidBody;

	// Builds and owns one cell's landscape collision: one bhkTriSampledHeightFieldBvTreeShape
	// per quadrant, each wrapped in a bhkRigidBody and queued into the cell's Havok world.
	class CellMopp : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CellMopp;
		inline static constexpr auto VTABLE = VTABLE_CellMopp;

		~CellMopp() override;  // 00

		// members
		std::uint8_t                            unk10[0xC8];  // 10 - not yet identified
		NiTObjectArray<NiPointer<bhkRigidBody>> rigidBodies;  // D8
	};
	static_assert(sizeof(CellMopp) == 0xF0);
}

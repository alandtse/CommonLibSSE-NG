#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSNavmesh;

	// partial layout, size not yet confirmed:
	// 08 - BSTHashMap<navmeshID, base slot>, 30 - byte[] per-triangle state (init 0x7F),
	// 38 - BSTArray<BSNavmesh*>, 48 - navmesh count, 50 - total triangle slots
	// referenced as BSNavmeshSearch::rayCache
	class NavmeshSearchRayCache
	{
	public:
		bool Init(const BSTArray<NiPointer<BSNavmesh>>& a_navmeshes)
		{
			using func_t = bool(NavmeshSearchRayCache*, const BSTArray<NiPointer<BSNavmesh>>&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89188, 91659) };
			return func(this, a_navmeshes);
		}

		bool FindFirstReachedTriangle(BSNavmesh*& a_outNavmesh, std::uint16_t& a_outTriangle)
		{
			using func_t = bool(NavmeshSearchRayCache*, BSNavmesh*&, std::uint16_t&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89190, 91661) };
			return func(this, a_outNavmesh, a_outTriangle);
		}

		bool GetTriangleForSlot(std::uint32_t a_slot, BSNavmesh*& a_outNavmesh, std::uint16_t& a_outTriangle)
		{
			using func_t = bool(NavmeshSearchRayCache*, std::uint32_t, BSNavmesh*&, std::uint16_t&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89189, 91660) };
			return func(this, a_slot, a_outNavmesh, a_outTriangle);
		}
	};
}

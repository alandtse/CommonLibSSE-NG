#include "RE/T/TESWaterSystem.h"

#include "RE/B/BSGeometry.h"

namespace RE
{
	void TESWaterSystem::AddRipple(const NiPoint3& a_pos, float a_scale)
	{
		using func_t = decltype(&TESWaterSystem::AddRipple);
		static REL::Relocation<func_t> func{ RELOCATION_ID(31410, 32217) };
		return func(this, a_pos, a_scale);
	}

	void TESWaterSystem::Enable()
	{
		using func_t = decltype(&TESWaterSystem::Enable);
		static REL::Relocation<func_t> func{ RELOCATION_ID(31406, 32213) };
		return func(this);
	}

	void TESWaterSystem::InitializeWater(BSTriShape* a_waterTri, TESWaterForm* a_form, float a_waterHeight, void* a_unk4, bool a_noDisplacement, bool a_isProcedural)
	{
		using func_t = decltype(&TESWaterSystem::InitializeWater);
		static REL::Relocation<func_t> func{ RELOCATION_ID(31388, 32179) };
		return func(this, a_waterTri, a_form, a_waterHeight, a_unk4, a_noDisplacement, a_isProcedural);
	}

	bool TESWaterSystem::RemoveGeometry(BSGeometry* a_geom)
	{
		using func_t = decltype(&TESWaterSystem::RemoveGeometry);
		static REL::Relocation<func_t> func{ RELOCATION_ID(31391, 32182) };
		return func(this, a_geom);
	}
}

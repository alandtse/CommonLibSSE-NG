#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	// members are not modelled: do not use sizeof or derive from this
	class BSPathingSearchRayCast
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathingSearchRayCast;
		inline static constexpr auto VTABLE = VTABLE_BSPathingSearchRayCast;

		virtual ~BSPathingSearchRayCast();  // 00

		std::uint32_t Initialize(const void* a_request, std::uint32_t* a_outValue)
		{
			using func_t = std::uint32_t(BSPathingSearchRayCast*, const void*, std::uint32_t*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90558, 93085) };
			return func(this, a_request, a_outValue);
		}

		bool CastSegmentInSteps(const NiPoint3* a_start, const NiPoint3* a_end)
		{
			using func_t = bool(BSPathingSearchRayCast*, const NiPoint3*, const NiPoint3*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90563, 93090) };
			return func(this, a_start, a_end);
		}

		bool CreateHavokRayQuery()
		{
			using func_t = bool(BSPathingSearchRayCast*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90561, 93088) };
			return func(this);
		}

		void PrepareHavokWorldQuery()
		{
			using func_t = void(BSPathingSearchRayCast*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90559, 93086) };
			func(this);
		}

		bool CastSegmentStep(const NiPoint3* a_start, const NiPoint3* a_end, NiPoint3* a_outHitPos)
		{
			using func_t = bool(BSPathingSearchRayCast*, const NiPoint3*, const NiPoint3*, NiPoint3*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90564, 93091) };
			return func(this, a_start, a_end, a_outHitPos);
		}
	};
}

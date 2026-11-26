#pragma once

#include "RE/B/BSPathing.h"  // BSPathingSolution
#include "RE/B/BSPathingRequest.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IPathBuilder.h"

namespace RE
{
	class ScrapHeap;

	class BSPathBuilder : public IPathBuilder
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathBuilder;
		inline static constexpr auto VTABLE = VTABLE_BSPathBuilder;

		~BSPathBuilder() override;  // 00
		void Build() override;      // 01

		bool TryFindEdgeGoalLocation(std::uint32_t a_nodeIndex, void* a_edgeRef, void* a_outLocations)
		{
			using func_t = bool(BSPathBuilder*, std::uint32_t, void*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89256, 91732) };
			return func(this, a_nodeIndex, a_edgeRef, a_outLocations);
		}

		bool FindClosestBoundaryEdgeLocation(const BSPathingLocation* a_source, const NiPoint3* a_point, BSPathingLocation* a_outLocation, bool a_flag)
		{
			using func_t = bool(BSPathBuilder*, const BSPathingLocation*, const NiPoint3*, BSPathingLocation*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89260, 91736) };
			return func(this, a_source, a_point, a_outLocation, a_flag);
		}

		// members
		BSTSmartPointer<BSPathingRequest>  request;      // 08 - refcount at +08 (BSIntrusiveRefCounted), virtual dtor
		BSTSmartPointer<BSPathingSolution> solution;     // 10 - refcount at +00, sized delete (size 0xB0)
		ScrapHeap*                         threadScrap;  // 18 - MemoryManager::GetThreadScrapHeap()
		bool                               flag20;       // 20
		std::uint8_t                       pad21[7];     // 21
	};
	STATIC_ASSERT_SIZE(BSPathBuilder, 0x28);
}

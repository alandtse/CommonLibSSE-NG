#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	// derives from AStarSearch<BSPathSmootherPOVNode, BSPathSmootherPOVLink, 12>; layout not yet reversed
	class BSPathSmootherPOVSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathSmootherPOVSearch;
		inline static constexpr auto VTABLE = VTABLE_BSPathSmootherPOVSearch;

		virtual ~BSPathSmootherPOVSearch();         // 00
		virtual void ExpandNode(void* a_node) = 0;  // 01
		virtual bool IsGoalNode(void* a_node) = 0;  // 02

		bool TryAddArcLink(const void* a_node, void* a_arg3, void* a_arg4)
		{
			using func_t = bool(BSPathSmootherPOVSearch*, const void*, void*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90490, 93007) };
			return func(this, a_node, a_arg3, a_arg4);
		}

		void ExtractPathFromGoalNode(void* a_goalNode, void* a_outEdges, void* a_outPoints)
		{
			using func_t = void(BSPathSmootherPOVSearch*, void*, void*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90502, 93019) };
			func(this, a_goalNode, a_outEdges, a_outPoints);
		}

		void ReleaseSearchState()
		{
			using func_t = void(BSPathSmootherPOVSearch*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90480, 92997) };
			func(this);
		}

		void CreateStartNode()
		{
			using func_t = void(BSPathSmootherPOVSearch*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90481, 92998) };
			func(this);
		}

		void BuildPortalVertexNodes()
		{
			using func_t = void(BSPathSmootherPOVSearch*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90482, 92999) };
			func(this);
		}

		void AddRequestObstacleCircleNodes()
		{
			using func_t = void(BSPathSmootherPOVSearch*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90484, 93001) };
			func(this);
		}

		void AddNavmeshObstacleCircleNodes()
		{
			using func_t = void(BSPathSmootherPOVSearch*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90485, 93002) };
			func(this);
		}

		void CreateGoalNode()
		{
			using func_t = void(BSPathSmootherPOVSearch*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90486, 93003) };
			func(this);
		}

		void AddStartGoalEdgeLinkNodes()
		{
			using func_t = void(BSPathSmootherPOVSearch*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90487, 93004) };
			func(this);
		}

		void EmitSmoothedPath(void* a_edgeRefs, void* a_segments)
		{
			using func_t = void(BSPathSmootherPOVSearch*, void*, void*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90488, 93005) };
			func(this, a_edgeRefs, a_segments);
		}

		bool CollectEdgesInsideObstacleCircles()
		{
			using func_t = bool(BSPathSmootherPOVSearch*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90489, 93006) };
			return func(this);
		}

		bool EvaluateSegmentObstaclePenalty(const std::int32_t* a_nodeA, const std::int32_t* a_nodeB, const NiPoint3* a_p0, const NiPoint3* a_p1, float* a_outPenalty)
		{
			using func_t = bool(BSPathSmootherPOVSearch*, const std::int32_t*, const std::int32_t*, const NiPoint3*, const NiPoint3*, float*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90492, 93009) };
			return func(this, a_nodeA, a_nodeB, a_p0, a_p1, a_outPenalty);
		}

		void AddPortalCornerNode(void* a_portals, std::uint32_t a_index, bool a_isRight)
		{
			using func_t = void(BSPathSmootherPOVSearch*, void*, std::uint32_t, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(90483, 93000) };
			func(this, a_portals, a_index, a_isRight);
		}
	};
}

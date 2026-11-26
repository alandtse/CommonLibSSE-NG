#pragma once

namespace RE
{
	// layout not yet reversed
	class TrianglePathWaterAndLedgeSplitter
	{
	public:
		inline static constexpr auto RTTI = RTTI_TrianglePathWaterAndLedgeSplitter;
		inline static constexpr auto VTABLE = VTABLE_TrianglePathWaterAndLedgeSplitter;

		virtual ~TrianglePathWaterAndLedgeSplitter();  // 00

		// add
		virtual bool SplitAtEdge(const void* a_fromTriangle, const void* a_edge, void* a_toTriangle, void* a_arg4, void* a_arg5) = 0;  // 01
		virtual bool CreateRayValidatorAndNodeGenerator(void* a_request, void* a_arg3, void** a_outRayValidator, void** a_arg5) = 0;   // 02
	};
}

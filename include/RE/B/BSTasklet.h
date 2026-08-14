#pragma once

namespace RE
{
	// Minimal polymorphic base for the engine's async job/task objects (e.g. CellMopp, which
	// builds landscape collision on a background thread). Its own destructor makes no base-class
	// call, so it has no meaningful polymorphic base of its own.
	class BSTasklet
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSTasklet;
		inline static constexpr auto VTABLE = VTABLE_BSTasklet;

		virtual ~BSTasklet() = default;  // 00
	};
	static_assert(sizeof(BSTasklet) == 0x8);
}

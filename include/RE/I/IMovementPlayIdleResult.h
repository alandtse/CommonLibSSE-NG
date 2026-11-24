#pragma once

namespace RE
{
	struct IMovementPlayIdleResult
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementPlayIdleResult;
		inline static constexpr auto VTABLE = VTABLE_IMovementPlayIdleResult;

		virtual void Unk_00(void) = 0;  // 00
		virtual void Unk_01(void) = 0;  // 01
		virtual void AddRef() = 0;      // 02
		virtual void Release() = 0;     // 03
	};
	static_assert(sizeof(IMovementPlayIdleResult) == 0x8);
}

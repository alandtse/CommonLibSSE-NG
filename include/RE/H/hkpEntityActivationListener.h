#pragma once

namespace RE
{
	class hkpEntityActivationListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpEntityActivationListener;
		inline static constexpr auto VTABLE = VTABLE_hkpEntityActivationListener;

		virtual ~hkpEntityActivationListener();  // 00

		// add
		virtual void Unk_01(void);  // 01
		virtual void Unk_02(void);  // 02
	};
	static_assert(sizeof(hkpEntityActivationListener) == 0x8);
}

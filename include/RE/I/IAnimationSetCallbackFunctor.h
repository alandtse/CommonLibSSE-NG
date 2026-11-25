#pragma once

namespace RE
{
	class IAnimationSetCallbackFunctor
	{
	public:
		inline static constexpr auto RTTI = RTTI_IAnimationSetCallbackFunctor;
		inline static constexpr auto VTABLE = VTABLE_IAnimationSetCallbackFunctor;

		virtual ~IAnimationSetCallbackFunctor();  // 00

		// add
		virtual void OnAnimationSetLoaded(void* a_unused, void* a_animations);  // 01 - receives the loaded BSTArray of hkx handles
	};
	static_assert(sizeof(IAnimationSetCallbackFunctor) == 0x8);
}

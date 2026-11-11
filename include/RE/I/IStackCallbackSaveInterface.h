#pragma once

namespace RE
{
	namespace BSScript
	{
		class IStackCallbackSaveInterface
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSScript__IStackCallbackSaveInterface;
			inline static constexpr auto VTABLE = VTABLE_BSScript__IStackCallbackSaveInterface;

			virtual ~IStackCallbackSaveInterface();  // 00

			// add
			virtual bool SaveCallback(BSStorage* a_storage, BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;                 // 01
			virtual bool LoadCallback(BSStorage* a_storage, bool* a_ok, BSTSmartPointer<IStackCallbackFunctor>& a_outCallback) = 0;  // 02
		};
		static_assert(sizeof(IStackCallbackSaveInterface) == 0x8);
	}
}

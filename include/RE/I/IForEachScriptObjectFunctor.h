#pragma once

#include "RE/O/Object.h"

namespace RE
{
	namespace BSScript
	{
		class IForEachScriptObjectFunctor
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSScript__IForEachScriptObjectFunctor;
			inline static constexpr auto VTABLE = VTABLE_BSScript__IForEachScriptObjectFunctor;

			enum ForEachResult
			{
				kStop = 0,
				kContinue = 1,
			};

			virtual ~IForEachScriptObjectFunctor();  // 00

			// add
			virtual ForEachResult Visit(Object*) = 0;  // 01
		};

		static_assert(sizeof(IForEachScriptObjectFunctor) == 0x8);
	}
}
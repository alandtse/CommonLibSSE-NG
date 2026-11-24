#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"

namespace RE
{
	class BSPathingStreamRead;
	class BSPathingStreamWrite;

	class IMovementParameters : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementParameters;
		inline static constexpr auto VTABLE = VTABLE_IMovementParameters;

		virtual ~IMovementParameters();  // 00

		// add
		virtual float GetParam10() = 0;                              // 01
		virtual float GetParam14() = 0;                              // 02
		virtual float GetParam18() = 0;                              // 03
		virtual float GetParam20() = 0;                              // 04
		virtual float GetParam1C() = 0;                              // 05
		virtual void  Unk_06(void) = 0;                              // 06
		virtual void  SaveGame(BSPathingStreamWrite& a_stream) = 0;  // 07
		virtual void  LoadGame(BSPathingStreamRead& a_stream) = 0;   // 08
	};
	static_assert(sizeof(IMovementParameters) == 0x10);
}

#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"

namespace RE
{
	class MovementMessage : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessage;
		inline static constexpr auto VTABLE = VTABLE_MovementMessage;

		virtual ~MovementMessage();  // 00

		// add
		virtual std::uint32_t GetType() const;  // 01
		virtual void          Unk_02(void);     // 02 - SaveGame on PathEvent
		virtual void          Unk_03(void);     // 03 - LoadGame on PathEvent
		virtual void          Unk_04(void);     // 04
		virtual std::uint32_t Unk_05(void);     // 05
	};
	static_assert(sizeof(MovementMessage) == 0x10);
}

#pragma once

#include "RE/M/MovementMessage.h"

namespace RE
{
	class MovementMessageSetStaticPath : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageSetStaticPath;
		inline static constexpr auto VTABLE = VTABLE_MovementMessageSetStaticPath;

		~MovementMessageSetStaticPath() override;  // 00

		// members
		bool         staticPath;  // 10
		std::uint8_t pad11[7];    // 11
	};
	static_assert(sizeof(MovementMessageSetStaticPath) == 0x18);
}

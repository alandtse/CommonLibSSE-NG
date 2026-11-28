#pragma once

#include "RE/M/MovementMessage.h"

namespace RE
{
	class MovementMessageFreezeDirection : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageFreezeDirection;
		inline static constexpr auto VTABLE = VTABLE_MovementMessageFreezeDirection;

		~MovementMessageFreezeDirection() override;               // 00
		void SaveGame(PathingStreamSaveGame* a_stream) override;  // 02
		void LoadGame(PathingStreamLoadGame* a_stream) override;  // 03

		// members
		std::uint32_t unk10;  // 10 - creator default 1
		std::uint32_t pad14;  // 14
	};
	static_assert(sizeof(MovementMessageFreezeDirection) == 0x18);
}

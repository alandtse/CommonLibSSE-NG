#pragma once

#include "RE/M/MovementMessage.h"

namespace RE
{
	class MovementMessageMovementTypeChange : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageMovementTypeChange;
		inline static constexpr auto VTABLE = VTABLE_MovementMessageMovementTypeChange;

		~MovementMessageMovementTypeChange() override;            // 00
		void SaveGame(PathingStreamSaveGame* a_stream) override;  // 02
		void LoadGame(PathingStreamLoadGame* a_stream) override;  // 03

		// members
		std::uint8_t typeData0[0x40];  // 10 - starts with a BSFixedString
		std::uint8_t typeData1[0x40];  // 50 - starts with a BSFixedString
	};
	static_assert(sizeof(MovementMessageMovementTypeChange) == 0x90);
}

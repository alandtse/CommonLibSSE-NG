#pragma once

#include "RE/M/MovementMessage.h"

namespace RE
{
	class MovementMessageSetStaticPath : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageSetStaticPath;
		inline static constexpr auto VTABLE = VTABLE_MovementMessageSetStaticPath;

		~MovementMessageSetStaticPath() override;                 // 00
		void SaveGame(PathingStreamSaveGame* a_stream) override;  // 02
		void LoadGame(PathingStreamLoadGame* a_stream) override;  // 03

		// members
		bool         staticPath;  // 10
		std::uint8_t pad11[7];    // 11
	};
	static_assert(sizeof(MovementMessageSetStaticPath) == 0x18);
}

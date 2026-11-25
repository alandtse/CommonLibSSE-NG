#pragma once

#include "RE/B/BSPathingLocation.h"
#include "RE/M/MovementMessage.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class MovementMessageWarpToLocation : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageWarpToLocation;
		inline static constexpr auto VTABLE = VTABLE_MovementMessageWarpToLocation;

		~MovementMessageWarpToLocation() override;                // 00
		void SaveGame(PathingStreamSaveGame* a_stream) override;  // 02
		void LoadGame(PathingStreamLoadGame* a_stream) override;  // 03

		// members
		BSPathingLocation location;   // 10
		NiPoint3          direction;  // 40
		std::uint32_t     pad4C;      // 4C
	};
	static_assert(sizeof(MovementMessageWarpToLocation) == 0x50);
}

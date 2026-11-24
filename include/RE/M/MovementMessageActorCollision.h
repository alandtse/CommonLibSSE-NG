#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/M/MovementMessage.h"

namespace RE
{
	class MovementMessageActorCollision : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageActorCollision;
		inline static constexpr auto VTABLE = VTABLE_MovementMessageActorCollision;

		~MovementMessageActorCollision() override;  // 00

		// members
		ActorHandle   actor;  // 10
		std::uint32_t pad14;  // 14
	};
	static_assert(sizeof(MovementMessageActorCollision) == 0x18);
}

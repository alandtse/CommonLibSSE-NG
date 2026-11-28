#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"

namespace RE
{
	class PathingStreamLoadGame;
	class PathingStreamSaveGame;

	class MovementMessage : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessage;
		inline static constexpr auto VTABLE = VTABLE_MovementMessage;

		virtual ~MovementMessage();  // 00

		// add
		virtual std::uint32_t GetType() const;                            // 01
		virtual void          SaveGame(PathingStreamSaveGame* a_stream);  // 02
		virtual void          LoadGame(PathingStreamLoadGame* a_stream);  // 03
		virtual void          Unk_04(void);                               // 04
		virtual std::uint32_t Unk_05(void);                               // 05
	};
	static_assert(sizeof(MovementMessage) == 0x10);
}

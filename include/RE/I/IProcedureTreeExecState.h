#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class BGSLoadFormBuffer;
	class BGSLoadGameBuffer;
	class BGSSaveGameBuffer;

	// Base interface for per-node AI procedure execution state.
	// Concrete subtypes: BGSProcedureTreeOneChildExecState (branch/sequence nodes),
	// BGSProcedureXxxExecState (leaf procedures via BGSTypedItem<T, IProcedureTreeExecState>).
	class IProcedureTreeExecState
	{
	public:
		inline static constexpr auto RTTI = RTTI_IProcedureTreeExecState;
		inline static constexpr auto VTABLE = VTABLE_IProcedureTreeExecState;

		virtual ~IProcedureTreeExecState() = default;  // 00

		// add
		virtual void           Unk_01(void) = 0;                                              // 01
		virtual void           RecycleChildren() = 0;                                         // 02
		virtual void           Unk_03(void) = 0;                                              // 03
		virtual void           Unk_04(void) = 0;                                              // 04
		virtual BSFixedString* GetPoolKey() = 0;                                              // 05 - used by ValidateExecState
		virtual void           SaveGame(BGSSaveGameBuffer* a_buffer, void* a_forwarded) = 0;  // 06
		virtual void           LoadGame(BGSLoadGameBuffer* a_buffer, void* a_forwarded);      // 07
		virtual void           InitLoadGame(BGSLoadFormBuffer* a_buffer);                     // 08
	};
	static_assert(sizeof(IProcedureTreeExecState) == 0x8);
}

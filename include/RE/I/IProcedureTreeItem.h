#pragma once

#include "RE/I/IProcedureTreeExecState.h"

namespace RE
{
	class TESFile;

	class IProcedureTreeItem
	{
	public:
		inline static constexpr auto RTTI = RTTI_IProcedureTreeItem;
		inline static constexpr auto VTABLE = VTABLE_IProcedureTreeItem;

		// Opaque context passed to Execute(). Anonymous struct, no RTTI.
		struct ExecStateContext
		{
			void*                    context;    // 00 - plain struct: Actor* at 00, bool interruptFlag at 21, exec-state manager at 28 (vtable[1] = SetActiveProcedure)
			IProcedureTreeExecState* nodeState;  // 08 - node-specific state (e.g. BGSProcedureTreeOneChildExecState)
		};
		static_assert(sizeof(ExecStateContext) == 0x10);

		virtual ~IProcedureTreeItem();  // 00

		// add
		virtual void Unk_01(void) = 0;                            // 01
		virtual void Unk_02(void) = 0;                            // 02
		virtual void Load(TESFile* a_mod) = 0;                    // 03
		virtual void Execute(ExecStateContext* a_execState) = 0;  // 04
		virtual void Unk_05(void) = 0;                            // 05
		virtual void Unk_06(void) = 0;                            // 06
		virtual void Unk_07(void) = 0;                            // 07
		virtual void Unk_08(void);                                // 08
		virtual void Unk_09(void);                                // 09
		virtual void Unk_0A(void) = 0;                            // 0A
		virtual void Unk_0B(void) = 0;                            // 0B
		virtual void Unk_0C(void) = 0;                            // 0C
		virtual void Unk_0D(void) = 0;                            // 0D
		virtual void Unk_0E(void) = 0;                            // 0E
		virtual void Unk_0F(void) = 0;                            // 0F
		virtual void Unk_10(void) = 0;                            // 10
	};
	static_assert(sizeof(IProcedureTreeItem) == 0x8);
}

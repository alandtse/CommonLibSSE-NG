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

		// Opaque context passed to Execute(). Binary layout (anonymous struct, no RTTI):
		//   [0x00] void* context  — plain struct: Actor* at [0x00], bool interruptFlag at [0x21],
		//                           exec-state manager object at [0x28] (vtable[1] = SetActiveProcedure)
		//   [0x08] IProcedureTreeExecState* nodeState — node-specific state (e.g. BGSProcedureTreeOneChildExecState)
		struct ExecStateContext
		{
			void*                    context;    // [0x00]
			IProcedureTreeExecState* nodeState;  // [0x08]
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

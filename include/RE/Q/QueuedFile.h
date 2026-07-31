#pragma once

#include "RE/I/IOTask.h"

namespace RE
{
	// Adds no new POD fields beyond IOTask's own tail --
	// sizeof(QueuedFile) == sizeof(IOTask) in SE/AE/VR alike.
	class QueuedFile : public IOTask
	{
	public:
		inline static constexpr auto RTTI = RTTI_QueuedFile;
		inline static constexpr auto VTABLE = VTABLE_QueuedFile;

		// Slot 0 is the deleting-destructor wrapper, RELOCATION_ID(74013, 75755); it calls the
		// non-deleting body RELOCATION_ID(73995, 75734), which derived destructors also call directly.
		~QueuedFile() override;  // 00

		// add (trivial stubs, shared/folded with unrelated classes' vtables)
		virtual void Unk_09() { return; }  // 09
		virtual void Unk_10() { return; }  // 10
		virtual void Unk_11() { return; }  // 11

		// IOTask::Unk_08 is overridden here as NotifyChildrenAndFinalize(std::uint32_t),
		// RELOCATION_ID(74003, 75742); reached only through the vtable.

		// Appends a_child to the children array, allocating the child-tracking object on first use.
		void AddChild(QueuedFile* a_child)
		{
			using func_t = decltype(&QueuedFile::AddChild);
			static REL::Relocation<func_t> func{ RELOCATION_ID(74005, 75744) };
			return func(this, a_child);
		}

		// Transitions state 0 or 1 to 2, invokes BSTask slot 1, sets state 3,
		// then runs ProcessStateMachine.
		void BeginProcessing()
		{
			using func_t = decltype(&QueuedFile::BeginProcessing);
			static REL::Relocation<func_t> func{ RELOCATION_ID(73999, 75738) };
			return func(this);
		}

		// Size of the children array, or 0 when the child-tracking object was never allocated.
		std::uint32_t GetTotalChildrenCount() const
		{
			using func_t = decltype(&QueuedFile::GetTotalChildrenCount);
			static REL::Relocation<func_t> func{ RELOCATION_ID(73996, 75735) };
			return func(this);
		}

		// Advances the task state (0 to 5, or 3 to 4 to 5 to 6). Bails without transitioning
		// while the child-tracking object reports fewer finished children than it holds.
		void ProcessStateMachine()
		{
			using func_t = decltype(&QueuedFile::ProcessStateMachine);
			static REL::Relocation<func_t> func{ RELOCATION_ID(74000, 75739) };
			return func(this);
		}
	};
}

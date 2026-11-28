#include "RE/M/MovementControllerAI.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	bool MovementControllerAI::Unk_09()
	{
		return REL::RelocateVirtual<decltype(&MovementControllerAI::Unk_09)>(0x09, 0x0A, this);
	}

	void MovementArbiter::Kill()
	{
		REL::RelocateVirtual<decltype(&MovementArbiter::Kill)>(0x0A, 0x0B, this);
	}

	void MovementArbiter::Deactivate()
	{
		REL::RelocateVirtual<decltype(&MovementArbiter::Deactivate)>(0x0B, 0x0C, this);
	}

	void MovementArbiter::UnregisterWithController()
	{
		REL::RelocateVirtual<decltype(&MovementArbiter::UnregisterWithController)>(0x0C, 0x0D, this);
	}

	void MovementArbiter::SaveGame(BSPathingStreamWrite& a_arg1)
	{
		REL::RelocateVirtual<decltype(&MovementArbiter::SaveGame)>(0x0D, 0x0E, this, a_arg1);
	}

	void MovementArbiter::LoadGame(BSPathingStreamRead& a_arg1)
	{
		REL::RelocateVirtual<decltype(&MovementArbiter::LoadGame)>(0x0E, 0x0F, this, a_arg1);
	}

	bool MovementArbiter::AddAgent(const BSTSmartPointer<MovementAgent>& a_arg1)
	{
		return REL::RelocateVirtual<decltype(&MovementArbiter::AddAgent)>(0x0F, 0x10, this, a_arg1);
	}

	bool MovementArbiter::RemoveAgent(const BSTSmartPointer<MovementAgent>& a_arg1)
	{
		return REL::RelocateVirtual<decltype(&MovementArbiter::RemoveAgent)>(0x10, 0x11, this, a_arg1);
	}

	void MovementArbiter::RemoveAllAgents()
	{
		REL::RelocateVirtual<decltype(&MovementArbiter::RemoveAllAgents)>(0x11, 0x12, this);
	}
#endif
}

#include "RE/M/MovementControllerNPC.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void MovementControllerNPC::SetSprinting(bool a_sprinting)
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::SetSprinting)>(0x0A, 0x0B, this, a_sprinting);
	}

	bool MovementControllerNPC::GetSprinting()
	{
		return REL::RelocateVirtual<decltype(&MovementControllerNPC::GetSprinting)>(0x0B, 0x0C, this);
	}

	void MovementControllerNPC::SetAIDriven()
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::SetAIDriven)>(0x0C, 0x0D, this);
	}

	void MovementControllerNPC::SetControlsDriven()
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::SetControlsDriven)>(0x0D, 0x0E, this);
	}

	bool MovementControllerNPC::GetAIDriven()
	{
		return REL::RelocateVirtual<decltype(&MovementControllerNPC::GetAIDriven)>(0x0E, 0x0F, this);
	}

	bool MovementControllerNPC::GetControlsDriven()
	{
		return REL::RelocateVirtual<decltype(&MovementControllerNPC::GetControlsDriven)>(0x0F, 0x10, this);
	}

	void MovementControllerNPC::SetMovementMode6Virtual()
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::SetMovementMode6Virtual)>(0x10, 0x11, this);
	}

	void MovementControllerNPC::SetFlightPathing(bool a_value)
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::SetFlightPathing)>(0x11, 0x12, this, a_value);
	}

	void MovementControllerNPC::SaveGame(void* a_buffer)
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::SaveGame)>(0x12, 0x13, this, a_buffer);
	}

	void MovementControllerNPC::LoadGame(void* a_buffer)
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::LoadGame)>(0x13, 0x14, this, a_buffer);
	}

	void MovementControllerNPC::OnMessageDispatched(MovementMessage* a_message)
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::OnMessageDispatched)>(0x14, 0x15, this, a_message);
	}
#endif
}

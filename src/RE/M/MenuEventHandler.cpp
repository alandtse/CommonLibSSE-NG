#include "RE/M/MenuEventHandler.h"

// Other builds define these as non-virtual RelocateVirtual wrappers in the header.
#ifdef EXCLUSIVE_SKYRIM_VR
namespace RE
{
	bool MenuEventHandler::ProcessKinect(KinectEvent*)
	{
		return false;
	}

	bool MenuEventHandler::ProcessThumbstick(ThumbstickEvent*)
	{
		return false;
	}

	bool MenuEventHandler::ProcessMouseMove(MouseMoveEvent*)
	{
		return false;
	}

	bool MenuEventHandler::ProcessButton(RE::ButtonEvent*)
	{
		return false;
	}
}
#endif

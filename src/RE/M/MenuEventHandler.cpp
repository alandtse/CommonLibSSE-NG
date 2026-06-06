#include "RE/M/MenuEventHandler.h"

// In SKYRIM_CROSS_VR these are non-virtual RelocateVirtual wrappers defined inline in the
// header (the VR vtable shifts these slots), so they must not be redefined here.
#ifndef SKYRIM_CROSS_VR
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

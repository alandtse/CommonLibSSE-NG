#include "RE/M/MenuEventHandler.h"

// Every non-VR-exclusive build (SE-only, AE-only, flat, and SKYRIM_CROSS_VR alike)
// defines these as non-virtual RelocateVirtual wrappers inline in the header, so
// they must not be redefined here -- only EXCLUSIVE_SKYRIM_VR still declares them
// as real virtuals with no inline body.
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

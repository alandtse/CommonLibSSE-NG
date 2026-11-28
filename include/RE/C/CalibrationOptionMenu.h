#pragma once
#ifdef ENABLE_SKYRIM_VR
#	include "RE/I/IMenu.h"
#	include "RE/M/MenuEventHandler.h"
#	include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class CalibrationOptionMenu :
#	ifdef EXCLUSIVE_SKYRIM_VR
		public IMenu,            // 00
		public MenuEventHandler  // 40
#	else
		public IMenu  // 00
#	endif
	{
	public:
		inline static constexpr auto RTTI = RTTI_CalibrationOptionMenu;

#	ifdef EXCLUSIVE_SKYRIM_VR
		using MenuEventHandler::operator delete;
#	endif

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

#	ifdef EXCLUSIVE_SKYRIM_VR
		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#	endif

		VR_ONLY_POINTER_ACCESSOR(MenuEventHandler, AsMenuEventHandler, 0x40);

		struct RUNTIME_DATA
		{
#	define RUNTIME_DATA_CONTENT                                               \
		bool unk50;    /* 50 - Set in ProcessMessage, cleared in CanProcess */ \
		char pad51[7]; /* 51 */

			RUNTIME_DATA_CONTENT
		};

		VR_ONLY_POINTER_ACCESSOR(RUNTIME_DATA, GetRuntimeData, 0x50);
		// members
#	ifdef EXCLUSIVE_SKYRIM_VR
		RUNTIME_DATA_CONTENT;  // 50
#	endif
	};
#	ifdef EXCLUSIVE_SKYRIM_VR
	static_assert(sizeof(CalibrationOptionMenu) == 0x58);
#	endif
}
#	undef RUNTIME_DATA_CONTENT
#endif

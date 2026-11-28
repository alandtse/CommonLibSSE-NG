#pragma once

#ifdef ENABLE_SKYRIM_VR

#	include "RE/N/NiSmartPointer.h"
#	include "RE/W/WorldSpaceMenu.h"
#	include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class EnemyHealth;
	class TESObjectREFR;

	class WSEnemyMeters :
		public WorldSpaceMenu  // 00
	{
	public:
		inline static constexpr auto      RTTI = RTTI_WSEnemyMeters;
		inline static constexpr auto      VTABLE = VTABLE_WSEnemyMeters;
		constexpr static std::string_view MENU_NAME = "WSEnemyMeters";

		struct RUNTIME_DATA
		{
#	define RUNTIME_DATA_CONTENT                       \
		EnemyHealth*             enemyHealth; /* 58 */ \
		NiPointer<TESObjectREFR> target;      /* 60 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x10);

		~WSEnemyMeters() override;  // 00

		// override
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04
		void               SetupMenuNode() override;                         // 0B
		NiNode*            GetMenuParentNode() override;                     // 0C
		void               SetTransform() override;                          // 0D

		VR_ONLY_POINTER_ACCESSOR(RUNTIME_DATA, GetRuntimeData, 0x58);
		// members
#	ifdef EXCLUSIVE_SKYRIM_VR
		RUNTIME_DATA_CONTENT;  // 58
#	endif
	};
#	ifdef EXCLUSIVE_SKYRIM_VR
	static_assert(sizeof(WSEnemyMeters) == 0x68);
#	endif
}
#	undef RUNTIME_DATA_CONTENT

#endif

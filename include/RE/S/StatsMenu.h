#pragma once

#include "RE/A/ActorValues.h"
#include "RE/B/BSResourceHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"
#include "RE/N/NiNode.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/W/WorldSpaceMenu.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSEffectShaderProperty;
	class BSFadeNode;
	class BSScaleformMovieLoadTask;
	class MenuOpenCloseEvent;
	class NiCamera;
	class NiControllerManager;
	class NiControllerSequence;
	class StatsMenuPerks;
	class StatsMenuSkillRing;
	class StatsNode;

	// menuDepth = 3
	// flags = kPausesGame | kUsesMenuContext | kDisablePauseMenu | kRequiresUpdate | kCustomRendering
	// kUsesCursor if gamepad disabled
	// context = kStats
	class StatsMenu :
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		public IMenu,            // 000
		public MenuEventHandler  // 030
#elif defined(EXCLUSIVE_SKYRIM_VR)
		public WorldSpaceMenu,                   // 000
		public MenuEventHandler,                 // 058
		public BSTEventSink<MenuOpenCloseEvent>  // 068
#else
		public IMenu  // 000
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_StatsMenu;
		inline static constexpr auto      VTABLE = VTABLE_StatsMenu;
		constexpr static std::string_view MENU_NAME = "StatsMenu";

		enum class MenuState : std::uint32_t
		{
			kNormal = 0,
			kZoomed = 1,
			kFadeIn = 2,
			kFadeOut = 3
		};

		enum
		{
			kTotalTrees = 18,
			kTotalVRModels = 6
		};

		struct Models
		{
			enum Model : std::uint32_t
			{
				kSkydome,
				kStars,
				kLines,
				kTotal
			};
		};
		using Model = Models::Model;

		struct UnkData
		{
		public:
			enum class State
			{
				kResting = 0,
				kEntering = 1,
				kExiting = 2
			};

			// members
			BSEffectShaderProperty*            unk00;  // 00
			REX::EnumSet<State, std::uint32_t> state;  // 08
			std::uint32_t                      unk0C;  // 0C
		};
		static_assert(sizeof(UnkData) == 0x10);

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                                               \
	NiPointer<NiCamera>                    camera;                      /* 040 */                                          \
	float                                  horizontalVelocity;          /* 048 */                                          \
	std::uint32_t                          unk04C;                      /* 04C */                                          \
	BSTArray<ActorValue>                   skillTrees;                  /* 050 */                                          \
	ModelDBHandle                          modelHandles[Model::kTotal]; /* 068 */                                          \
	BSFadeNode*                            skydomeNode;                 /* 080 */                                          \
	BSFadeNode*                            starsNode;                   /* 088 */                                          \
	BSFadeNode*                            linesNode;                   /* 090 */                                          \
	UnkData                                unk098[kTotalTrees];         /* 098 */                                          \
	REX::EnumSet<MenuState, std::uint32_t> menuState;                   /* 1B8 */                                          \
	bool                                   scrolling;                   /* 1BC */                                          \
	std::uint8_t                           unk1BD;                      /* 1BD */                                          \
	std::uint16_t                          unk1BE;                      /* 1BE */                                          \
	std::uint32_t                          selectedTree;                /* 1C0 */                                          \
	std::uint32_t                          unk1C4;                      /* 1C4 */                                          \
	StatsNode*                             unk1C8;                      /* 1C8 */                                          \
	std::uint32_t                          unk1D0;                      /* 1D0 */                                          \
	NiPoint3                               unk1D4;                      /* 1D4 */                                          \
	std::uint64_t                          unk1E0;                      /* 1E0 */                                          \
	std::uint32_t                          unk1E8;                      /* 1E8 */                                          \
	NiPoint3                               skillsLookAt;                /* 1EC */                                          \
	NiPoint3                               starCameraOffset;            /* 1F8 */                                          \
	NiPoint3                               starLookAt;                  /* 204 */                                          \
	std::uint64_t                          unk210;                      /* 210 */                                          \
	std::uint64_t                          unk218;                      /* 218 */                                          \
	std::uint64_t                          unk220;                      /* 220 */                                          \
	std::uint64_t                          unk228;                      /* 228 */                                          \
	std::uint64_t                          unk230;                      /* 230 */                                          \
	std::uint64_t                          unk238;                      /* 238 */                                          \
	float                                  unk240;                      /* 240 */                                          \
	float                                  unk244;                      /* 244 */                                          \
	float                                  unk248;                      /* 248 */                                          \
	float                                  unk24C;                      /* 24C */                                          \
	float                                  unk250;                      /* 250 */                                          \
	float                                  unk254;                      /* 254 */                                          \
	float                                  unk258;                      /* 258 */                                          \
	float                                  unk25C;                      /* 25C */                                          \
	float                                  unk260;                      /* 260 */                                          \
	float                                  unk264;                      /* 264 */                                          \
	float                                  unk268;                      /* 268 */                                          \
	float                                  unk26C;                      /* 26C */                                          \
	float                                  unk270;                      /* 270 */                                          \
	float                                  unk274;                      /* 274 */                                          \
	std::uint32_t                          unk278;                      /* 278 */                                          \
	float                                  unk27C;                      /* 27C */                                          \
	float                                  horizontalAcceleration;      /* 280 */                                          \
	std::uint32_t                          unk284;                      /* 284 */                                          \
	NiNode*                                cameraPosition;              /* 288 */                                          \
	NiControllerSequence*                  cameraIntro;                 /* 290 */                                          \
	NiControllerSequence*                  cameraOutro;                 /* 298 */                                          \
	NiControllerSequence*                  idle;                        /* 2A0 */                                          \
	NiControllerManager*                   skydomeNodeController;       /* 2A8 */                                          \
	ImageSpaceModifierInstanceForm*        unk2B0;                      /* 2B0 - SkillMenuTransition */                    \
	ImageSpaceModifierInstanceForm*        unk2B8;                      /* 2B8 - SkillMenuIdle */                          \
	BSTArray<StatsNode*>                   unk2C0;                      /* 2C0 */                                          \
	BSTArray<GFxValue>                     unk2D8;                      /* 2D8 */                                          \
	BSScaleformMovieLoadTask*              unk2F0;                      /* 2F0 */                                          \
	GFxValue                               beastSkillHolder;            /* 2F8 - StatsMenuBaseInstance.BeastSkillHolder */ \
	std::uint32_t                          numSelectableTrees;          /* 310 */                                          \
	float                                  screenHeight;                /* 314 */                                          \
	float                                  screenWidth;                 /* 318 */                                          \
	std::uint32_t                          flags;                       /* 31C */                                          \
	std::uint8_t                           unk320;                      /* 320 */                                          \
	std::uint8_t                           unk321;                      /* 321 */                                          \
	bool                                   fadeInTriggered;             /* 322 */                                          \
	bool                                   is3dInitialized;             /* 323 */                                          \
	std::uint32_t                          unk324;                      /* 324 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x2E8);

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT                                                    \
	std::uint32_t                          unk070;                       /* 070 */ \
	std::uint32_t                          pad074;                       /* 074 */ \
	BSTArray<ActorValue>                   skillTrees;                   /* 078 */ \
	ModelDBHandle                          modelHandles[kTotalVRModels]; /* 090 */ \
	BSFadeNode*                            skydomeNode;                  /* 0C0 */ \
	BSFadeNode*                            starsNode;                    /* 0C8 */ \
	BSFadeNode*                            linesNode;                    /* 0D0 */ \
	NiPointer<NiNode>                      questMarkerNode;              /* 0D8 */ \
	NiPointer<NiNode>                      unk0E0;                       /* 0E0 */ \
	NiPointer<NiNode>                      unk0E8;                       /* 0E8 */ \
	NiPointer<NiNode>                      statsModelFollowNode;         /* 0F0 */ \
	NiPointer<NiNode>                      statsModelFollowOffsetNode;   /* 0F8 */ \
	NiPointer<NiNode>                      skillRingMenuNode;            /* 100 */ \
	NiPointer<NiNode>                      perksMenuNode;                /* 108 */ \
	StatsMenuSkillRing*                    skillRingMenu;                /* 110 */ \
	StatsMenuPerks*                        perksMenu;                    /* 118 */ \
	UnkData                                unk098[kTotalTrees];          /* 120 */ \
	REX::EnumSet<MenuState, std::uint32_t> menuState;                    /* 240 */ \
	bool                                   scrolling;                    /* 244 */ \
	std::uint8_t                           pad245[3];                    /* 245 */ \
	std::uint32_t                          selectedTree;                 /* 248 */ \
	std::uint32_t                          pad24C;                       /* 24C */ \
	StatsNode*                             unk1C8;                       /* 250 */ \
	std::uint32_t                          unk1D0;                       /* 258 */ \
	NiPoint3                               unk1D4;                       /* 25C */ \
	NiControllerSequence*                  idle;                         /* 268 */ \
	NiControllerManager*                   skydomeNodeController;        /* 270 */ \
	BSTArray<StatsNode*>                   unk2C0;                       /* 278 */ \
	BSTArray<GFxValue>                     unk2D8;                       /* 290 */ \
	BSScaleformMovieLoadTask*              unk2F0;                       /* 2A8 */ \
	GFxValue                               beastSkillHolder;             /* 2B0 */ \
	std::uint32_t                          numSelectableTrees;           /* 2C8 */ \
	std::uint8_t                           flags0;                       /* 2CC */ \
	std::uint8_t                           flags1;                       /* 2CD */ \
	std::uint8_t                           unk2CE;                       /* 2CE */ \
	std::uint8_t                           unk2CF;                       /* 2CF */ \
	std::uint8_t                           flags3;                       /* 2D0 */ \
	std::uint8_t                           unk320;                       /* 2D1 */ \
	std::uint8_t                           unk321;                       /* 2D2 */ \
	bool                                   fadeInTriggered;              /* 2D3 */ \
	bool                                   is3dInitialized;              /* 2D4 */ \
	std::uint8_t                           unk324;                       /* 2D5 */ \
	std::uint8_t                           unk2D6[0xA];                  /* 2D6 */ \
	std::uint64_t                          unk2E0;                       /* 2E0 */ \
	bool                                   unk2E8;                       /* 2E8 */ \
	std::uint8_t                           unk2E9[0x2F];                 /* 2E9 */ \
	bool                                   unk318;                       /* 318 */ \
	std::uint8_t                           unk319[0x2F];                 /* 319 */ \
	bool                                   unk348;                       /* 348 */ \
	std::uint8_t                           unk349[0x17];                 /* 349 */ \
	bool                                   unk360;                       /* 360 */ \
	std::uint8_t                           unk361[0x17];                 /* 361 */ \
	bool                                   unk378;                       /* 378 */ \
	std::uint8_t                           unk379[0x2F];                 /* 379 */ \
	std::uint32_t                          unk3A8;                       /* 3A8 */ \
	float                                  unk3AC;                       /* 3AC */ \
	float                                  unk3B0;                       /* 3B0 */ \
	std::uint8_t                           unk3B4[0x24];                 /* 3B4 */ \
	bool                                   unk3D8;                       /* 3D8 */ \
	std::uint8_t                           unk3D9[7];                    /* 3D9 */

			VR_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x370);

		~StatsMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		void               Unk_03(void) override;                            // 03 - { unk321 = 1; }
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04
		void               PostDisplay() override;                           // 06

#ifdef EXCLUSIVE_SKYRIM_VR
		// override (WorldSpaceMenu)
		void    SetupMenuNode() override;      // 0B
		NiNode* GetMenuParentNode() override;  // 0C
		void    SetTransform() override;       // 0D

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;  // 01
#endif

		// override (MenuEventHandler)
#ifndef SKYRIM_CROSS_VR
		bool CanProcess(InputEvent* a_event) override;  // 01
#endif
#ifdef EXCLUSIVE_SKYRIM_VR
		bool ProcessVrWandTouchpadSwipe(VrWandTouchpadSwipeEvent* a_event) override;        // 02
		bool ProcessVrWandTouchpadPosition(VrWandTouchpadPositionEvent* a_event) override;  // 03
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;                          // 06
		bool ProcessButton(ButtonEvent* a_event) override;                                  // 08
#endif

#ifndef SKYRIM_CROSS_VR
		RUNTIME_CAST_ACCESSOR(MenuEventHandler, AsMenuEventHandler, 0x30, 0x58);
#endif
		VR_ONLY_POINTER_ACCESSOR(BSTEventSink<MenuOpenCloseEvent>, AsMenuOpenCloseEventSink, 0x68);

		SE_ONLY_POINTER_ACCESSOR(RUNTIME_DATA, GetRuntimeData, 0x40);
		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x70);
		// members
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		RUNTIME_DATA_CONTENT;  // 40
#elif defined(EXCLUSIVE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT;                 // 70
#endif
	};
	STATIC_ASSERT_SIZE(StatsMenu, 0x328, 0x328, 0x3E0, 0x30);
}
#undef RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT

#pragma once

#include "RE/B/BSResourceHandle.h"
#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiPoint3.h"
#include "RE/S/SimpleAnimationGraphManagerHolder.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSFadeNode;
	class BSLightingShaderProperty;
	class NiAVObject;
	class NiControllerManager;
	class NiControllerSequence;

	struct ImageSpaceBaseData;

	// menuDepth = 8
	// flags = kDisablePauseMenu | kAllowSaving | kDontHideCursorWhenTopmost
	// context = kNone
	class MistMenu :
#ifndef SKYRIM_CROSS_VR
		public IMenu,                              // 00
		public SimpleAnimationGraphManagerHolder,  // 30, 40
		public MenuEventHandler                    // 48, 58
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_MistMenu;
		inline static constexpr auto      VTABLE = VTABLE_MistMenu;
		constexpr static std::string_view MENU_NAME = "Mist Menu";

		struct Colors
		{
			enum Color
			{
				kXNeg,
				kXPos,
				kYNeg,
				kYPos,
				kZNeg,
				kZPos,

				kTotal
			};
		};

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                            \
	NiColor                         ambientColors[Colors::kTotal]; /* 058 */                            \
	std::uint32_t                   unk0A0;                        /* 0A0 */                            \
	std::uint32_t                   unk0A4;                        /* 0A4 */                            \
	std::uint64_t                   unk0A8;                        /* 0A8 */                            \
	NiPointer<NiNode>               mistModel;                     /* 0B0 - smart ptr */                \
	ModelDBHandle                   mistModelDBHandle;             /* 0B8 */                            \
	ModelDBHandle                   loadScreenModelHandle;         /* 0C0 */                            \
	NiPointer<BSFadeNode>           cameraPath;                    /* 0C8 - parent of cameraPathNode */ \
	NiPointer<NiNode>               cameraPathNode;                /* 0D0 - smart ptr */                \
	NiPointer<NiControllerSequence> cameraPathSequence;            /* 0D8 - smart ptr */                \
	NiPointer<NiControllerManager>  cameraPathController;          /* 0E0 - smart ptr */                \
	BSLightingShaderProperty*       logoShaderProperty;            /* 0E8 - default logo only */        \
	NiPointer<BSFadeNode>           loadScreenModel;               /* 0F0 */                            \
	ImageSpaceBaseData*             originalImageSpace;            /* 0F8 - imagespacedata? */          \
	float                           cameraFOV;                     /* 100 */                            \
	float                           angleZ;                        /* 104 */                            \
	float                           unk108;                        /* 108 */                            \
	float                           unk10C;                        /* 10C */                            \
	NiMatrix3                       cameraRotate;                  /* 110 */                            \
	bool                            showMist;                      /* 134 */                            \
	bool                            showLoadScreen;                /* 135 */                            \
	std::uint8_t                    unk136;                        /* 136 */                            \
	std::uint8_t                    unk137;                        /* 137 */                            \
	std::uint8_t                    unk138;                        /* 138 - initCameraPath? */          \
	std::uint8_t                    unk139;                        /* 139 - cameraPath related */       \
	bool                            leftButtonHeldDown;            /* 13A */                            \
	bool                            rightButtonHeldDown;           /* 13B */                            \
	std::uint32_t                   pad13C;                        /* 13C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0xE8);

		// VR appends deferred load-screen-model setup state past the shared RUNTIME_DATA (at +0x150): the
		// model NIF streams in asynchronously, so SetupLoadScreenModel3D stashes the InitLoadScreen3D
		// transform here and AdvanceMovie replays setup once the model lands. Absent on SE/AE (which load
		// the model synchronously). Reachable in any build via GetVRRuntimeData().
		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT                                                                             \
	std::uint8_t  unk150[0x18];            /* 150 */                                                        \
	bool          deferredSetupNeeded;     /* 168 - set when the load-screen model NIF is not yet loaded */ \
	std::uint8_t  pad169[0x3];             /* 169 */                                                        \
	float         stashedModelScale;       /* 16C */                                                        \
	NiPoint3      stashedRotateOffset;     /* 170 */                                                        \
	NiPoint3      stashedTranslateOffset;  /* 17C */                                                        \
	NiPoint3      unk188;                  /* 188 */                                                        \
	NiPoint3      unk194;                  /* 194 */                                                        \
	std::uint8_t  unk1A0;                  /* 1A0 */                                                        \
	bool          loadScreenModelReady;    /* 1A1 - set once the model is loaded and set up */              \
	bool          loadScreen3DInitialized; /* 1A2 - set after InitLoadScreen3D runs on the model */         \
	std::uint8_t  unk1A3;                  /* 1A3 */                                                        \
	std::uint32_t unk1A4;                  /* 1A4 */

			VR_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x58);

		~MistMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05
		void               PostDisplay() override;                                                // 06

		// override (MenuEventHandler)
#ifndef SKYRIM_CROSS_VR
		bool CanProcess(InputEvent* a_event) override;              // 01
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03
		bool ProcessMouseMove(MouseMoveEvent* a_event) override;    // 04
		bool ProcessButton(ButtonEvent* a_event) override;          // 05
#endif

#ifndef SKYRIM_CROSS_VR
		RUNTIME_CAST_ACCESSOR(SimpleAnimationGraphManagerHolder, AsSimpleAnimationGraphManagerHolder, 0x30, 0x40);
		RUNTIME_CAST_ACCESSOR(MenuEventHandler, AsMenuEventHandler, 0x48, 0x58);
#endif

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x58, 0x68);

		// VR-only tail accessor; returns nullptr on SE/AE. Works in every build (incl. cross-VR) since it
		// resolves the absolute VR offset rather than relying on inline members.
		[[nodiscard]] inline VR_RUNTIME_DATA* GetVRRuntimeData() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
				return &REL::RelocateMember<VR_RUNTIME_DATA>(this, 0, 0x150);
			}
			return nullptr;
		}

		[[nodiscard]] inline const VR_RUNTIME_DATA* GetVRRuntimeData() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
				return &REL::RelocateMember<VR_RUNTIME_DATA>(this, 0, 0x150);
			}
			return nullptr;
		}

		[[nodiscard]] static MistMenu* GetSingleton()
		{
			static REL::Relocation<MistMenu**> singleton{ RELOCATION_ID(519827, 406370) };
			return *singleton;
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 58, 68
#	if defined(EXCLUSIVE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT;  // 150
#	endif
#endif
	};
	STATIC_ASSERT_SIZE(MistMenu, 0x140, 0x140, 0x1A8, 0x30);
}
#undef RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT

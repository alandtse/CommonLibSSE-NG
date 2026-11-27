#pragma once

#include "RE/B/BSBloodSplatterShaderProperty.h"
#include "RE/B/BSTSingleton.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiCamera;
	class NiNode;
	class NiSourceTexture;

	class ScreenSplatter : public BSTSingletonSDM<ScreenSplatter>
	{
	public:
		static ScreenSplatter* GetSingleton()
		{
			static REL::Relocation<ScreenSplatter**> singleton{ RELOCATION_ID(514512, 400672) };
			return *singleton;
		}

		void Clear()
		{
			using func_t = decltype(&ScreenSplatter::Clear);
			static REL::Relocation<func_t> func{ RELOCATION_ID(16175, 16407) };
			return func(this);
		}

		static void InitStaticName()
		{
			using func_t = void();
			static REL::Relocation<func_t> func{ RELOCATION_ID(16169, 16401) };
			func();
		}

		static void ReleaseStaticName()
		{
			using func_t = void();
			static REL::Relocation<func_t> func{ RELOCATION_ID(16170, 16402) };
			func();
		}

		NiNode* CreateSplatterNode(std::uint16_t a_count)
		{
			using func_t = NiNode*(ScreenSplatter*, std::uint16_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(16176, 16408) };
			return func(this, a_count);
		}

		// members
		std::uint8_t               pad01;                                            // 01
		std::uint16_t              pad02;                                            // 02
		std::uint32_t              pad04;                                            // 04
		NiPointer<NiNode>          root;                                             // 08
		NiPointer<NiCamera>        camera;                                           // 10
		float                      wRadius;                                          // 18
		float                      hRadius;                                          // 1C
		bool                       enabled;                                          // 20
		bool                       pad21;                                            // 21
		std::uint16_t              pad22;                                            // 22
		std::uint32_t              uiCount;                                          // 24
		NiPointer<NiSourceTexture> textures[BSBloodSplatterShaderProperty::kTotal];  // 28
	};
	static_assert(sizeof(ScreenSplatter) == 0x40);
}

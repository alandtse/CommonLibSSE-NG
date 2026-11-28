#pragma once

#include <cstddef>
#include <cstdint>

#include "RE/B/BSShaderRenderTargets.h"
#include "RE/R/RenderTargetProperties.h"
#include "RE/R/RendererShadowState.h"

namespace RE
{
	namespace BSGraphics
	{
		class RenderTargetManager
		{
		public:
			[[nodiscard]] static RenderTargetManager* GetSingleton()
			{
				static REL::Relocation<RenderTargetManager**> singleton{ RELOCATION_ID(524970, 411451) };
				return *singleton;
			}

			void CreateCubeMapRenderTarget(RENDER_TARGET_CUBEMAP a_renderTarget, const CubeMapRenderTargetProperties& a_properties);
			void CreateDepthStencilTarget(RENDER_TARGET_DEPTHSTENCIL a_renderTarget, const DepthStencilTargetProperties& a_properties);
			void SetCurrentCubeMapRenderTarget(RENDER_TARGET_CUBEMAP a_renderTarget, SetRenderTargetMode a_mode, std::uint32_t a_faceIndex, bool a_updateViewport);
			void SetCurrentDepthStencilTarget(RENDER_TARGET_DEPTHSTENCIL a_renderTarget, SetRenderTargetMode a_mode, std::uint32_t a_slice);

#if defined(SKYRIM_CROSS_VR) || (defined(ENABLE_SKYRIM_SE) && defined(ENABLE_SKYRIM_AE))
			// Several layouts are compiled in: dispatch on the running game, not #ifdef.
			[[nodiscard]] inline RenderTargetProperties& GetRenderTargetProperties(std::uint32_t a_index) noexcept
			{
				const auto offset = a_index * REL::Relocate<std::ptrdiff_t>(0x1C, 0x1C, 0x28);
				return REL::RelocateMember<RenderTargetProperties>(this, offset, offset);
			}
			[[nodiscard]] inline DepthStencilTargetProperties& GetDepthStencilTargetProperties(std::uint32_t a_index) noexcept
			{
				const auto offset = REL::Relocate<std::ptrdiff_t>(0xC78, 0xCB0, 0x1388) + a_index * REL::Relocate<std::ptrdiff_t>(0x10, 0x10, 0x1C);
				return REL::RelocateMember<DepthStencilTargetProperties>(this, offset, offset);
			}
			[[nodiscard]] inline CubeMapRenderTargetProperties* GetCubeMapRenderTargetData() noexcept
			{
				const auto offset = REL::Relocate<std::ptrdiff_t>(0xD38, 0xD70, 0x15D4);
				return &REL::RelocateMember<CubeMapRenderTargetProperties>(this, offset, offset);
			}
#endif

			// members
#if defined(SKYRIM_CROSS_VR)
			std::byte runtimeDataPlaceholder[0xD7C];  // 000
#elif defined(ENABLE_SKYRIM_SE) && defined(ENABLE_SKYRIM_AE)
			RenderTargetProperties renderTargetData[RENDER_TARGET::kTOTAL];  // 000
			// Placeholder sized to the larger (AE) layout
			std::byte runtimeDataPlaceholder[0x104];  // C78
#elif defined(EXCLUSIVE_SKYRIM_VR)
			VRRenderTargetProperties       renderTargetData[RENDER_TARGET::kVRTOTAL];                      // 0000
			VRDepthStencilTargetProperties depthStencilTargetData[RENDER_TARGETS_DEPTHSTENCIL::kVRTOTAL];  // 1388
			CubeMapRenderTargetProperties  cubeMapRenderTargetData[RENDER_TARGETS_CUBEMAP::kTOTAL];        // 15D4
#else
			RenderTargetProperties        renderTargetData[RENDER_TARGET::kTOTAL];                      // 000
#	ifdef ENABLE_SKYRIM_AE
			std::byte                     padC78[0x38];                                                 // C78
#	endif
			DepthStencilTargetProperties  depthStencilTargetData[RENDER_TARGETS_DEPTHSTENCIL::kTOTAL];  // C78, CB0
			CubeMapRenderTargetProperties cubeMapRenderTargetData[RENDER_TARGETS_CUBEMAP::kTOTAL];      // D38, D70
#endif
		};

#if defined(EXCLUSIVE_SKYRIM_VR)
		static_assert(sizeof(RenderTargetManager) == 0x15E0);
#elif defined(SKYRIM_CROSS_VR) || defined(ENABLE_SKYRIM_AE)
		static_assert(sizeof(RenderTargetManager) == 0xD7C);
#else
		static_assert(sizeof(RenderTargetManager) == 0xD44);
#endif
	}
}

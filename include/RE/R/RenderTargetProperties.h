#pragma once

#include "RE/T/TextureFormat.h"

namespace RE
{
	namespace BSGraphics
	{
		struct RenderTargetProperties
		{
			std::uint32_t                       width;                   // 00
			std::uint32_t                       height;                  // 04
			REX::EnumSet<Format, std::uint32_t> format;                  // 08
			bool                                copyable;                // 0C
			bool                                supportUnorderedAccess;  // 0D
			bool                                allowMipGeneration;      // 0E
			bool                                unk0F;                   // 0F
			std::int32_t                        mipLevel;                // 10
			std::uint32_t                       textureTarget;           // 14
			std::uint32_t                       unk18;                   // 18
		};
		static_assert(sizeof(RenderTargetProperties) == 0x1C);

		struct VRRenderTargetProperties : public RenderTargetProperties
		{
			std::byte unk1C[0xC];  // 1C
		};
		static_assert(sizeof(VRRenderTargetProperties) == 0x28);

		struct DepthStencilTargetProperties
		{
			std::uint32_t width;           // 00
			std::uint32_t height;          // 04
			std::uint32_t arraySize;       // 08
			bool          unk0C;           // 0C
			bool          stencil;         // 0D
			bool          use16BitsDepth;  // 0E
		};
		static_assert(sizeof(DepthStencilTargetProperties) == 0x10);

		struct VRDepthStencilTargetProperties : public DepthStencilTargetProperties
		{
			std::byte unk10[0xC];  // 10
		};
		static_assert(sizeof(VRDepthStencilTargetProperties) == 0x1C);

		struct CubeMapRenderTargetProperties
		{
			std::uint32_t                       width;   // 00
			std::uint32_t                       height;  // 04
			REX::EnumSet<Format, std::uint32_t> format;  // 08
		};
		static_assert(sizeof(CubeMapRenderTargetProperties) == 0xC);
	}
}

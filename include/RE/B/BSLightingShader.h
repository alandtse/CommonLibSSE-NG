#pragma once

#include "RE/B/BSShader.h"

namespace RE
{
	class BSLightingShader : public BSShader
	{
	public:
		// Bit flags packed into the lower 24 bits of the raw technique ID.
		// Source: Nukem9/skyrimse-test BSLightingShader.h; confirmed against aers/Skyrim-SE-Shader-Tools HLSL defines.
		enum class TechniqueFlag : std::uint32_t
		{
			kVC                  = 1 << 0,
			kSkinned             = 1 << 1,
			kModelSpaceNormals   = 1 << 2,
			kLightCount1         = 1 << 3,
			kLightCount2         = 1 << 4,
			kLightCount3         = 1 << 5,
			kLightCount4         = 1 << 6,
			kLightCount5         = 1 << 7,
			kLightCount6         = 1 << 8,
			kSpecular            = 1 << 9,
			kSoftLighting        = 1 << 10,
			kRimLighting         = 1 << 11,
			kBackLighting        = 1 << 12,
			kShadowDir           = 1 << 13,
			kDefShadow           = 1 << 14,
			kProjectedUV         = 1 << 15,
			kAnisoLighting       = 1 << 16,
			kAmbientSpecular     = 1 << 17,
			kWorldMap            = 1 << 18,
			kBaseObjectIsSnow    = 1 << 19,
			kDoAlphaTest         = 1 << 20,
			kSnow                = 1 << 21,
			kCharacterLight      = 1 << 22,
			kAdditionalAlphaMask = 1 << 23,
		};

		// Base technique ID for BSLightingShader: (0x48 << 24) | always-on flags (VC, MSN, LightCount1, LightCount3).
		// Subtracting this from a raw technique ID isolates the material feature in bits [29:24].
		// Not named in reference implementations (Nukem9/skyrimse-test); decomposed here for clarity.
		static constexpr std::uint32_t kTechniqueIDBase =
			(0x48u << 24) |
			static_cast<std::uint32_t>(TechniqueFlag::kVC) |
			static_cast<std::uint32_t>(TechniqueFlag::kModelSpaceNormals) |
			static_cast<std::uint32_t>(TechniqueFlag::kLightCount1) |
			static_cast<std::uint32_t>(TechniqueFlag::kLightCount3);

		uint32_t unk90;                // 90
		uint32_t currentRawTechnique;  // 94
		uint64_t unk98;                // 98
		uint64_t unkA0;                // A0
		uint64_t unkA8;                // A8
		uint64_t unkB0;                // B0
		uint64_t unkB8;                // B8
		uint64_t unkC0;                // C0
		uint64_t unkC8;                // C8
		uint64_t unkD0;                // D0
		uint64_t unkD8;                // D8
		uint64_t unkE0;                // E0
		uint64_t unkE8;                // E8
		uint64_t unkF0;                // F0
	};
	static_assert(sizeof(BSLightingShader) == 0xF8);
}

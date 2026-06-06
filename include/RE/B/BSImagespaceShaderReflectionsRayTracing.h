#pragma once

#include "RE/B/BSImagespaceShader.h"

namespace RE
{
	class BSImagespaceShaderReflectionsRayTracing : public BSImagespaceShader
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSImagespaceShaderReflectionsRayTracing;
		inline static constexpr auto VTABLE = VTABLE_BSImagespaceShaderReflectionsRayTracing;

		~BSImagespaceShaderReflectionsRayTracing() override;  // 00

		// override (BSImagespaceShader)
		// GetShaderMacros is shifted by VR's FakeDispatchComputeShader insertion in the
		// BSImagespaceShader base (flat 0x0D -> VR 0x0E), mirroring BSImagespaceShader's
		// own handling. The class adds no new virtuals of its own.
#if defined(EXCLUSIVE_SKYRIM_VR) || defined(EXCLUSIVE_SKYRIM_FLAT)
		void GetShaderMacros(ShaderMacro* a_macros) override;  // 0D, VR 0E
#endif

#ifdef SKYRIM_CROSS_VR
		void GetShaderMacros(ShaderMacro* a_macros)
		{
			REL::RelocateVirtual<decltype(&BSImagespaceShaderReflectionsRayTracing::GetShaderMacros)>(0x0D, 0x0E, this, a_macros);
		}
#endif
	};
	static_assert(sizeof(BSImagespaceShaderReflectionsRayTracing) == 0x1A8);
}

#include "RE/B/BSCubeMapCamera.h"

#include "RE/B/BSShaderAccumulator.h"

#include "RE/M/MemoryManager.h"

namespace RE
{
	BSCubeMapCamera* BSCubeMapCamera::Create()
	{
		auto camera = malloc<BSCubeMapCamera>();
		if (camera) {
			std::memset(reinterpret_cast<void*>(camera), 0, sizeof(BSCubeMapCamera));
			camera->Ctor();
		}
		return camera;
	}

	BSCubeMapCamera::~BSCubeMapCamera()
	{
		Dtor();
	}

	BSCubeMapCamera* BSCubeMapCamera::Ctor()
	{
		using func_t = decltype(&BSCubeMapCamera::Ctor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(100776, 107560) };
		return func(this);
	}

	void BSCubeMapCamera::SetFace(Face a_face)
	{
		using func_t = decltype(&BSCubeMapCamera::SetFace);
		static REL::Relocation<func_t> func{ RELOCATION_ID(100779, 107563) };
		return func(this, a_face);
	}

	void BSCubeMapCamera::Dtor()
	{
		using func_t = decltype(&BSCubeMapCamera::Dtor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(100781, 107565) };
		return func(this);
	}

#ifdef SKYRIM_CROSS_VR
	void BSCubeMapCamera::RenderCubemap(FaceEnableFlags a_faceMask, bool a_arg2, bool a_clearScenes, bool a_arg4)
	{
		REL::RelocateVirtual<decltype(&BSCubeMapCamera::RenderCubemap)>(0x35, 0x36, this, a_faceMask, a_arg2, a_clearScenes, a_arg4);
	}
#endif
}

#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSFaceGenMorphData;
	class BSFaceGenNiNode;
	class BSTriShape;

	class BSFaceGenModelMeshData
	{
	public:
		// members
		std::uint32_t                 unk00;      // 00
		std::uint32_t                 pad04;      // 04
		NiPointer<BSFaceGenNiNode>    faceNode;   // 08
		NiPointer<BSTriShape>         faceShape;  // 10
		void*                         triData;    // 18
		NiPointer<BSFaceGenMorphData> morphData;  // 20
	};
	static_assert(sizeof(BSFaceGenModelMeshData) == 0x28);

	class BSFaceGenModel : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSFaceGenModel;
		inline static constexpr auto VTABLE = VTABLE_BSFaceGenModel;

		~BSFaceGenModel() override;  // 00

		bool LoadModel(const char* a_modelPath, const char* a_triPath, bool a_unk)
		{
			using func_t = bool(BSFaceGenModel*, const char*, const char*, bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(26297, 26880) };
			return func(this, a_modelPath, a_triPath, a_unk);
		}

		// members
		BSTSmartPointer<BSFaceGenModelMeshData> modelMeshData;  // 10
		std::uint32_t                           unk18;          // 18
		std::uint32_t                           pad1C;          // 1C
	};
	static_assert(sizeof(BSFaceGenModel) == 0x20);
}

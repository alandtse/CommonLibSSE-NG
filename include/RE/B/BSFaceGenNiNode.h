#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiNode.h"
#include "RE/N/NiSmartPointer.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class NiUpdateData;
	class NiCloningProcess;
	class BSFaceGenAnimationData;
	class NiNode;

	class BSFaceGenNiNode : public NiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSFaceGenNiNode;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSFaceGenNiNode;
		inline static constexpr auto VTABLE = VTABLE_BSFaceGenNiNode;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                  \
	NiMatrix3                         baseRotation;  /* 00 */ \
	std::uint32_t                     pad14C;        /* 24 */ \
	NiPointer<BSFaceGenAnimationData> animationData; /* 28 */ \
	float                             lastTime;      /* 30 */ \
	ActorHandle                       unk15C;        /* 34 */ \
	std::uint16_t                     flags;         /* 38 */ \
	std::uint16_t                     pad162;        /* 3A */ \
	std::uint32_t                     pad164;        /* 3C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x40);

		~BSFaceGenNiNode() override;  // 00

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
#ifndef SKYRIM_CROSS_VR
		// The following are virtual functions past the point where VR compatibility breaks.
		void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;  // 2C
#endif

		// add
		SKYRIM_REL_VR_VIRTUAL void FixSkinInstances(NiNode* a_skeleton, bool a_arg2);  // 3E

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x128, 0x150);
		void CopyMembers(BSFaceGenNiNode* a_target, NiCloningProcess& a_cloning)
		{
			using func_t = void(BSFaceGenNiNode*, BSFaceGenNiNode*, NiCloningProcess&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(26401, 26981) };
			func(this, a_target, a_cloning);
		}

		void ApplyMorph(std::uint32_t a_morphType, std::uint32_t a_index, float a_value)
		{
			using func_t = void(BSFaceGenNiNode*, std::uint32_t, std::uint32_t, float);
			static REL::Relocation<func_t> func{ RELOCATION_ID(26412, 26993) };
			func(this, a_morphType, a_index, a_value);
		}

		bool HasMorph(std::uint32_t a_morphType, std::uint32_t a_index)
		{
			using func_t = bool(BSFaceGenNiNode*, std::uint32_t, std::uint32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(26413, 26994) };
			return func(this, a_morphType, a_index);
		}

		void UpdateBaseMorphs()
		{
			using func_t = void(BSFaceGenNiNode*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(26414, 26995) };
			func(this);
		}

		void UpdateFaceAnimation(NiUpdateData& a_data)
		{
			using func_t = void(BSFaceGenNiNode*, NiUpdateData&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(26417, 26998) };
			func(this, a_data);
		}

		void SetAnimationData(BSFaceGenAnimationData* a_data)
		{
			using func_t = void(BSFaceGenNiNode*, BSFaceGenAnimationData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(24423, 24934) };
			func(this, a_data);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT  // 128, 150
#endif
	};
	STATIC_ASSERT_SIZE(BSFaceGenNiNode, 0x168, 0x168, 0x190, 0x110);
}
#undef RUNTIME_DATA_CONTENT

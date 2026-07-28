#pragma once

#include "RE/B/BSTaskletData.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSProceduralLightningTasklet : public BSTaskletData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSProceduralLightningTasklet;
		inline static constexpr auto VTABLE = VTABLE_BSProceduralLightningTasklet;

		~BSProceduralLightningTasklet() override { Dtor(); }  // 00

		// override (BSTaskletData)
		void Func2() override;  // 02
		void Func3() override;  // 03

		// members
		bool          unk08;        // 08
		std::uint8_t  pad09[7];     // 09
		void*         unk10;        // 10 - group/manager pointer
		bool          active;       // 18
		std::uint8_t  pad19[3];     // 19
		std::uint32_t unk1C;        // 1C
		std::uint8_t  unk20[0x60];  // 20 - own container/array bookkeeping; not yet identified
		void*         unk80;        // 80
		std::uint32_t unk84;        // 84
		std::uint16_t unk8C;        // 8C
		std::uint8_t  pad8E[2];     // 8E
		std::uint32_t unk90;        // 90
		std::uint32_t unk94;        // 94
		std::uint32_t unk98;        // 98
		std::uint32_t unk9C;        // 9C
		void*         unkA0;        // A0
		std::uint32_t unkA8;        // A8
		bool          unkAC;        // AC
		std::uint8_t  padAD[3];     // AD

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT \
	std::uint8_t unk[0x18];  // B0 - VR-only extra tail; not yet identified
			VR_RUNTIME_DATA_CONTENT;
		};
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x18);

		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0xB0);

#if defined(EXCLUSIVE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT;  // B0
#endif

	private:
		void Dtor();
	};
#undef VR_RUNTIME_DATA_CONTENT
	STATIC_ASSERT_SIZE(BSProceduralLightningTasklet, 0xB0, 0xB0, 0xC8, 0xB0);
}

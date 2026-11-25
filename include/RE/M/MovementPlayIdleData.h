#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSPathingStreamRead;
	class BSPathingStreamWrite;

	// semantic names of the clip vectors/floats are unproven
	struct MovementPlayIdleData
	{
	public:
		void dtor()
		{
			using func_t = void(MovementPlayIdleData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89559, 92024) };
			func(this);
		}
		MovementPlayIdleData* CopyFrom(MovementPlayIdleData* a_other)
		{
			using func_t = MovementPlayIdleData*(MovementPlayIdleData*, MovementPlayIdleData*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89560, 92025) };
			return func(this, a_other);
		}
		void InitType2(float* a_src, NiPoint3* a_vecA, NiPoint3* a_vecB)
		{
			using func_t = void(MovementPlayIdleData*, float*, NiPoint3*, NiPoint3*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89563, 92028) };
			func(this, a_src, a_vecA, a_vecB);
		}
		void InitType3(void* a_clip, NiPoint3* a_vecA, NiPoint3* a_vecB)
		{
			using func_t = void(MovementPlayIdleData*, void*, NiPoint3*, NiPoint3*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89564, 92029) };
			func(this, a_clip, a_vecA, a_vecB);
		}

		void InitFromSelection(float* a_selection, NiPoint3* a_vecA, NiPoint3* a_vecB, NiPoint3* a_vecC, NiPoint3* a_vecD)
		{
			using func_t = void(MovementPlayIdleData*, float*, NiPoint3*, NiPoint3*, NiPoint3*, NiPoint3*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(89562, 92027) };
			func(this, a_selection, a_vecA, a_vecB, a_vecC, a_vecD);
		}

		// members
		std::uint32_t type;        // 00 - 0 after ctor, 2/3 after InitType2/InitType3
		NiPoint3      vecA;        // 04
		NiPoint3      vecB;        // 10
		NiPoint3      clipVecC;    // 1C
		NiPoint3      clipVecD;    // 28
		float         unk34[18];   // 34
		float         clipFloatE;  // 7C
		float         clipFloatF;  // 80
		float         clipFloatG;  // 84
	};
	static_assert(sizeof(MovementPlayIdleData) == 0x88);
}

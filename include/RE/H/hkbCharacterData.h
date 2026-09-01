#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkVector4.h"

namespace RE
{
	class hkbCharacterStringData;
	class hkbFootIkDriverInfo;
	class hkbHandIkDriverInfo;
	class hkbMirroredSkeletonInfo;
	class hkbVariableInfo;
	class hkbVariableValueSet;

	class hkbCharacterData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbCharacterData;
		inline static constexpr auto VTABLE = VTABLE_hkbCharacterData;

		// members
		float                             unk10;                    // 10 - sub-field split from activeragdoll; span 10-30 confirmed via dtor (arrays land at the expected 60/70)
		float                             unk14;                    // 14
		std::uint64_t                     unk18;                    // 18
		hkRefPtr<hkReferencedObject>      unk20;                    // 20 - real ref-counted ptr (RemoveReference'd in dtor); concrete type unconfirmed
		std::uint64_t                     unk28;                    // 28
		float                             modelUpMS[4];             // 30 (hkVector4)
		float                             modelForwardMS[4];        // 40 (hkVector4)
		float                             modelRightMS[4];          // 50 (hkVector4)
		hkArray<hkbVariableInfo>          characterPropertyInfos;   // 60
		hkArray<std::int32_t>             numBonesPerLod;           // 70
		hkRefPtr<hkbVariableValueSet>     characterPropertyValues;  // 80
		hkRefPtr<hkbFootIkDriverInfo>     footIkDriverInfo;         // 88
		hkRefPtr<hkbHandIkDriverInfo>     handIkDriverInfo;         // 90
		hkRefPtr<hkbCharacterStringData>  stringData;               // 98 - offset/ref-counted-ness confirmed via dtor; identity vs. mirroredSkeletonInfo below unconfirmed
		hkRefPtr<hkbMirroredSkeletonInfo> mirroredSkeletonInfo;     // A0 - offset/ref-counted-ness confirmed via dtor; identity vs. stringData above unconfirmed
		float                             scale;                    // A8 - from activeragdoll; not independently confirmed here (past the dtor's last touched offset)
		std::int16_t                      numHands;                 // AC - from activeragdoll; not independently confirmed here
		std::int16_t                      numFloatSlots;            // AE - from activeragdoll; not independently confirmed here
	};
	static_assert(sizeof(hkbCharacterData) == 0xB0);
}

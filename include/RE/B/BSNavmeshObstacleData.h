#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTArray.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	struct BSNavmeshInfo;
	class bhkRigidBody;
	class NiRefObject;

	class BSNavmeshObstacleData : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSNavmeshObstacleData;
		inline static constexpr auto VTABLE = VTABLE_BSNavmeshObstacleData;

		virtual ~BSNavmeshObstacleData();  // 00

		// members
		std::uint32_t            pad0C;             // 0C
		void*                    unk10;             // 10
		NiPointer<bhkRigidBody>  rigidBody;         // 18
		std::uint8_t             pad20[0x44];       // 20
		NiPoint3                 aabbMin;           // 64
		NiPoint3                 aabbMax;           // 70
		NiPoint3                 boundsMin;         // 7C
		NiPoint3                 boundsMax;         // 88
		std::uint32_t            lastUpdateTimeMS;  // 94 - tick from the time manager
		bool                     significant;       // 98
		bool                     unk99;             // 99
		std::uint8_t             pad9A[6];          // 9A
		BSTArray<BSNavmeshInfo*> navmeshInfos;      // A0
		NiPointer<NiRefObject>   unkB8;             // B8
	};
	static_assert(sizeof(BSNavmeshObstacleData) == 0xC0);
}

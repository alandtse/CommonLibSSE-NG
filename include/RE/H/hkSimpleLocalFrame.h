#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkLocalFrame.h"
#include "RE/H/hkLocalFrameGroup.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkStringPtr.h"
#include "RE/H/hkTransform.h"

namespace RE
{
	class hkSimpleLocalFrame : public hkLocalFrame
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkSimpleLocalFrame;
		inline static constexpr auto VTABLE = VTABLE_hkSimpleLocalFrame;

		~hkSimpleLocalFrame() override;  // 00

		// override
		void                GetTransform(hkTransform& a_transform) const override;                                                                 // 03
		void                SetTransform(const hkTransform& a_transform) override;                                                                 // 04
		void                GetOrigin(hkVector4& a_origin) const override;                                                                         // 05
		void                GetNearbyFrames(const hkVector4& a_position, float a_maxDistance, hkLocalFrameCollector& a_collector) const override;  // 06
		const char*         GetName() const override;                                                                                              // 07
		const hkLocalFrame* GetParentFrame() const override;                                                                                       // 08
		void                SetParentFrame(const hkLocalFrame* a_parentFrame) override;                                                            // 09
		std::int32_t        GetNumChildFrames() const override;                                                                                    // 0A
		hkLocalFrame*       GetChildFrame(std::int32_t a_index) const override;                                                                    // 0B
		hkLocalFrameGroup*  GetGroup() const override;                                                                                             // 0C
		void                SetGroup(hkLocalFrameGroup* a_group) override;                                                                         // 0D

		// members
		hkTransform                     transform;    // 10
		hkArray<hkRefPtr<hkLocalFrame>> children;     // 50
		hkLocalFrame*                   parentFrame;  // 60 - non-owning
		hkRefPtr<hkLocalFrameGroup>     group;        // 68
		hkStringPtr                     name;         // 70
		std::uint64_t                   pad78;        // 78
	};
	static_assert(sizeof(hkSimpleLocalFrame) == 0x80);
}

#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"
#include "RE/H/hkTransform.h"
#include "RE/H/hkVector4.h"

namespace RE
{
	class hkLocalFrameCollector;
	class hkLocalFrameGroup;
	class hkMemoryAllocator;

	class hkLocalFrame : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkLocalFrame;
		inline static constexpr auto VTABLE = VTABLE_hkLocalFrame;

		~hkLocalFrame() override;  // 00

		virtual void                GetTransform(hkTransform& a_transform) const = 0;                                                                 // 03
		virtual void                SetTransform(const hkTransform& a_transform) = 0;                                                                 // 04
		virtual void                GetOrigin(hkVector4& a_origin) const = 0;                                                                         // 05
		virtual void                GetNearbyFrames(const hkVector4& a_position, float a_maxDistance, hkLocalFrameCollector& a_collector) const = 0;  // 06
		virtual const char*         GetName() const = 0;                                                                                              // 07
		virtual const hkLocalFrame* GetParentFrame() const = 0;                                                                                       // 08
		virtual void                SetParentFrame(const hkLocalFrame* a_parentFrame) = 0;                                                            // 09
		virtual std::int32_t        GetNumChildFrames() const = 0;                                                                                    // 0A
		virtual hkLocalFrame*       GetChildFrame(std::int32_t a_index) const = 0;                                                                    // 0B
		virtual hkLocalFrameGroup*  GetGroup() const = 0;                                                                                             // 0C
		virtual void                SetGroup(hkLocalFrameGroup* a_group) = 0;                                                                         // 0D
		virtual void                GetDescendants(hkArray<const hkLocalFrame*>& a_descendants, hkMemoryAllocator& a_allocator) const;                // 0E
	};
	static_assert(sizeof(hkLocalFrame) == 0x10);
}

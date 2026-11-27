#pragma once

#include "RE/H/hkpSphereRepShape.h"

namespace RE
{
	class hkpConvexShape : public hkpSphereRepShape
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpConvexShape;
		inline static constexpr auto VTABLE = VTABLE_hkpConvexShape;

		~hkpConvexShape() override;  // 00

		// override (hkpSphereRepShape)
		float GetMaximumProjection(const hkVector4& a_direction) const override;                                                                         // 03
		bool  IsConvex() const override;                                                                                                                 // 05 - { return true; }
		void  CastRayWithCollectorImpl(const hkpShapeRayCastInput& a_input, const hkpCdBody& a_cdBody, hkpRayHitCollector& a_collector) const override;  // 09

		// add
		virtual void         GetFirstVertexImpl(hkVector4& a_vertexOut) const = 0;                                                                                                                                                                                                                              // 0D
		virtual void         GetSupportingVertexImpl(const hkVector4& a_direction, hkpCdVertex& a_supportVertexOut) const = 0;                                                                                                                                                                                  // 0E
		virtual void         ConvertVertexIdsToVerticesImpl(const hkpVertexID* a_ids, std::int32_t a_numIDs, hkpCdVertex* a_verticesOut) const = 0;                                                                                                                                                             // 0F
		virtual std::int32_t WeldContactPointImpl(hkpVertexID* a_featurePoints, std::uint8_t& a_numFeaturePoints, hkVector4& a_contactPointWs, const hkTransform* a_thisTransform, const hkpConvexShape* a_collidingShape, const hkTransform* a_collidingTransform, hkVector4& a_separatingNormalInOut) const;  // 10 - { return 2; }
		virtual void         GetCentreImpl(hkVector4& a_centreOut) const;                                                                                                                                                                                                                                       // 11

		// members
		float         radius;  // 20
		std::uint32_t pad1C;   // 24
	};
	static_assert(sizeof(hkpConvexShape) == 0x28);
}

#pragma once

#include "RE/B/BSPathingLocation.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSPathingStreamRead;
	class BSPathingStreamWrite;

	class PathingCoverLocation : public BSPathingLocation
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingCoverLocation;
		inline static constexpr auto VTABLE = VTABLE_PathingCoverLocation;

		virtual ~PathingCoverLocation();  // 00

		// add
		virtual void Read(BSPathingStreamRead* a_stream);          // 01
		virtual void Write(BSPathingStreamWrite* a_stream) const;  // 02

		void SetCoverData(std::uint16_t a_value, std::uint16_t a_lowerBound, std::uint16_t a_upperBound, std::uint8_t a_flag0, std::uint8_t a_flag1, std::uint8_t a_edgeIndex)
		{
			using func_t = void(PathingCoverLocation*, std::uint16_t, std::uint16_t, std::uint16_t, std::uint8_t, std::uint8_t, std::uint8_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(30402, 31241) };
			func(this, a_value, a_lowerBound, a_upperBound, a_flag0, a_flag1, a_edgeIndex);
		}

		bool IsStartPointCloser(NiPoint3* a_point)
		{
			using func_t = bool(PathingCoverLocation*, NiPoint3*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(30404, 31243) };
			return func(this, a_point);
		}

		std::uint32_t GetObstacleUpdateTime()
		{
			using func_t = std::uint32_t(PathingCoverLocation*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(30407, 31246) };
			return func(this);
		}

		bool IsObstacleUpdateTime(std::uint32_t a_time)
		{
			using func_t = bool(PathingCoverLocation*, std::uint32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(30408, 31247) };
			return func(this, a_time);
		}

		// members
		NiPoint3     edgeStart;       // 38
		NiPoint3     edgeEnd;         // 44
		NiPoint3     coverDirection;  // 50 - horizontal unit vector perpendicular to the edge
		std::uint8_t coverValue;      // 5C
		bool         aboveLower;      // 5D - coverValue >= lowerBound
		bool         aboveUpper;      // 5E - coverValue > upperBound
		bool         flag0;           // 5F
		bool         flag1;           // 60
		std::uint8_t edgeIndex;       // 61
		std::uint8_t unk62;           // 62
		std::uint8_t pad63[5];        // 63
	};
	static_assert(sizeof(PathingCoverLocation) == 0x68);
}

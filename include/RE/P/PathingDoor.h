#pragma once

#include "RE/B/BSPathingDoor.h"
#include "RE/B/BSPathingLocation.h"

namespace RE
{
	class PathingDoor : public BSPathingDoor
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingDoor;
		inline static constexpr auto VTABLE = VTABLE_PathingDoor;

		~PathingDoor() override;  // 00

		std::uint32_t GetType() const override;                                                  // 01
		std::uint32_t GetID() const override;                                                    // 02
		void          WriteID(BSPathingStreamWrite* a_stream) const override;                    // 03
		void          ReadID(BSPathingStreamRead* a_stream) override;                            // 04
		void          VisitID(BSPathingNumericIDVisitor* a_visitor) const override;              // 05
		bool          IsOpen() const override;                                                   // 06
		bool          IsClosed() const override;                                                 // 07
		bool          IsOpening() const override;                                                // 08
		bool          IsClosing() const override;                                                // 09
		void          GetLocation(BSPathingLocation& a_out) const override;                      // 0A
		void          GetTeleportLocation(BSPathingLocation& a_out) const override;              // 0B
		void          GetRotationZ(float& a_out) const override;                                 // 0C
		void          GetTeleportRotationZ(float& a_out) const override;                         // 0D
		float         GetAutoLoadFadeDistance() const override;                                  // 0E
		void          GetLinkedDoor(BSTSmartPointer<BSPathingDoor>& a_out) const override;       // 0F
		bool          IsSameDoor(const BSTSmartPointer<BSPathingDoor>& a_other) const override;  // 10
		void          GetDebugText(char* a_buf, std::int32_t a_size) const override;             // 11

		// members
		std::uint32_t     doorID;            // 10
		std::uint32_t     refHandle;         // 14 - TESObjectREFR handle (NullRefHandleId when none)
		BSPathingLocation forwardLocation;   // 18 - flag bit checked: forwardLocation.flags & 0x40
		BSPathingLocation backwardLocation;  // 48
	};
	STATIC_ASSERT_SIZE(PathingDoor, 0x78);
}

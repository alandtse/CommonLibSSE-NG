#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	class BSPathingLocation;
	class BSPathingStreamRead;
	class BSPathingStreamWrite;
	struct BSPathingNumericIDVisitor;

	class BSPathingDoor : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathingDoor;
		inline static constexpr auto VTABLE = VTABLE_BSPathingDoor;

		virtual ~BSPathingDoor();  // 00

		// add - all pure virtuals; concrete implementations live in derived PathingDoor
		virtual std::uint32_t GetType() const = 0;                                                  // 01
		virtual std::uint32_t GetID() const = 0;                                                    // 02
		virtual void          WriteID(BSPathingStreamWrite* a_stream) const = 0;                    // 03
		virtual void          ReadID(BSPathingStreamRead* a_stream) = 0;                            // 04
		virtual void          VisitID(BSPathingNumericIDVisitor* a_visitor) const = 0;              // 05
		virtual bool          IsOpen() const = 0;                                                   // 06
		virtual bool          IsClosed() const = 0;                                                 // 07
		virtual bool          IsOpening() const = 0;                                                // 08
		virtual bool          IsClosing() const = 0;                                                // 09
		virtual void          GetLocation(BSPathingLocation& a_out) const = 0;                      // 0A
		virtual void          GetTeleportLocation(BSPathingLocation& a_out) const = 0;              // 0B
		virtual void          GetRotationZ(float& a_out) const = 0;                                 // 0C
		virtual void          GetTeleportRotationZ(float& a_out) const = 0;                         // 0D
		virtual float         GetAutoLoadFadeDistance() const = 0;                                  // 0E
		virtual void          GetLinkedDoor(BSTSmartPointer<BSPathingDoor>& a_out) const = 0;       // 0F
		virtual bool          IsSameDoor(const BSTSmartPointer<BSPathingDoor>& a_other) const = 0;  // 10
		virtual void          GetDebugText(char* a_buf, std::int32_t a_size) const = 0;             // 11
	};
	STATIC_ASSERT_SIZE(BSPathingDoor, 0x10);
}

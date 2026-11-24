#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementQueryPathingState : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementQueryPathingState;
		inline static constexpr auto VTABLE = VTABLE_IMovementQueryPathingState;

		~IMovementQueryPathingState() override;  // 00

		// add
		virtual bool          GetRequest(void* a_out) = 0;                // 01
		virtual bool          GetSolution(void* a_out) = 0;               // 02
		virtual std::uint32_t QueryRequestComplete(void* a_request) = 0;  // 03
		virtual std::uint32_t QueryRequestIdle(void* a_request) = 0;      // 04
		virtual std::uint32_t QueryRequestPathing(void* a_request) = 0;   // 05
		virtual std::uint32_t QueryRequestPending(void* a_request) = 0;   // 06
		virtual void          Unk_07(void) = 0;                           // 07
		virtual void          Unk_08(void) = 0;                           // 08
		virtual bool          IsIdle() = 0;                               // 09
		virtual bool          IsComplete() = 0;                           // 0A
		virtual bool          IsPathing() = 0;                            // 0B
		virtual bool          IsValid() = 0;                              // 0C
		virtual bool          IsPending() = 0;                            // 0D
	};
	static_assert(sizeof(IMovementQueryPathingState) == 0x8);
}

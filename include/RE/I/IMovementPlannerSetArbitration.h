#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IMovementInterface.h"

namespace RE
{
	struct MovementArbitrationMaxWeightParameters;
	struct MovementArbitrationMaxWeightPoint;
	struct MovementArbitrationVectorAdd;

	class IMovementPlannerSetArbitration : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementPlannerSetArbitration;
		inline static constexpr auto VTABLE = VTABLE_IMovementPlannerSetArbitration;

		~IMovementPlannerSetArbitration() override;  // 00

		// add
		virtual void  SetVectorArbitration(const BSTSmartPointer<MovementArbitrationVectorAdd>& a_arb) = 0;                // 01
		virtual void  SetPointArbitration(const BSTSmartPointer<MovementArbitrationMaxWeightPoint>& a_arb) = 0;            // 02
		virtual void  SetParametersArbitration(const BSTSmartPointer<MovementArbitrationMaxWeightParameters>& a_arb) = 0;  // 03
		virtual void  ClearInitialized() = 0;                                                                              // 04
		virtual bool  GetInitialized() const = 0;                                                                          // 05
		virtual float GetBlockedTime() const = 0;                                                                          // 06
	};
	static_assert(sizeof(IMovementPlannerSetArbitration) == 0x8);
}

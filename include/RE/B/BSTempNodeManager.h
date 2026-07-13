#pragma once

#include "RE/N/NiNode.h"

namespace RE
{
	class BSTempNodeManager : public NiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSTempNodeManager;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSTempNodeManager;
		inline static constexpr auto VTABLE = VTABLE_BSTempNodeManager;

		~BSTempNodeManager() override;  // 00

		// override (NiNode)
#ifndef SKYRIM_CROSS_VR
		void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;          // 2C
		void UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;  // 2D
		void UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;     // 2E
#endif

		// add

		// Per-frame update: decrements each attached BSTempNode child's remaining lifetime by
		// elapsed time, detaching any that reach zero.
		void UpdateTempNodeTimers(float a_elapsedTime);

	private:
		std::uint64_t unk128;  // 128 - not yet reverse engineered
	};
	STATIC_ASSERT_SIZE(BSTempNodeManager, 0x130, 0x130, 0x158, SIZE_UNDEFINED, 0x130);
}

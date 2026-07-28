#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/N/NiInterpController.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSProceduralLightningController : public NiInterpController
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSProceduralLightningController;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSProceduralLightningController;
		inline static constexpr auto VTABLE = VTABLE_BSProceduralLightningController;

		~BSProceduralLightningController() override { Dtor(); }  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                            // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;   // 17
		void          LoadBinary(NiStream& a_stream) override;             // 18
		void          LinkObject(NiStream& a_stream) override;             // 19
		bool          RegisterStreamables(NiStream& a_stream) override;    // 1A
		void          SaveBinary(NiStream& a_stream) override;             // 1B
		bool          IsEqual(NiObject* a_object) override;                // 1C
		void          ProcessClone(NiCloningProcess& a_cloning) override;  // 1D

		// override (NiTimeController)
		void Update(float a_time) override;          // 27
		bool TargetIsRequiredType() const override;  // 2E

		// override (NiInterpController)
		std::uint16_t        GetInterpolatorCount() const override;                                                                                                                                                                   // 2F
		const char*          GetInterpolatorID(std::uint16_t a_index = 0) override;                                                                                                                                                   // 30
		std::uint16_t        GetInterpolatorIndex(const char* a_id) const override;                                                                                                                                                   // 31
		std::uint16_t        GetInterpolatorIndexFx(const BSFixedString& a_id) const override;                                                                                                                                        // 32
		NiInterpolator*      GetInterpolator(std::uint16_t a_index = 0) const override;                                                                                                                                               // 33
		void                 SetInterpolator(NiInterpolator* a_interpolator, std::uint16_t a_index = 0) override;                                                                                                                     // 34
		const char*          GetCtlrID() override;                                                                                                                                                                                    // 36
		NiInterpolator*      CreatePoseInterpolator(std::uint16_t a_index) override;                                                                                                                                                  // 37
		void                 SynchronizePoseInterpolator(NiInterpolator* a_interp, std::uint16_t a_index = 0) override;                                                                                                               // 38
		NiBlendInterpolator* CreateBlendInterpolator(std::uint16_t a_index = 0, bool a_managerControlled = false, bool a_accumulateAnimations = false, float a_weightThreshold = 0.0f, std::uint8_t a_arraySize = 2) const override;  // 39
		void                 GuaranteeTimeRange(float a_startTime, float a_endTime) override;                                                                                                                                         // 3A
		bool                 InterpolatorIsCorrectType(NiInterpolator* a_interpolator, std::uint16_t a_index) const override;                                                                                                         // 3B

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT \
	std::uint8_t unk[0x18];  // 190 - VR-only extra tail; not yet identified
			VR_RUNTIME_DATA_CONTENT;
		};
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x18);

		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x190);

		// members
		std::uint8_t unk48[0x148];  // 48 - own state (interpolators, event source, geometry/tasklet pointers, animation keyframe bookkeeping); not yet broken out field-by-field
#if defined(EXCLUSIVE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT;  // 190
#endif

	private:
		void Dtor();
	};
#undef VR_RUNTIME_DATA_CONTENT
	STATIC_ASSERT_SIZE(BSProceduralLightningController, 0x190, 0x190, 0x1A8, 0x190);
}

#pragma once
#include "BSFadeNode.h"

namespace RE
{
	class BSLeafAnimNode : public BSFadeNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSLeafAnimNode;
ttinline static constexpr auto VTABLE = VTABLE_BSLeafAnimNode;
		inline static auto           Ni_RTTI = NiRTTI_BSLeafAnimNode;

		~BSLeafAnimNode() override;  //00

		// override (BSFadeNode)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C
#ifndef SKYRIM_CROSS_VR
		// The following are virtual functions past the point where VR compatibility breaks.
		void            OnVisible(NiCullingProcess& a_process) override;  // 34
		BSLeafAnimNode* AsLeafAnimNode() override;                        // 3F
#endif
	private:
		float sqrDistanceToCamera;  //158
		float leafAmplitudeRefr;    //15C
		float leafFrequency;        //160
		float runningTime;          //164
		float previousTimer;        //168
	};
#ifdef ENABLE_SKYRIM_VR
	static_assert(sizeof(BSLeafAnimNode) == 0x128);
#else
	static_assert(sizeof(BSLeafAnimNode) == 0x170);
#endif
}

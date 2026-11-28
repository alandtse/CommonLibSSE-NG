#pragma once

#include "RE/A/AITimeStamp.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/F/FightReactions.h"
#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class DetectionListener;
	class DetectionState;

	class ActorKnowledge : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActorKnowledge;
		inline static constexpr auto VTABLE = VTABLE_ActorKnowledge;

		enum class FLAGS
		{
			kNone = 0
		};

		~ActorKnowledge() override;  // 00

		DetectionState* GetFreshDetectionState(std::int32_t a_level)
		{
			using func_t = DetectionState*(ActorKnowledge*, std::int32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(41624, 42702) };
			return func(this, a_level);
		}
		void UpdateListeners()
		{
			using func_t = void(ActorKnowledge*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(41632, 42710) };
			func(this);
		}
		void QueueDetectionUpdate(AITimeStamp a_time)
		{
			using func_t = void(ActorKnowledge*, AITimeStamp);
			static REL::Relocation<func_t> func{ RELOCATION_ID(41633, 42712) };
			func(this, a_time);
		}
		static void PushBackListener(void* a_listeners, DetectionListener* a_listener)
		{
			using func_t = void(void*, DetectionListener*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(41636, 42716) };
			func(a_listeners, a_listener);
		}

		void AddListener(DetectionListener* a_listener, std::int32_t a_level)
		{
			using func_t = void(ActorKnowledge*, DetectionListener*, std::int32_t);
			static REL::Relocation<func_t> func{ RELOCATION_ID(41622, 42700) };
			func(this, a_listener, a_level);
		}

		void AddListenerNoNotify(DetectionListener* a_listener)
		{
			using func_t = void(ActorKnowledge*, DetectionListener*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(41631, 42709) };
			func(this, a_listener);
		}

		// members
		ActorHandle                                 owner;                        // 10
		ActorHandle                                 target;                       // 14
		REX::EnumSet<FIGHT_REACTION, std::uint32_t> factionFightReaction;         // 18
		AITimeStamp                                 shouldAttackTargetTimeStamp;  // 1C
		NiPointer<DetectionState>                   detectionState;               // 20
		BSTArray<NiPointer<DetectionListener>>      listeners;                    // 28
		REX::EnumSet<FLAGS, std::uint32_t>          flags;                        // 40
		AITimeStamp                                 detectionQueuedTimeStamp;     // 44
	};
	static_assert(sizeof(ActorKnowledge) == 0x48);
}

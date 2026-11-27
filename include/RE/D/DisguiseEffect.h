#pragma once

#include "RE/A/ActiveEffect.h"
#include "RE/D/DetectionCollector.h"

namespace RE
{
	class DetectionListener;

	class DisguiseEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_DisguiseEffect;
		inline static constexpr auto VTABLE = VTABLE_DisguiseEffect;

		enum class State
		{
			kInitiate = 0,
			kWaiting,
			kNormal,
			kFail
		};

		// Size is inferred from the member extents, not an allocation size.
		class DetectionChecker : public DetectionCollector
		{
		public:
			inline static constexpr auto RTTI = RTTI_DisguiseEffect__DetectionChecker;
			inline static constexpr auto VTABLE = VTABLE_DisguiseEffect__DetectionChecker;

			// members
			DisguiseEffect* effect;        // 30
			std::uint32_t   casterHandle;  // 38
			std::uint32_t   pad3C;         // 3C
		};
		static_assert(sizeof(DetectionChecker) == 0x40);

		// override (ActiveEffect)
		virtual void EvaluateConditions(float a_delta, bool a_forceUpdate) override;  // 05
		virtual void SaveGame(BGSSaveFormBuffer* a_buf) override;                     // 08
		virtual void LoadGame(BGSLoadFormBuffer* a_buf) override;                     // 09
		virtual void FinishLoadGame(BGSLoadFormBuffer* a_buf) override;               // 0A
		virtual ~DisguiseEffect();                                                    // 13
		virtual void Start() override;                                                // 14
		virtual void Finish() override;                                               // 15

		static bool RefreshActorKnowledgeOfPlayer(DetectionListener** a_listener, std::uint32_t* a_handle)
		{
			using func_t = bool(DetectionListener**, std::uint32_t*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(33521, 34300) };
			return func(a_listener, a_handle);
		}

		void StartDetectionCheck()
		{
			using func_t = void(DisguiseEffect*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(33516, 34295) };
			func(this);
		}

		// members
		DisguiseEffect::State state;  // 90
	};
	static_assert(sizeof(DisguiseEffect) == 0x98);
}

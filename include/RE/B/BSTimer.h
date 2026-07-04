#pragma once

namespace RE
{
	class BSTimer
	{
	public:
		[[nodiscard]] static BSTimer* GetSingleton() noexcept
		{
			static REL::Relocation<BSTimer*> singleton{ RELOCATION_ID(523657, 410196) };
			return singleton.get();
		}

		static float QGlobalTimeMultiplier()
		{
			static REL::Relocation<float*> value{ RELOCATION_ID(511882, 388442) };
			return *value;
		}

		static float QGlobalTimeMultiplierTarget()
		{
			static REL::Relocation<float*> value{ RELOCATION_ID(511883, 388443) };
			return *value;
		}

		void SetGlobalTimeMultiplier(float a_multiplier, bool a_arg2)
		{
			using func_t = decltype(&BSTimer::SetGlobalTimeMultiplier);
			static REL::Relocation<func_t> func{ RELOCATION_ID(66988, 68245) };
			return func(this, a_multiplier, a_arg2);
		}

		// members
		//
		// Field semantics verified by RE (decompiled + disassembled, cross-checked byte-for-byte
		// identical on SE 1.5.97, AE 1.6.1170, and VR 1.4.15): SetGlobalTimeMultiplier, the per-frame
		// tick update, the smoothing-window setter, and Pause()/Unpause(). See CommonLibVR PR #203.
		//
		// qpcBaseline (08): a QueryPerformanceCounter baseline Pause()/Unpause() use to measure pause
		//   duration. Verified as ONE 64-bit read (`sub rax,[this+8]`) on all three runtimes -- NOT the
		//   two uint32_t fields this used to be split into (the high dword was never unused padding).
		// smoothedTickCount (20) / tickCount (24): paired tick bookkeeping. tickCount is set to the
		//   frame's consumed tick count every update; smoothedTickCount mirrors it when unsmoothed but
		//   drifts by the averaged-delta contribution when smoothing is active. Both are advanced by the
		//   pause duration in Unpause(), paired respectively with pausedSmoothedOffset/pausedTickOffset.
		// tickCountBaseline (28): external raw tick counter is diffed against this each update. Verified
		//   uint32_t, not the previous (incorrect) float typing.
		// pausedSmoothedOffset (2C) / pausedTickOffset (30): Pause() scratch = ticksAtPause minus
		//   smoothedTickCount/tickCountBaseline; Unpause() uses them to advance those fields by the
		//   pause duration.
		// smoothingSampleCount (38): AE's decompile names this setter parameter
		//   iUnstableFrameTimeHistorySize_Display (gated by bCompensateUnstableFrameTime_Display) -- an
		//   authoritative Bethesda name. 0-2 = passthrough, >=3 = moving average over smoothingBuffer.
		float*        smoothingBuffer;                // 00
		std::int64_t  qpcBaseline;                    // 08
		float         clamp;                          // 10
		float         clampRemainder;                 // 14
		float         delta;                          // 18
		float         realTimeDelta;                  // 1C
		std::uint32_t smoothedTickCount;              // 20
		std::uint32_t tickCount;                      // 24
		std::uint32_t tickCountBaseline;              // 28
		std::uint32_t pausedSmoothedOffset;           // 2C
		std::uint32_t pausedTickOffset;               // 30
		std::uint32_t pauseCount;                     // 34
		std::uint8_t  smoothingSampleCount;           // 38
		std::uint8_t  smoothingBufferIndex;           // 39
		bool          useGlobalTimeMultiplierTarget;  // 3A
		std::uint8_t  pad3B;                          // 3B
		std::uint32_t pad3C;                          // 3C
	};
	static_assert(sizeof(BSTimer) == 0x40);
}

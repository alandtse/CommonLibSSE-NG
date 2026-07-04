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
		// identical on SE 1.5.97, AE 1.6.1170, and VR 1.4.15): the constructor, SetGlobalTimeMultiplier,
		// the per-frame tick update, the smoothing-window setter, and Pause()/Unpause(). Several fields
		// also line up with pre-existing, independently-named globals at gTimeManager's fixed instance
		// (gSecondsSinceLastFrame_WorldTime, gSecondsSinceLastFrame_RealTime,
		// gDurationOfApplicationRunTimeMS, gChangeTimeMultSlowly) -- an authoritative second source that
		// corroborates the RE below field-for-field. See CommonLibVR PR #203.
		//
		// qpcBaseline (08): a QueryPerformanceCounter baseline the constructor initializes and
		//   Pause()/Unpause() use to measure pause duration. Verified as ONE 64-bit read/write
		//   (`sub rax,[this+8]` / ctor's `((LARGE_INTEGER*)(this+8))->QuadPart = ...`) on all three
		//   runtimes -- NOT the two uint32_t fields this used to be split into (the high dword was
		//   never unused padding). Defaults to "now" at construction.
		// clamp (10) / clampRemainder (14): fixed-timestep step size and its fractional carry. Both
		//   default to 0 (variable timestep) at construction.
		// delta (18) / realTimeDelta (1C): delta = realTimeDelta * current global time multiplier;
		//   realTimeDelta is captured first, before the multiplier is applied. Matches the existing
		//   globals gSecondsSinceLastFrame_WorldTime (delta) and gSecondsSinceLastFrame_RealTime /
		//   fSecondsSinceLastFrameRealTime (realTimeDelta) at gTimeManager's fixed address. Both
		//   default to 0 at construction.
		// smoothedRunTimeMS (20) / runTimeMS (24): paired, millisecond-scale elapsed-runtime
		//   bookkeeping (matches the authoritative AE global name gDurationOfApplicationRunTimeMS for
		//   offset 20). runTimeMS is set to the frame's consumed elapsed time every update;
		//   smoothedRunTimeMS mirrors it when unsmoothed but drifts by the averaged-delta contribution
		//   when smoothing is active. Both are advanced by the pause duration in Unpause(), paired
		//   respectively with pausedSmoothedRunTimeOffset/runTimeMSBaseline. Both default to 0 (except
		//   runTimeMSBaseline, see below) at construction.
		// runTimeMSBaseline (28): external elapsed-runtime input is diffed against this each update.
		//   Verified uint32_t, not the previous (incorrect) float typing. The constructor either
		//   computes this from QueryPerformanceCounter "now", or takes it directly as an explicit
		//   optional 2nd constructor argument (non-zero = caller-supplied epoch).
		// pausedSmoothedRunTimeOffset (2C) / pausedRunTimeOffset (30): Pause() scratch = elapsed-time-
		//   at-pause minus smoothedRunTimeMS/runTimeMSBaseline; Unpause() uses them to advance those
		//   fields by the pause duration.
		// pauseCount (34): Pause()/Unpause() reference count (supports nested pausing), not a bool.
		//   Defaults to 0 at construction.
		// smoothingSampleCount (38): AE's decompile names this setter parameter
		//   iUnstableFrameTimeHistorySize_Display (gated by bCompensateUnstableFrameTime_Display) -- an
		//   authoritative Bethesda name. 0-2 = passthrough, >=3 = moving average over smoothingBuffer.
		// useGlobalTimeMultiplierTarget (3A): gates whether SetGlobalTimeMultiplier snaps
		//   gCurrentGlobalTimeMultiplier immediately or eases it toward gTargetGlobalTimeMultiplier.
		//   Defaults to false at construction, but -- unlike every other field here -- is NOT just a
		//   one-time default: it is refreshed every frame in the per-frame update's caller from the
		//   ini setting bChangeTimeMultSlowly:General (matches the existing global name
		//   gChangeTimeMultSlowly at this exact offset on all three runtimes).
		float*        smoothingBuffer;                // 00
		std::int64_t  qpcBaseline;                    // 08
		float         clamp;                          // 10
		float         clampRemainder;                 // 14
		float         delta;                          // 18
		float         realTimeDelta;                  // 1C
		std::uint32_t smoothedRunTimeMS;              // 20
		std::uint32_t runTimeMS;                      // 24
		std::uint32_t runTimeMSBaseline;              // 28
		std::uint32_t pausedSmoothedRunTimeOffset;    // 2C
		std::uint32_t pausedRunTimeOffset;            // 30
		std::uint32_t pauseCount;                     // 34
		std::uint8_t  smoothingSampleCount;           // 38
		std::uint8_t  smoothingBufferIndex;           // 39
		bool          useGlobalTimeMultiplierTarget;  // 3A
		std::uint8_t  pad3B;                          // 3B
		std::uint32_t pad3C;                          // 3C
	};
	static_assert(sizeof(BSTimer) == 0x40);
}

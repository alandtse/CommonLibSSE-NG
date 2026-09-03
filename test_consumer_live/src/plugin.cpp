#include <spdlog/sinks/basic_file_sink.h>

// Live-verification harness for RE::detail::VtableShimBase-style adapters
// (currently: RE::MenuEventHandlerEx). See README.md for what this is and
// why it exists outside the normal `tests/` Catch2 suite.
//
// To exercise a different adapter (e.g. a future PlayerInputHandlerEx),
// swap TestHandler/BrokenHandler's base classes and RealProcessButtonSlot()'s
// return values for the new adapter's real per-runtime slot layout.

#ifndef RUN_BROKEN_COMPARISON
// Off by default: reproducing the broken path deliberately crashes the
// game. Set to 1 (or pass -DRUN_BROKEN_COMPARISON=1) to also run it.
#	define RUN_BROKEN_COMPARISON 0
#endif

namespace
{
	void SetupLog()
	{
		auto logsFolder = SKSE::log::log_directory();
		if (!logsFolder) {
			SKSE::stl::report_and_fail("no log dir");
		}
		auto path = *logsFolder / "CommonLibSSELiveVerify.log";
		auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path.string(), true);
		auto logger = std::make_shared<spdlog::logger>("log", std::move(fileSink));
		spdlog::set_default_logger(std::move(logger));
		spdlog::set_level(spdlog::level::trace);
		spdlog::flush_on(spdlog::level::trace);
	}

	// The fixed path: a real, genuinely overridable derived class.
	class TestHandler : public RE::MenuEventHandlerEx
	{
	public:
		bool sawCanProcess = false;
		bool sawProcessButton = false;

		bool CanProcess(RE::InputEvent*) override
		{
			sawCanProcess = true;
			SKSE::log::info("TestHandler::CanProcess called (typed dispatch through shim vtable)");
			return true;
		}

		bool ProcessButton(RE::ButtonEvent*) override
		{
			sawProcessButton = true;
			SKSE::log::info("TestHandler::ProcessButton called");
			return true;
		}
	};

#if RUN_BROKEN_COMPARISON
	// The broken path this harness exists to catch: deriving directly from
	// the real interface. CanProcess is still a genuine pure virtual (not
	// converted by the RelocateVirtual migration), so it overrides normally;
	// ProcessButton is no longer virtual, so this can only ever be a
	// same-named NON-virtual method -- exactly what a plugin author forced
	// to drop `override` ends up writing, and exactly what produced
	// CommonLibSSE-NG#324.
	class BrokenHandler : public RE::MenuEventHandler
	{
	public:
		bool sawProcessButton = false;

		bool CanProcess(RE::InputEvent*) override { return true; }

		bool ProcessButton(RE::ButtonEvent*)
		{
			sawProcessButton = true;
			SKSE::log::info("BrokenHandler::ProcessButton called (should be unreachable via real dispatch)");
			return true;
		}
	};
#endif

	HMODULE ModuleOf(void* a_addr)
	{
		HMODULE hm = nullptr;
		GetModuleHandleExA(
			GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
			reinterpret_cast<LPCSTR>(a_addr), &hm);
		return hm;
	}

	// The real engine's fixed vtable slot for ProcessButton on the
	// currently-running exe, mirroring MenuEventHandlerEx's own runtime
	// detection. This is what the game's dispatcher actually indexes by --
	// simulating it here (rather than only calling through our own typed
	// pointer) is what makes this check meaningful: it doesn't just prove
	// our own code calls itself correctly, it proves the vtable is shaped
	// the way the real, external caller expects.
	int RealProcessButtonSlot()
	{
		if (REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
			return 7;
		}
		return 5;
	}

	void RunSelfTest()
	{
		SKSE::log::info("=== MenuEventHandlerEx live self-test starting ===");

		TestHandler           handler;
		RE::MenuEventHandler* h = handler.Handler();
		SKSE::log::info("Handler() = {:x}", reinterpret_cast<std::uintptr_t>(h));

		auto vtbl = *reinterpret_cast<void***>(h);
		SKSE::log::info("shim vtbl = {:x}", reinterpret_cast<std::uintptr_t>(vtbl));

		HMODULE gameModule = GetModuleHandleA(nullptr);
		HMODULE pluginModule = ModuleOf(reinterpret_cast<void*>(&RunSelfTest));
		SKSE::log::info("game module = {:x}, plugin module = {:x}",
			reinterpret_cast<std::uintptr_t>(gameModule), reinterpret_cast<std::uintptr_t>(pluginModule));

		for (int i = 0; i < 6; ++i) {
			void*       slot = vtbl[i];
			HMODULE     owner = ModuleOf(slot);
			const char* which = owner == gameModule ? "GAME" : (owner == pluginModule ? "PLUGIN" : "UNKNOWN");
			SKSE::log::info("slot[{}] = {:x} ({})", i, reinterpret_cast<std::uintptr_t>(slot), which);
		}

		bool typedCanProcess = h->CanProcess(nullptr);
		SKSE::log::info("typed h->CanProcess(nullptr) = {}, sawCanProcess = {}", typedCanProcess, handler.sawCanProcess);

		handler.sawProcessButton = false;
		int buttonSlot = RealProcessButtonSlot();
		using RawFn = bool (*)(void*, RE::ButtonEvent*);
		auto rawSlotFn = reinterpret_cast<RawFn>(vtbl[buttonSlot]);
		bool rawResult = rawSlotFn(h, nullptr);
		SKSE::log::info(
			"raw vtbl[{}](h, nullptr) [simulating real engine dispatch] = {}, sawProcessButton = {}",
			buttonSlot, rawResult, handler.sawProcessButton);

		bool typedButtonResult = h->ProcessButton(nullptr);
		SKSE::log::info("typed h->ProcessButton(nullptr) = {}", typedButtonResult);

		const auto& ti = typeid(*h);
		SKSE::log::info("typeid(*h).name() = {}", ti.name());

		bool pass = handler.sawCanProcess && handler.sawProcessButton && typedCanProcess && rawResult;
		SKSE::log::info("=== MenuEventHandlerEx live self-test {} ===", pass ? "PASSED" : "FAILED");
	}

#if RUN_BROKEN_COMPARISON
	// Reproduces #324's actual failure for a controlled before/after: the
	// real engine's fixed-slot dispatch (simulated exactly as above) against
	// a plugin's shortened, compiler-generated vtable instead of a
	// synthesized one. This WILL crash the game -- that's the point.
	void RunBrokenComparison()
	{
		SKSE::log::info("=== broken (pre-MenuEventHandlerEx) comparison starting ===");

		BrokenHandler broken;
		auto          vtbl = *reinterpret_cast<void***>(&broken);
		SKSE::log::info("BrokenHandler vtbl = {:x}", reinterpret_cast<std::uintptr_t>(vtbl));

		HMODULE gameModule = GetModuleHandleA(nullptr);
		HMODULE pluginModule = ModuleOf(reinterpret_cast<void*>(&RunBrokenComparison));
		for (int i = 0; i < 2; ++i) {
			void*       slot = vtbl[i];
			HMODULE     owner = ModuleOf(slot);
			const char* which = owner == gameModule ? "GAME" : (owner == pluginModule ? "PLUGIN" : "UNKNOWN");
			SKSE::log::info("BrokenHandler slot[{}] = {:x} ({})", i, reinterpret_cast<std::uintptr_t>(slot), which);
		}

		int         buttonSlot = RealProcessButtonSlot();
		void*       overrunSlot = vtbl[buttonSlot];
		HMODULE     owner = ModuleOf(overrunSlot);
		const char* which = owner == gameModule ? "GAME" : (owner == pluginModule ? "PLUGIN" : "UNKNOWN");
		SKSE::log::info(
			"BrokenHandler vtbl[{}] (real ProcessButton slot the engine would call) = {:x} ({}) -- reading {} bytes past a 2-slot vtable",
			buttonSlot, reinterpret_cast<std::uintptr_t>(overrunSlot), which, (buttonSlot - 1) * 8);

		SKSE::log::info("calling it now, simulating the real engine's blind dispatch -- expect a crash if #324's mechanism is real");
		using RawFn = bool (*)(void*, RE::ButtonEvent*);
		auto rawSlotFn = reinterpret_cast<RawFn>(overrunSlot);
		bool result = rawSlotFn(&broken, nullptr);
		SKSE::log::info("did NOT crash: vtbl[{}](&broken, nullptr) = {}, sawProcessButton = {}",
			buttonSlot, result, broken.sawProcessButton);
	}
#endif

	void OnMessage(SKSE::MessagingInterface::Message* a_msg)
	{
		if (a_msg->type == SKSE::MessagingInterface::kDataLoaded) {
			SKSE::log::info("kDataLoaded received");
			RunSelfTest();
#if RUN_BROKEN_COMPARISON
			RunBrokenComparison();
#endif
		}
	}
}

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
	SetupLog();
	SKSE::Init(a_skse);
	if (!SKSE::GetMessagingInterface()->RegisterListener(OnMessage)) {
		SKSE::stl::report_and_fail("Failed to register message listener");
		return false;
	}
	SKSE::log::info("CommonLibSSELiveVerify loaded (RUN_BROKEN_COMPARISON={})", RUN_BROKEN_COMPARISON);
	return true;
}

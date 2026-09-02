#include "catch2/catch_all.hpp"

#include "RE/M/MenuEventHandler.h"
#include "RE/M/MenuEventHandlerEx.h"

// Regression test: deriving from RE::MenuEventHandler and overriding
// CanProcess/ProcessButton directly no longer compiles/links safely on
// builds spanning multiple runtimes (see MenuEventHandlerEx.h). This is
// exactly the pattern used by real-world plugins (e.g.
// github.com/zyf2008Neptune/skse-qui's PluginExplorerMenu), migrated to the
// supported RE::MenuEventHandlerEx replacement.
namespace
{
	class TestHandler : public RE::MenuEventHandlerEx
	{
	public:
		bool CanProcess(RE::InputEvent*) override { return true; }
		bool ProcessButton(RE::ButtonEvent*) override { return true; }
	};
}

TEST_CASE("MenuEventHandlerEx derived class links and destructs", "[.]")
{
	TestHandler           h;
	RE::MenuEventHandler* handler = h.Handler();
	REQUIRE(handler != nullptr);
	SUCCEED();
}

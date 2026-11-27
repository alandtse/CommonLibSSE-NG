#include "RE/E/ErrorLogger.h"

namespace RE
{
	namespace BSScript
	{
		void ErrorLogger::PostMessageBySeverity(const char* a_message, Severity a_severity)
		{
			using func_t = decltype(&ErrorLogger::PostMessageBySeverity);
			static REL::Relocation<func_t> func{ RELOCATION_ID(97690, 104432) };
			return func(this, a_message, a_severity);
		}
	}
}

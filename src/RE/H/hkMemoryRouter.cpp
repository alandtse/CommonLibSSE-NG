#include "RE/H/hkMemoryRouter.h"
#include <WinSock2.h>
#include <processthreadsapi.h>

namespace RE
{
	static DWORD* g_dwTlsIndex = (DWORD*)RELOCATION_ID(520865, 407383).address();

	hkMemoryRouter& hkGetMemoryRouter()
	{
		return *(RE::hkMemoryRouter*)(uintptr_t)TlsGetValue(*g_dwTlsIndex);
	}
}

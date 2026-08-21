#pragma once

#include "RE/B/BSSaveDataSystemUtility.h"

namespace RE
{
	class BSWin32SaveDataSystemUtility : public BSSaveDataSystemUtility
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSWin32SaveDataSystemUtility;
		inline static constexpr auto VTABLE = VTABLE_BSWin32SaveDataSystemUtility;

		~BSWin32SaveDataSystemUtility() override;

		// override (BSSaveDataSystemUtility)
		bool    CreateSaveDirectory(const char* a_pathName, bool a_ignoreINI) override;                               // 01
		errno_t PrepareFileSavePath(const char* a_fileName, char* a_dst, bool a_tmpSave, bool a_ignoreINI) override;  // 02

		static BSWin32SaveDataSystemUtility* GetSingleton();
	};
	static_assert(sizeof(BSWin32SaveDataSystemUtility) == 0x228);
}

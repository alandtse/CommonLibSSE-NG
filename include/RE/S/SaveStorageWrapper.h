#pragma once

#include "RE/B/BSStorage.h"

namespace RE
{
	class Win32FileType;

	class SaveStorageWrapper : public BSStorage
	{
	public:
		inline static constexpr auto RTTI = RTTI_SaveStorageWrapper;
		inline static constexpr auto VTABLE = VTABLE_SaveStorageWrapper;

		~SaveStorageWrapper() override;  // 00

		// override BSStorage
		std::size_t              GetSize() const override;                                                       // 01
		std::size_t              GetPosition() const override;                                                   // 02
		BSStorageDefs::ErrorCode Seek(std::size_t a_offset, BSStorageDefs::SeekMode a_seekMode) const override;  // 03
		BSStorageDefs::ErrorCode Read(std::size_t a_numBytes, std::byte* a_bytes) const override;                // 04
		BSStorageDefs::ErrorCode Write(std::size_t a_numBytes, const std::byte* a_bytes) override;               // 05

		// members
		Win32FileType* file;           // 20
		std::uint32_t  startPosition;  // 28
	};
	static_assert(sizeof(SaveStorageWrapper) == 0x30);
}

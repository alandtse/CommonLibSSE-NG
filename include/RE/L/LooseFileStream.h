#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/L/LooseFileStreamBase.h"
#include "RE/S/Stream.h"
#include "REL/Relocation.h"

namespace RE
{
	namespace BSResource
	{
		class Location;

		// Stream is the primary base on SE and VR; on AE the polymorphic LooseFileStreamBase is first
		// and Stream is at 0x30. Builds that mix AE with SE or VR must use the accessors.
#if defined(ENABLE_SKYRIM_AE) && !defined(EXCLUSIVE_SKYRIM_AE)
		class LooseFileStream
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSResource____LooseFileStream;
			inline static constexpr auto VTABLE = VTABLE_BSResource____LooseFileStream;

			LooseFileStream() = delete;
			~LooseFileStream() = delete;

			struct RUNTIME_DATA
			{
				Location*     location;  // 00
				std::uint64_t filePos;   // 08
				void*         buffer;    // 10
			};
			static_assert(sizeof(RUNTIME_DATA) == 0x18);

			[[nodiscard]] Stream*              AsStream() noexcept { return &REL::RelocateMember<Stream>(this, REL::Module::IsAE() ? 0x30 : 0x00); }
			[[nodiscard]] LooseFileStreamBase* GetFileData() noexcept { return &REL::RelocateMember<LooseFileStreamBase>(this, REL::Module::IsAE() ? 0x08 : 0x10); }
			[[nodiscard]] RUNTIME_DATA&        GetRuntimeData() noexcept { return REL::RelocateMember<RUNTIME_DATA>(this, REL::Module::IsAE() ? 0x48 : 0x38); }
		};
#else
		class LooseFileStream :
			public LooseFileStreamBase,  // 10 (AE 00)
			public Stream                // 00 (AE 30)
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSResource____LooseFileStream;
			inline static constexpr auto VTABLE = VTABLE_BSResource____LooseFileStream;

			~LooseFileStream() override;  // 00

			// override (Stream)
			ErrorCode               DoOpen() override;                                                                                // 01
			void                    DoClose() override;                                                                               // 02
			ErrorCode               DoGetInfo(Info& a_info) override;                                                                 // 04
			void                    DoClone(BSTSmartPointer<Stream>& a_out) const override;                                           // 05
			ErrorCode               DoRead(void* a_buffer, std::uint64_t a_toRead, std::uint64_t& a_read) const override;             // 06
			ErrorCode               DoWrite(const void* a_buffer, std::uint64_t a_toWrite, std::uint64_t& a_written) const override;  // 07
			ErrorCode               DoSeek(std::uint64_t a_toSeek, SeekMode a_mode, std::uint64_t& a_sought) const override;          // 08
			ErrorCode               DoSetEndOfStream() override;                                                                      // 09
			bool                    DoGetName(BSFixedString& a_dst) const override;                                                   // 0A
			ErrorCode               DoCreateAsync(BSTSmartPointer<AsyncStream>& a_streamOut) const override;                          // 0B
#	ifndef ENABLE_SKYRIM_AE
			static LooseFileStream* Create(BSFixedString a_prefix, BSFixedString a_dirName, BSFixedString a_fileName, std::uint32_t a_fileSize, bool a_readOnly, Location* a_location);
#	endif

			[[nodiscard]] Stream* AsStream() noexcept
			{
				return this;
			}
			[[nodiscard]] LooseFileStreamBase* GetFileData() noexcept { return this; }

			// members
			Location*     location;  // 38 (AE 48)
			std::uint64_t filePos;   // 40 (AE 50)
			void*         buffer;    // 48 (AE 58)

		private:
#	ifndef ENABLE_SKYRIM_AE
			LooseFileStream* Ctor(const BSFixedString& a_prefix, const BSFixedString& a_dirName, const BSFixedString& a_fileName, std::uint32_t a_fileSize, bool a_readOnly, Location* a_location);
#	endif
		};
#	ifdef EXCLUSIVE_SKYRIM_AE
		static_assert(sizeof(LooseFileStream) == 0x60);
#	else
		static_assert(sizeof(LooseFileStream) == 0x50);
#	endif
#endif
	}
}

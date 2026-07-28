#pragma once

#include "RE/E/ErrorCodes.h"
#include "RE/M/MemoryManager.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	namespace BSResource
	{
		struct Info;

		class StreamBase
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSResource__StreamBase;
			inline static constexpr auto VTABLE = VTABLE_BSResource__StreamBase;

			enum : std::uint32_t
			{
				kWritable = 1 << 0,
				kRefCountBeg = 0x1000,
				kRefCountMask = (std::uint32_t)0xFFFFF000
			};

			StreamBase();
			StreamBase(const StreamBase& a_rhs);
			StreamBase(StreamBase&& a_rhs);
			StreamBase(std::uint32_t a_totalSize);
			virtual ~StreamBase() = default;  // 00

			// add
			virtual ErrorCode                   DoOpen() = 0;             // 01
			virtual void                        DoClose() = 0;            // 02
			[[nodiscard]] virtual std::uint64_t DoGetKey() const;         // 03 - { return 0; }
			virtual ErrorCode                   DoGetInfo(Info& a_info);  // 04 - { return ErrorCode::kUnsupported; }

			TES_HEAP_REDEFINE_NEW();

			std::uint32_t      DecRef();
			std::uint32_t      IncRef();
			[[nodiscard]] bool IsWritable() const;

			// unk0C only exists in AE. Confirmed via Ghidra: SE 1.5.97 and VR 1.4.15 have no
			// gap between totalSize and the ref-count field; AE 1.6.1170 does. Returns nullptr
			// on SE/VR; uses IsAE() (not ENABLE_SKYRIM_AE) so cross-runtime builds resolve by
			// the actual detected runtime, not just whether AE support was compiled in.
			struct AE_RUNTIME_DATA
			{
#define AE_RUNTIME_DATA_CONTENT \
	std::uint32_t unk0C;  // 0C
				AE_RUNTIME_DATA_CONTENT
			};
			static_assert(sizeof(AE_RUNTIME_DATA) == 0x4);

			[[nodiscard]] inline AE_RUNTIME_DATA* GetAERuntimeData() noexcept
			{
				if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
					return reinterpret_cast<AE_RUNTIME_DATA*>(reinterpret_cast<std::uint8_t*>(this) + 0xC);
				}
				return nullptr;
			}

			[[nodiscard]] inline const AE_RUNTIME_DATA* GetAERuntimeData() const noexcept
			{
				if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
					return reinterpret_cast<const AE_RUNTIME_DATA*>(reinterpret_cast<const std::uint8_t*>(this) + 0xC);
				}
				return nullptr;
			}

			// flags exists in every runtime, but AE's extra unk0C field shifts its real offset
			// from 0xC (SE/VR) to 0x10 (AE). The `flags` member below only reserves the byte
			// range at the compiler's own chosen offset; always go through GetFlags() instead
			// of the bare member so cross-runtime builds read/write the correct real offset.
			[[nodiscard]] inline std::uint32_t& GetFlags() noexcept
			{
				if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
					return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x10);
				}
				return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0xC);
			}

			[[nodiscard]] inline const std::uint32_t& GetFlags() const noexcept
			{
				if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
					return *reinterpret_cast<const std::uint32_t*>(reinterpret_cast<const std::uint8_t*>(this) + 0x10);
				}
				return *reinterpret_cast<const std::uint32_t*>(reinterpret_cast<const std::uint8_t*>(this) + 0xC);
			}

			// members
			std::uint32_t totalSize;  // 08
#ifdef ENABLE_SKYRIM_AE
			AE_RUNTIME_DATA_CONTENT;
#endif
			std::uint32_t flags;  // 10 (0xC on SE/VR; see GetFlags())
		};
#undef AE_RUNTIME_DATA_CONTENT
#ifdef ENABLE_SKYRIM_AE
		static_assert(sizeof(StreamBase) == 0x18);
#else
		static_assert(sizeof(StreamBase) == 0x10);
#endif
	}
}

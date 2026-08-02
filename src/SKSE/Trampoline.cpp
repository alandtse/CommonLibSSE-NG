#include "SKSE/Trampoline.h"

#include "SKSE/Logger.h"

#include "REX/W32/KERNEL32.h"

// xbyak brings in <Windows.h>
#ifdef SKSE_SUPPORT_XBYAK
#	include <xbyak/xbyak.h>
#	undef max
#	undef MEM_COMMIT
#	undef MEM_FREE
#	undef MEM_RELEASE
#	undef MEM_RESERVE
#	undef PAGE_EXECUTE_READWRITE
#endif

// hde64.h transitively pulls in <Windows.h> (like xbyak above), colliding with REX::W32's
// own MEM_*/PAGE_* names used below.
#ifdef SKSE_SUPPORT_PATCH_SAFETY
#	include <hde64.h>
#	undef max
#	undef MEM_COMMIT
#	undef MEM_FREE
#	undef MEM_RELEASE
#	undef MEM_RESERVE
#	undef PAGE_EXECUTE_READWRITE
#endif

namespace SKSE
{
	namespace detail
	{
#ifdef SKSE_SUPPORT_PATCH_SAFETY
		// FNV-1a 64-bit. Not a security hash -- just a cheap, deterministic change-detector
		// so a_expectedPatchHash can tell "still the bytes I verified" from "something moved."
		[[nodiscard]] std::uint64_t fnv1a64(std::uintptr_t a_addr, std::size_t a_len) noexcept
		{
			constexpr std::uint64_t offsetBasis = 0xCBF29CE484222325ULL;
			constexpr std::uint64_t prime = 0x00000100000001B3ULL;

			auto       hash = offsetBasis;
			const auto bytes = reinterpret_cast<const std::uint8_t*>(a_addr);
			for (std::size_t i = 0; i < a_len; ++i) {
				hash ^= bytes[i];
				hash *= prime;
			}
			return hash;
		}

		// Warns when a write_branch<N> patch partially overwrites the instruction after the
		// one it targets -- those bytes can still be a live indirect-dispatch target. Never
		// blocks the write either way.
		//
		// a_expectedPatchHash pins the check to a specific verified byte pattern (see
		// SKSE::Trampoline::write_branch's doc comment): 0 means unset (today's behavior,
		// always logs and prints the hash to capture), a match goes quiet (already verified,
		// nothing to re-read), a mismatch escalates (something changed since verification --
		// a different game binary, or a newly-installed patch colliding with this site).
		void check_patch_site_boundary(std::uintptr_t a_src, std::size_t a_len, std::uint64_t a_expectedPatchHash, std::source_location a_loc)
		{
			// Basename only -- the full compiler path buries the one token that identifies
			// the responsible patch (e.g. "actorvaluestorage_clear_race_crash.h").
			std::string_view file{ a_loc.file_name() };
			if (const auto sep = file.find_last_of("/\\"); sep != std::string_view::npos) {
				file.remove_prefix(sep + 1);
			}

			std::size_t consumed = 0;
			std::size_t instrCount = 0;
			std::size_t lastLen = 0;

			while (consumed < a_len) {
				hde64s     hs{};
				const auto len = hde64_disasm(reinterpret_cast<const void*>(a_src + consumed), &hs);
				if (len == 0 || (hs.flags & F_ERROR) != 0) {
					log::debug(
						"patch-site safety [{}:{}]: failed to decode instruction at 0x{:X} (+0x{:X} into a "
						"write_branch<{}> at 0x{:X}) -- skipping boundary check for this patch"sv,
						file, a_loc.line(), a_src + consumed, consumed, a_len, a_src);
					return;
				}
				consumed += len;
				lastLen = len;
				++instrCount;
			}

			if (consumed == a_len || instrCount == 1) {
				return;  // safe: exact boundary, or never left the first instruction
			}

			const auto badAddr = a_src + (consumed - lastLen);
			const auto overwritten = a_len - (consumed - lastLen);
			const auto hash = fnv1a64(badAddr, lastLen);

			if (a_expectedPatchHash != 0 && a_expectedPatchHash == hash) {
				log::trace(
					"patch-site safety [{}:{}]: write_branch<{}> at 0x{:X} matches its pinned hash "
					"0x{:X} -- already verified, nothing changed."sv,
					file, a_loc.line(), a_len, a_src, hash);
				return;
			}

			if (a_expectedPatchHash != 0 && a_expectedPatchHash != hash) {
				log::warn(
					"patch-site safety [{}:{}]: write_branch<{}> at 0x{:X} pinned hash 0x{:X} no longer "
					"matches the live bytes at 0x{:X} (now 0x{:X}) -- the verification this site relied "
					"on may no longer hold (different game binary, or another patch now overlaps this "
					"site). Re-verify: code xrefs (CALL/JMP) AND vtable slots holding 0x{:X} as a "
					"function pointer. Writing anyway for now."sv,
					file, a_loc.line(), a_len, a_src, a_expectedPatchHash, badAddr, hash, badAddr);
				return;
			}

			log::debug(
				"patch-site safety [{}:{}]: write_branch<{}> at 0x{:X} fully consumes {} instruction(s) then "
				"partially overwrites {} of {} bytes of the instruction at 0x{:X} (hash 0x{:X}) -- that "
				"address used to be a valid instruction start. Before treating this site as safe, check "
				"for anything targeting it directly: code xrefs (CALL/JMP) AND vtable slots holding it "
				"as a function pointer (indirect vtable dispatch won't show as a code xref). If clean, "
				"pass a_expectedPatchHash=0x{:X} to pin this verified state (re-checked every launch), "
				"or relocate the patch onto a longer instruction. Writing anyway for now."sv,
				file, a_loc.line(), a_len, a_src, instrCount - 1, overwritten, lastLen, badAddr, hash, hash);
		}
#endif

		[[nodiscard]] constexpr std::size_t roundup(std::size_t a_number, std::size_t a_multiple) noexcept
		{
			if (a_multiple == 0)
				return 0;

			const auto remainder = a_number % a_multiple;
			return (remainder == 0) ? a_number : (a_number + a_multiple - remainder);
		}

		[[nodiscard]] constexpr std::size_t rounddown(std::size_t a_number, std::size_t a_multiple) noexcept
		{
			if (a_multiple == 0)
				return 0;

			const auto remainder = a_number % a_multiple;
			return (remainder == 0) ? a_number : (a_number - remainder);
		}
	}

	void Trampoline::create(std::size_t a_size, void* a_module)
	{
		if (a_size == 0) {
			stl::report_and_fail("cannot create a trampoline with a zero size"sv);
		}

		if (!a_module) {
			const auto text = REL::Module::get().segment(REL::Segment::textx);
			a_module = text.pointer<std::byte>() + text.size();
		}

		auto mem = do_create(a_size, reinterpret_cast<std::uintptr_t>(a_module));
		if (!mem) {
			stl::report_and_fail("failed to create trampoline"sv);
		}

		set_trampoline(mem, a_size, [](void* a_mem, std::size_t) {
			REX::W32::VirtualFree(a_mem, 0, REX::W32::MEM_RELEASE);
		});
	}

#ifdef SKSE_SUPPORT_XBYAK
	void* Trampoline::allocate(Xbyak::CodeGenerator& a_code)
	{
		auto result = do_allocate(a_code.getSize());
		log_stats();
		std::memcpy(result, a_code.getCode(), a_code.getSize());
		return result;
	}
#endif

	// https://stackoverflow.com/a/54732489
	void* Trampoline::do_create(std::size_t a_size, std::uintptr_t a_address)
	{
		constexpr std::size_t    gigabyte = static_cast<std::size_t>(1) << 30;
		constexpr std::size_t    minRange = gigabyte * 2;
		constexpr std::uintptr_t maxAddr = (std::numeric_limits<std::uintptr_t>::max)();

		REX::W32::SYSTEM_INFO si;
		REX::W32::GetSystemInfo(&si);
		const std::uint32_t granularity = si.allocationGranularity;

		std::uintptr_t       min = a_address >= minRange ? detail::roundup(a_address - minRange, granularity) : 0;
		const std::uintptr_t max = a_address < (maxAddr - minRange) ? detail::rounddown(a_address + minRange, granularity) : maxAddr;

		REX::W32::MEMORY_BASIC_INFORMATION mbi;
		do {
			if (!REX::W32::VirtualQuery(reinterpret_cast<void*>(min), std::addressof(mbi), sizeof(mbi))) {
				log::error("VirtualQuery failed with code: 0x{:08X}"sv, REX::W32::GetLastError());
				return nullptr;
			}

			const auto baseAddr = reinterpret_cast<std::uintptr_t>(mbi.baseAddress);
			min = baseAddr + mbi.regionSize;

			if (mbi.state == REX::W32::MEM_FREE) {
				const std::uintptr_t addr = detail::roundup(baseAddr, granularity);

				// if rounding didn't advance us into the next region and the region is the required size
				if (addr < min && (min - addr) >= a_size) {
					const auto mem = REX::W32::VirtualAlloc(
						reinterpret_cast<void*>(addr), a_size, REX::W32::MEM_COMMIT | REX::W32::MEM_RESERVE, REX::W32::PAGE_EXECUTE_READWRITE);
					if (mem) {
						return mem;
					}
					log::warn("VirtualAlloc failed with code: 0x{:08X}"sv, REX::W32::GetLastError());
				}
			}
		} while (min < max);

		return nullptr;
	}

	void* Trampoline::do_allocate(std::size_t a_size)
	{
		if (a_size > free_size()) {
			stl::report_and_fail("Failed to handle allocation request"sv);
		}

		auto mem = _data + _size;
		_size += a_size;

		return mem;
	}

	void Trampoline::write_5branch(std::uintptr_t a_src, std::uintptr_t a_dst, std::uint8_t a_opcode, bool a_skipSafetyCheck, std::uint64_t a_expectedPatchHash, std::source_location a_loc)
	{
#pragma pack(push, 1)
		struct SrcAssembly
		{
			// jmp/call [rip + imm32]
			std::uint8_t opcode;  // 0 - 0xE9/0xE8
			std::int32_t disp;    // 1
		};
		static_assert(offsetof(SrcAssembly, opcode) == 0x0);
		static_assert(offsetof(SrcAssembly, disp) == 0x1);
		static_assert(sizeof(SrcAssembly) == 0x5);

		// FF /4
		// JMP r/m64
		struct TrampolineAssembly
		{
			// jmp [rip]
			std::uint8_t  jmp;    // 0 - 0xFF
			std::uint8_t  modrm;  // 1 - 0x25
			std::int32_t  disp;   // 2 - 0x00000000
			std::uint64_t addr;   // 6 - [rip]
		};
		static_assert(offsetof(TrampolineAssembly, jmp) == 0x0);
		static_assert(offsetof(TrampolineAssembly, modrm) == 0x1);
		static_assert(offsetof(TrampolineAssembly, disp) == 0x2);
		static_assert(offsetof(TrampolineAssembly, addr) == 0x6);
		static_assert(sizeof(TrampolineAssembly) == 0xE);
#pragma pack(pop)

		TrampolineAssembly* mem = nullptr;
		if (const auto it = _5branches.find(a_dst); it != _5branches.end()) {
			mem = reinterpret_cast<TrampolineAssembly*>(it->second);
		} else {
			mem = allocate<TrampolineAssembly>();
			_5branches.emplace(a_dst, reinterpret_cast<std::byte*>(mem));
		}

		const auto disp =
			reinterpret_cast<const std::byte*>(mem) -
			reinterpret_cast<const std::byte*>(a_src + sizeof(SrcAssembly));
		if (!in_range(disp)) {  // the trampoline should already be in range, so this should never happen
			stl::report_and_fail("displacement is out of range"sv);
		}

#ifdef SKSE_SUPPORT_PATCH_SAFETY
		if (!a_skipSafetyCheck) {
			detail::check_patch_site_boundary(a_src, sizeof(SrcAssembly), a_expectedPatchHash, a_loc);
		}
#endif

		SrcAssembly assembly;
		assembly.opcode = a_opcode;
		assembly.disp = static_cast<std::int32_t>(disp);
		REL::safe_write(a_src, &assembly, sizeof(assembly));

		mem->jmp = static_cast<std::uint8_t>(0xFF);
		mem->modrm = static_cast<std::uint8_t>(0x25);
		mem->disp = static_cast<std::int32_t>(0);
		mem->addr = static_cast<std::uint64_t>(a_dst);
	}

	void Trampoline::write_6branch(std::uintptr_t a_src, std::uintptr_t a_dst, std::uint8_t a_modrm, bool a_skipSafetyCheck, std::uint64_t a_expectedPatchHash, std::source_location a_loc)
	{
#pragma pack(push, 1)
		struct Assembly
		{
			// jmp/call [rip + imm32]
			std::uint8_t opcode;  // 0 - 0xFF
			std::uint8_t modrm;   // 1 - 0x25/0x15
			std::int32_t disp;    // 2
		};
		static_assert(offsetof(Assembly, opcode) == 0x0);
		static_assert(offsetof(Assembly, modrm) == 0x1);
		static_assert(offsetof(Assembly, disp) == 0x2);
		static_assert(sizeof(Assembly) == 0x6);
#pragma pack(pop)

		std::uintptr_t* mem = nullptr;
		if (const auto it = _6branches.find(a_dst); it != _6branches.end()) {
			mem = reinterpret_cast<std::uintptr_t*>(it->second);
		} else {
			mem = allocate<std::uintptr_t>();
			_6branches.emplace(a_dst, reinterpret_cast<std::byte*>(mem));
		}

		const auto disp =
			reinterpret_cast<const std::byte*>(mem) -
			reinterpret_cast<const std::byte*>(a_src + sizeof(Assembly));
		if (!in_range(disp)) {  // the trampoline should already be in range, so this should never happen
			stl::report_and_fail("displacement is out of range"sv);
		}

#ifdef SKSE_SUPPORT_PATCH_SAFETY
		if (!a_skipSafetyCheck) {
			detail::check_patch_site_boundary(a_src, sizeof(Assembly), a_expectedPatchHash, a_loc);
		}
#endif

		Assembly assembly;
		assembly.opcode = static_cast<std::uint8_t>(0xFF);
		assembly.modrm = a_modrm;
		assembly.disp = static_cast<std::int32_t>(disp);
		REL::safe_write(a_src, &assembly, sizeof(assembly));

		*mem = a_dst;
	}

	void Trampoline::log_stats() const
	{
		const auto pct = (static_cast<double>(_size) / static_cast<double>(_capacity)) * 100.0;
		log::debug("{} => {}B / {}B ({:05.2f}%)"sv, _name, _size, _capacity, pct);
	}

	Trampoline& GetTrampoline()
	{
		static Trampoline trampoline;
		return trampoline;
	}
}

#pragma once

namespace REL
{
	// FNV-1a 64-bit hash of a byte range. Not a security hash -- a cheap, deterministic
	// change-detector for hook-integrity verification: "are these bytes still what I
	// verified them to be."
	[[nodiscard]] std::uint64_t HashBytes(std::uintptr_t a_addr, std::size_t a_len) noexcept;

	enum class VerifyResult
	{
		kUnset,     // a_expectedHash was 0 -- no pin to compare against
		kMatch,     // live bytes hash to the pinned value
		kMismatch,  // live bytes differ from the pinned value
	};

	// Verifies [a_addr, a_addr + a_len) against a_expectedHash and logs the result:
	//   unset    -> debug, and prints the live hash so a caller can capture + pin it.
	//   match    -> trace (quiet -- already verified, nothing changed).
	//   mismatch -> warn (loud -- something changed since the pin was captured: a different
	//               game binary, or another patch now overlapping this range).
	//
	// General-purpose hook-integrity primitive, not tied to any specific patch mechanism:
	// pin a patch's own target bytes before writing, a downstream collateral range after
	// writing, or any other hook-adjacent byte range worth tracking for silent drift.
	// Never fails/blocks by itself -- callers that want fail-closed behavior on kMismatch
	// (e.g. skip a patch whose target bytes no longer match) check the return value.
	VerifyResult VerifyBytes(
		std::uintptr_t       a_addr,
		std::size_t          a_len,
		std::uint64_t        a_expectedHash,
		std::string_view     a_context,
		std::source_location a_loc = std::source_location::current());
}

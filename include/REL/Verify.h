#pragma once

namespace REL
{
	// FNV-1a 64-bit -- a change-detector, not a security hash.
	[[nodiscard]] std::uint64_t HashBytes(std::uintptr_t a_addr, std::size_t a_len) noexcept;

	enum class VerifyResult
	{
		kUnset,     // a_expectedHash was 0 -- no pin to compare against
		kMatch,     // live bytes hash to the pinned value
		kMismatch,  // live bytes differ from the pinned value
	};

	// Verifies [a_addr, a_addr + a_len) against a_expectedHash: unset logs the live hash to
	// capture, match stays quiet, mismatch warns. Never blocks -- callers wanting fail-closed
	// behavior check the returned VerifyResult themselves.
	VerifyResult VerifyBytes(
		std::uintptr_t       a_addr,
		std::size_t          a_len,
		std::uint64_t        a_expectedHash,
		std::string_view     a_context,
		std::source_location a_loc = std::source_location::current());
}

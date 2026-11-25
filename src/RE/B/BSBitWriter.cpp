#include "RE/B/BSBitWriter.h"

namespace RE
{
	namespace BSScript
	{
		BSBitWriter::BSBitWriter(std::uint64_t* a_words) :
			words(a_words) {}

		[[nodiscard]] std::uint32_t BSBitWriter::Position() const { return static_cast<std::uint32_t>(position); }

		void BSBitWriter::Write(const std::uint64_t a_value, const std::uint32_t a_count)  // a_count < 64
		{
			assert(a_count < 64);
			WriteAt(position, a_value, a_count);
			position += a_count;
		}

		void BSBitWriter::WriteAt(const std::uint64_t a_position, const std::uint64_t a_value, const std::uint32_t a_count)
		{
			assert(a_count < 64);
			if (a_count == 0) {
				return;
			}
			const std::uint64_t mask = (std::uint64_t{ 1 } << a_count) - 1;
			const std::uint64_t value = a_value & mask;
			const auto          word = a_position >> 6;
			const auto          shift = static_cast<std::uint32_t>(a_position & 63);

			words[word] = (words[word] & ~(mask << shift)) | (value << shift);
			if (shift + a_count > 64) {
				const auto spill = 64 - shift;
				words[word + 1] = (words[word + 1] & ~(mask >> spill)) | (value >> spill);
			}
		}
	}
}

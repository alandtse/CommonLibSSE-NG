#pragma once

namespace RE::BSScript
{
	struct BSBitWriter
	{
	public:
		explicit BSBitWriter(std::uint64_t* a_words);

		[[nodiscard]] std::uint32_t Position() const;

		void Write(const std::uint64_t a_value, const std::uint32_t a_count);

		void WriteAt(const std::uint64_t a_position, const std::uint64_t a_value, const std::uint32_t a_count);

	private:
		std::uint64_t* words;
		std::uint64_t  position{ 0 };
	};
}

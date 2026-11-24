#include "REL/Version.h"

#include "REX/W32/VERSION.h"

#include <sstream>
#include <vector>

namespace REL
{
	namespace
	{
		template <class CharT>
		std::optional<Version> ParseProductVersion(const void* a_verBuf, std::uint32_t a_verLen, CharT a_delim)
		{
			Version                         version;
			std::basic_istringstream<CharT> ss(std::basic_string<CharT>(static_cast<const CharT*>(a_verBuf), a_verLen));
			std::basic_string<CharT>        token;
			for (std::size_t i = 0; i < 4 && std::getline(ss, token, a_delim); ++i) {
				version[i] = static_cast<std::uint16_t>(std::stoi(token));
			}
			return version;
		}
	}

	std::optional<Version> GetFileVersion(std::string_view a_filename)
	{
		const std::string filename(a_filename);
		std::uint32_t     dummy;
		std::vector<char> buf(REX::W32::GetFileVersionInfoSizeA(filename.c_str(), std::addressof(dummy)));
		if (buf.empty()) {
			return std::nullopt;
		}

		if (!REX::W32::GetFileVersionInfoA(filename.c_str(), 0, static_cast<std::uint32_t>(buf.size()), buf.data())) {
			return std::nullopt;
		}

		void*         verBuf{ nullptr };
		std::uint32_t verLen{ 0 };
		if (!REX::W32::VerQueryValueA(buf.data(), "\\StringFileInfo\\040904B0\\ProductVersion", std::addressof(verBuf), std::addressof(verLen))) {
			return std::nullopt;
		}

		return ParseProductVersion<char>(verBuf, verLen, '.');
	}

	std::optional<Version> GetFileVersion(std::wstring_view a_filename)
	{
		const std::wstring filename(a_filename);
		std::uint32_t      dummy;
		std::vector<char>  buf(REX::W32::GetFileVersionInfoSizeW(filename.c_str(), std::addressof(dummy)));
		if (buf.empty()) {
			return std::nullopt;
		}

		if (!REX::W32::GetFileVersionInfoW(filename.c_str(), 0, static_cast<std::uint32_t>(buf.size()), buf.data())) {
			return std::nullopt;
		}

		void*         verBuf{ nullptr };
		std::uint32_t verLen{ 0 };
		if (!REX::W32::VerQueryValueW(buf.data(), L"\\StringFileInfo\\040904B0\\ProductVersion", std::addressof(verBuf), std::addressof(verLen))) {
			return std::nullopt;
		}

		return ParseProductVersion<wchar_t>(verBuf, verLen, L'.');
	}
}

#include "REL/ID.h"

#include "REX/W32/KERNEL32.h"

#ifdef ENABLE_SKYRIM_VR
#	include <glaze/glaze.hpp>
#	include <fstream>
#	include <sstream>
#endif

namespace REL
{
	namespace detail
	{
		bool memory_map::open(stl::zwstring a_name, std::size_t a_size)
		{
			close();

			REX::W32::ULARGE_INTEGER bytes;
			bytes.value = a_size;

			_mapping = REX::W32::OpenFileMappingW(
				REX::W32::FILE_MAP_READ | REX::W32::FILE_MAP_WRITE,
				false,
				a_name.data());
			if (!_mapping) {
				close();
				return false;
			}

			_view = REX::W32::MapViewOfFile(
				_mapping,
				REX::W32::FILE_MAP_READ | REX::W32::FILE_MAP_WRITE,
				0,
				0,
				bytes.value);
			if (!_view) {
				close();
				return false;
			}

			return true;
		}

		bool memory_map::create(stl::zwstring a_name, std::size_t a_size)
		{
			close();

			REX::W32::ULARGE_INTEGER bytes;
			bytes.value = a_size;

			_mapping = REX::W32::OpenFileMappingW(
				REX::W32::FILE_MAP_READ | REX::W32::FILE_MAP_WRITE,
				false,
				a_name.data());
			if (!_mapping) {
				_mapping = REX::W32::CreateFileMappingW(
					REX::W32::INVALID_HANDLE_VALUE,
					nullptr,
					REX::W32::PAGE_READWRITE,
					bytes.hi,
					bytes.lo,
					a_name.data());
				if (!_mapping) {
					return false;
				}
			}

			_view = REX::W32::MapViewOfFile(
				_mapping,
				REX::W32::FILE_MAP_READ | REX::W32::FILE_MAP_WRITE,
				0,
				0,
				bytes.value);
			if (!_view) {
				return false;
			}

			return true;
		}

		void memory_map::close()
		{
			if (_view) {
				REX::W32::UnmapViewOfFile(static_cast<const void*>(_view));
				_view = nullptr;
			}

			if (_mapping) {
				REX::W32::CloseHandle(_mapping);
				_mapping = nullptr;
			}
		}
	}

	IDDatabase IDDatabase::_instance;

	bool IDDatabase::load_file(stl::zwstring a_filename, Version a_version, std::uint8_t a_formatVersion, bool a_failOnError)
	{
		try {
			istream_t in(a_filename.data(), std::ios::in | std::ios::binary);
			header_t  header;
			header.read(in, a_formatVersion);
			if (header.version() != a_version) {
				return stl::report_and_error("version mismatch"sv, a_failOnError);
			}

			auto mapname = L"CommonLibSSEOffsets-v2-"s;
			mapname += a_version.wstring();
			const auto byteSize = static_cast<std::size_t>(header.address_count()) * sizeof(mapping_t);
			if (_mmap.open(mapname, byteSize)) {
				_id2offset = { static_cast<mapping_t*>(_mmap.data()), header.address_count() };
			} else if (_mmap.create(mapname, byteSize)) {
				_id2offset = { static_cast<mapping_t*>(_mmap.data()), header.address_count() };
				unpack_file(in, header, a_failOnError);
				std::sort(_id2offset.begin(), _id2offset.end(), [](auto&& a_lhs, auto&& a_rhs) {
					return a_lhs.id < a_rhs.id;
				});
			} else {
				return stl::report_and_error("failed to create shared mapping"sv, a_failOnError);
			}
		} catch (const std::system_error&) {
			return stl::report_and_error(
				std::format(
					"Failed to locate an appropriate address library with the path: {}\n"
					"This means you are missing the address library for this specific version of "
					"the game. Please continue to the mod page for address library to download "
					"an appropriate version. If one is not available, then it is likely that "
					"address library has not yet added support for this version of the game."sv,
					stl::utf16_to_utf8(a_filename).value_or("<unknown filename>"s)),
				a_failOnError);
			return false;
		}

		return true;
	}

#ifdef ENABLE_SKYRIM_VR
	bool IDDatabase::load_csv(stl::zwstring a_filename, Version a_version, bool a_failOnError)
	{
		auto nstring = SKSE::stl::utf16_to_utf8(a_filename).value_or(""s);
		if (!std::filesystem::exists(nstring)) {
			return stl::report_and_error(
				std::format("Required VR Address Library file {} does not exist"sv, nstring),
				a_failOnError);
		}

		// Read CSV file using glaze
		std::ifstream file(nstring);
		if (!file.is_open()) {
			return stl::report_and_error(
				std::format("Failed to open VR Address Library file {}"sv, nstring),
				a_failOnError);
		}

		std::vector<std::string> lines;
		std::string              line;
		while (std::getline(file, line)) {
			if (!line.empty()) {
				lines.push_back(line);
			}
		}
		file.close();

		if (lines.empty()) {
			return stl::report_and_error("VR Address Library file is empty"sv, a_failOnError);
		}

		// Parse header row (first row contains address_count and version)
		std::size_t        address_count;
		std::string        version;
		std::istringstream header_stream(lines[0]);
		std::string        cell;

		// Skip the "id" header
		if (!std::getline(header_stream, cell, ',')) {
			return stl::report_and_error("Failed to parse CSV header"sv, a_failOnError);
		}

		// Get address_count from first cell (which is actually in the data row)
		// The CSV format is: first row has headers, second row has address_count and version
		if (lines.size() < 2) {
			return stl::report_and_error("VR Address Library file has insufficient rows"sv, a_failOnError);
		}

		std::istringstream first_data_stream(lines[1]);
		if (!std::getline(first_data_stream, cell, ',')) {
			return stl::report_and_error("Failed to parse first data row"sv, a_failOnError);
		}
		address_count = std::stoull(cell);

		if (!std::getline(first_data_stream, cell, ',')) {
			return stl::report_and_error("Failed to parse version from first data row"sv, a_failOnError);
		}
		version = cell;

		_vrAddressLibraryVersion = Version(version);
		auto mapname = L"CommonLibSSEOffsets-v2-"s;
		mapname += a_version.wstring();
		const auto byteSize = static_cast<std::size_t>(address_count * sizeof(mapping_t));
		if (!_mmap.open(mapname, byteSize) &&
			!_mmap.create(mapname, byteSize)) {
			return stl::report_and_error("failed to create shared mapping"sv, a_failOnError);
		}

		_id2offset = { static_cast<mapping_t*>(_mmap.data()), static_cast<std::size_t>(address_count) };
		
		// Total data rows (excluding header) should be: 1 metadata row + address_count data rows
		const std::size_t data_row_count = lines.size() - 1;  // Exclude header line
		const std::size_t expected_data_rows = address_count + 1;
		if (data_row_count > expected_data_rows) {
			return stl::report_and_error(
				std::format("VR Address Library {} tried to exceed {} allocated entries."sv,
					version, address_count),
				a_failOnError);
		} else if (data_row_count < expected_data_rows) {
			return stl::report_and_error(
				std::format("VR Address Library {} loaded only {} entries but expected {}. Please redownload."sv,
					version, data_row_count - 1, address_count),
				a_failOnError);
		}

		// Parse data rows (starting from index 2, after header and metadata)
		for (std::size_t index = 2; index < lines.size(); ++index) {
			std::istringstream row_stream(lines[index]);
			std::string        id_str, offset_str;

			if (!std::getline(row_stream, id_str, ',')) {
				return stl::report_and_error(
					std::format("Failed to parse ID at row {}"sv, index),
					a_failOnError);
			}

			if (!std::getline(row_stream, offset_str, ',')) {
				return stl::report_and_error(
					std::format("Failed to parse offset at row {}"sv, index),
					a_failOnError);
			}

			auto id = std::stoull(id_str);
			auto offset = std::stoull(offset_str, nullptr, 16);

			_id2offset[index - 2] = { id, offset };
		}

		std::sort(_id2offset.begin(), _id2offset.end(), [](auto&& a_lhs, auto&& a_rhs) {
			return a_lhs.id < a_rhs.id;
		});

		return true;
	}

	bool IDDatabase::IsVRAddressLibraryAtLeastVersion(const char* a_minimalVRAddressLibVersion, bool a_reportAndFail) const
	{
		const auto minimalVersion = REL::Version(a_minimalVRAddressLibVersion);

		if (minimalVersion <= _vrAddressLibraryVersion) {
			return true;
		}

		if (!a_reportAndFail) {
			return false;
		}

		stl::report_and_fail(
			std::format("You need version: {} of VR Address Library for SKSEVR, you have version: {}"sv,
				minimalVersion, _vrAddressLibraryVersion));
	}
#endif
}

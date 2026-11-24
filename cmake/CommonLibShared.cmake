include(FetchContent)

# Fallback when find_package(commonlib-shared) is unavailable (e.g. add_subdirectory
# consumers whose vcpkg manifest doesn't declare the overlay port). Fetches the
# pinned libxse/commonlib-shared archive and builds only its REX subset, keeping
# CommonLibSSE-NG's multi-runtime REL implementation isolated from commonlib-shared's REL.
FetchContent_Declare(
	commonlib_shared
	URL https://github.com/libxse/commonlib-shared/archive/def5f6c93db28d20307d8e55a62118fc1c4f0b6c.tar.gz
	URL_HASH SHA512=79e7fed14f077daa1903a5aa45763e8babc66c81fa32e37836adedc9c7e098779bfcfd787dfdb8a7183fc3b1bb75995786270b954b4b356ceb623c947e2e372d
	SOURCE_SUBDIR include/REX
)
FetchContent_MakeAvailable(commonlib_shared)

set(_commonlib_shared_include_dir "${CMAKE_CURRENT_BINARY_DIR}/_commonlib_shared_include")
file(COPY "${commonlib_shared_SOURCE_DIR}/include/REX" DESTINATION "${_commonlib_shared_include_dir}")

include("${commonlib_shared_SOURCE_DIR}/res/cmake/sourcelist.cmake")
set(_commonlib_shared_sources)
foreach(_entry IN LISTS SOURCES)
	if(_entry MATCHES "^src/REX/.*\\.cpp$")
		list(APPEND _commonlib_shared_sources "${commonlib_shared_SOURCE_DIR}/${_entry}")
	elseif(_entry MATCHES "^include/REX/.*\\.h$")
		string(REGEX REPLACE "^include/" "" _rel_header "${_entry}")
		list(APPEND _commonlib_shared_sources "${_commonlib_shared_include_dir}/${_rel_header}")
	endif()
endforeach()
unset(SOURCES)

if(COMMONLIB_INI)
	find_package(SimpleIni REQUIRED CONFIG)
endif()
if(COMMONLIB_JSON)
	find_package(glaze REQUIRED CONFIG)
endif()
if(COMMONLIB_TOML)
	find_package(toml11 REQUIRED CONFIG)
endif()
if(COMMONLIB_RANDOM)
	find_package(xoshiro-cpp REQUIRED CONFIG)
endif()

add_library(
	commonlib-shared
	STATIC
	${_commonlib_shared_sources}
)
add_library(commonlib-shared::commonlib-shared ALIAS commonlib-shared)

target_compile_definitions(
	commonlib-shared
	PUBLIC
	"$<$<BOOL:${COMMONLIB_INI}>:COMMONLIB_OPTION_INI=1>"
	"$<$<BOOL:${COMMONLIB_JSON}>:COMMONLIB_OPTION_JSON=1>"
	"$<$<BOOL:${COMMONLIB_TOML}>:COMMONLIB_OPTION_TOML=1>"
	"$<$<BOOL:${COMMONLIB_RANDOM}>:COMMONLIB_OPTION_RANDOM=1>"
)

target_compile_features(commonlib-shared PUBLIC cxx_std_23)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_options(
		commonlib-shared
		PUBLIC
		/we4715
		/wd4200
		/wd4201
		/wd4324
		/wd4702
	)
endif()

target_include_directories(
	commonlib-shared
	PUBLIC
	"$<BUILD_INTERFACE:${_commonlib_shared_include_dir}>"
	"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(
	commonlib-shared
	PUBLIC
	spdlog::spdlog
	advapi32.lib
	bcrypt.lib
	d3d11.lib
	d3dcompiler.lib
	dbghelp.lib
	dxgi.lib
	ole32.lib
	shell32.lib
	user32.lib
	version.lib
	ws2_32.lib
	"$<$<BOOL:${COMMONLIB_INI}>:SimpleIni::SimpleIni>"
	"$<$<BOOL:${COMMONLIB_JSON}>:glaze::glaze>"
	"$<$<BOOL:${COMMONLIB_TOML}>:toml11::toml11>"
	"$<$<BOOL:${COMMONLIB_RANDOM}>:xoshiro-cpp::xoshiro-cpp>"
)

target_precompile_headers(
	commonlib-shared
	PRIVATE
	"${commonlib_shared_SOURCE_DIR}/src/REX/PCH.h"
)

set(COMMONLIB_SHARED_FROM_FETCHCONTENT TRUE)

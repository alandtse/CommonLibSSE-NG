vcpkg_check_linkage(ONLY_STATIC_LIBRARY)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO libxse/commonlib-shared
    REF def5f6c93db28d20307d8e55a62118fc1c4f0b6c
    SHA512 79e7fed14f077daa1903a5aa45763e8babc66c81fa32e37836adedc9c7e098779bfcfd787dfdb8a7183fc3b1bb75995786270b954b4b356ceb623c947e2e372d
    HEAD_REF main
)

# CommonLibSSE-NG provides its own multi-runtime REL implementation (SE/AE/VR);
# keep src/REL/Utility.cpp for FModule::SetImportFunctionPointer while stripping
# commonlib-shared's other single-runtime REL sources and all REL headers from install.
set(SOURCELIST_PATH "${SOURCE_PATH}/res/cmake/sourcelist.cmake")
file(STRINGS "${SOURCELIST_PATH}" SOURCELIST_LINES)
set(FILTERED_SOURCELIST_LINES)
foreach(SOURCELIST_LINE IN LISTS SOURCELIST_LINES)
    if(SOURCELIST_LINE MATCHES "^[ \t]*(include/REL/.*\\.h|src/REL/.*)$"
       AND NOT SOURCELIST_LINE MATCHES "^[ \t]*src/REL/Utility\\.cpp$")
        continue()
    endif()

    list(APPEND FILTERED_SOURCELIST_LINES "${SOURCELIST_LINE}")
endforeach()
list(JOIN FILTERED_SOURCELIST_LINES "\n" FILTERED_SOURCELIST)
file(WRITE "${SOURCELIST_PATH}" "${FILTERED_SOURCELIST}\n")

set(CMAKELISTS_PATH "${SOURCE_PATH}/CMakeLists.txt")
file(READ "${CMAKELISTS_PATH}" CMAKELISTS)
string(REPLACE
    "            /wd4324 # structure was padded due to alignment specifier"
    "            /wd4324 # structure was padded due to alignment specifier\n            /wd4702 # unreachable code in fmt ranges with spdlog wchar support"
    CMAKELISTS
    "${CMAKELISTS}"
)
string(REPLACE
    "\t\t\"include/REL\"\n"
    ""
    CMAKELISTS
    "${CMAKELISTS}"
)
file(WRITE "${CMAKELISTS_PATH}" "${CMAKELISTS}")

vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    FEATURES
        ini    COMMONLIB_INI
        json   COMMONLIB_JSON
        random COMMONLIB_RANDOM
        toml   COMMONLIB_TOML
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS ${FEATURE_OPTIONS}
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(
    PACKAGE_NAME commonlib-shared
    CONFIG_PATH lib/cmake/commonlib-shared
)

file(REMOVE_RECURSE
    "${CURRENT_PACKAGES_DIR}/debug/include"
    "${CURRENT_PACKAGES_DIR}/include/REL"
)

vcpkg_install_copyright(
    FILE_LIST
        "${SOURCE_PATH}/LICENSE"
        "${SOURCE_PATH}/EXCEPTIONS"
)

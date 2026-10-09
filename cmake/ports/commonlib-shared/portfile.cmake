vcpkg_check_linkage(ONLY_STATIC_LIBRARY)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO libxse/commonlib-shared
    REF 29fbdb0e2dc548c9ab22f6964981d75090dc9094
    SHA512 dc52af0e385755f7947553feac61f3731cacd02cf0f7a858512bfcaa7348ed642ddd11f8d555fd4e34b4c035172d35ba6e95d1b49cb41ec68303afe53bba6734
    HEAD_REF main
)

set(SOURCELIST_PATH "${SOURCE_PATH}/res/cmake/sourcelist.cmake")
file(STRINGS "${SOURCELIST_PATH}" SOURCELIST_LINES)
set(FILTERED_SOURCELIST_LINES)
foreach(SOURCELIST_LINE IN LISTS SOURCELIST_LINES)
    if(SOURCELIST_LINE MATCHES "^[ \t]*(include/REL/.*\\.h|src/REL/.*)$")
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
file(WRITE "${CMAKELISTS_PATH}" "${CMAKELISTS}")

vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    FEATURES
        ini    COMMONLIB_INI
        json   COMMONLIB_JSON
		random COMMONLIB_RANDOM
        toml   COMMONLIB_TOML
        xbyak  COMMONLIB_XBYAK

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

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(REMOVE_RECURSE
    "${CURRENT_PACKAGES_DIR}/include/REL"
    "${CURRENT_PACKAGES_DIR}/src/REL"
)

vcpkg_install_copyright(
    FILE_LIST
        "${SOURCE_PATH}/LICENSE"
        "${SOURCE_PATH}/EXCEPTIONS"
)

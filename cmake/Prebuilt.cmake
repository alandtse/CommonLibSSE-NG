# Resolve a directory containing a prebuilt CommonLibSSE.lib (+ include/, openvr) so
# add_subdirectory consumers can link the published binary instead of compiling ~16 min
# of source. Mirrors the xmake clean-tag auto-fetch.
#
# A directory is resolved from, in order:
#   1. COMMONLIB_PREBUILT_DIR, if it points at an already-extracted bundle, else
#   2. on a CLEAN release tag, in CI (GITHUB_ACTIONS) or with COMMONLIB_PREBUILT set, the
#      matching cmake bundle downloaded from the GitHub release and SHA256-verified.
# Anything else (no exact tag, dirty tree, options that don't match the baked config,
# missing/unverified asset, offline) leaves the output empty so the caller builds from
# source. The download is cached under the build tree and attempted at most once per tag.
function(commonlib_resolve_prebuilt out_dir)
    set(${out_dir} "" PARENT_SCOPE)

    # explicit override: a consumer (or this repo's self-test) points at an extracted bundle
    if(COMMONLIB_PREBUILT_DIR AND EXISTS "${COMMONLIB_PREBUILT_DIR}/lib/CommonLibSSE.lib")
        set(${out_dir} "${COMMONLIB_PREBUILT_DIR}" PARENT_SCOPE)
        return()
    endif()

    if(NOT (DEFINED ENV{GITHUB_ACTIONS} OR COMMONLIB_PREBUILT))
        return()
    endif()

    # options must match the config the bundle was baked with (skyrim all + rex_ini +
    # skse_xbyak; rex_json/toml off) — otherwise the headers/lib would mismatch ABI.
    if(NOT (ENABLE_SKYRIM_SE AND ENABLE_SKYRIM_AE AND ENABLE_SKYRIM_VR
            AND REX_OPTION_INI AND SKSE_SUPPORT_XBYAK)
       OR REX_OPTION_JSON OR REX_OPTION_TOML)
        return()
    endif()

    find_package(Git QUIET)
    if(NOT Git_FOUND)
        return()
    endif()
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" -C "${CMAKE_CURRENT_SOURCE_DIR}" describe --tags --exact-match --dirty
        OUTPUT_VARIABLE _tag OUTPUT_STRIP_TRAILING_WHITESPACE
        RESULT_VARIABLE _rc ERROR_QUIET)
    if(NOT _rc EQUAL 0 OR _tag MATCHES "dirty" OR NOT _tag MATCHES "^v[0-9]")
        return()
    endif()

    set(_cache "${CMAKE_CURRENT_BINARY_DIR}/.prebuilt/${_tag}")
    if(EXISTS "${_cache}/lib/CommonLibSSE.lib")
        set(${out_dir} "${_cache}" PARENT_SCOPE)
        return()
    endif()
    if(EXISTS "${_cache}/.failed")
        return()
    endif()

    set(_base "https://github.com/alandtse/CommonLibVR/releases/download/${_tag}")
    set(_asset "commonlibsse-ng-prebuilt-${_tag}-all-msvc-cmake.zip")
    set(_zip "${_cache}.zip")
    file(DOWNLOAD "${_base}/${_asset}.sha256" "${_cache}.sha256" STATUS _s1)
    list(GET _s1 0 _s1code)
    if(NOT _s1code EQUAL 0)
        file(MAKE_DIRECTORY "${_cache}")
        file(TOUCH "${_cache}/.failed")
        return()
    endif()
    file(READ "${_cache}.sha256" _shaline)
    string(REGEX MATCH "[0-9a-fA-F]+" _want "${_shaline}")
    file(DOWNLOAD "${_base}/${_asset}" "${_zip}" EXPECTED_HASH "SHA256=${_want}" STATUS _s2)
    list(GET _s2 0 _s2code)
    if(NOT _s2code EQUAL 0)
        file(MAKE_DIRECTORY "${_cache}")
        file(TOUCH "${_cache}/.failed")
        return()
    endif()
    file(ARCHIVE_EXTRACT INPUT "${_zip}" DESTINATION "${_cache}.x")
    file(GLOB_RECURSE _found "${_cache}.x/*/lib/CommonLibSSE.lib")
    if(NOT _found)
        file(MAKE_DIRECTORY "${_cache}")
        file(TOUCH "${_cache}/.failed")
        return()
    endif()
    get_filename_component(_root "${_found}" DIRECTORY)        # .../lib
    get_filename_component(_root "${_root}" DIRECTORY)         # bundle root
    file(RENAME "${_root}" "${_cache}")
    set(${out_dir} "${_cache}" PARENT_SCOPE)
endfunction()

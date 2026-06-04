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
# A bundle is only usable if all four pieces the IMPORTED target consumes are present
# (include/, the lib, openvr lib + headers); otherwise a partial extraction or stale cache
# would resolve and fail deep in configure/build instead of falling back to source.
function(_commonlib_prebuilt_complete dir out_var)
    if(IS_DIRECTORY "${dir}/include"
       AND EXISTS "${dir}/lib/CommonLibSSE.lib"
       AND EXISTS "${dir}/lib/openvr_api.lib"
       AND IS_DIRECTORY "${dir}/extern/openvr/headers")
        set(${out_var} TRUE PARENT_SCOPE)
    else()
        set(${out_var} FALSE PARENT_SCOPE)
    endif()
endfunction()

function(commonlib_resolve_prebuilt out_dir)
    set(${out_dir} "" PARENT_SCOPE)

    # Auto-fetch only makes sense for add_subdirectory consumers. When CommonLibSSE is the
    # top-level project (developing or releasing CommonLib itself, including the bundle
    # producer building at a release tag) always build from source.
    if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
        return()
    endif()

    # The bundle is baked Release (/MD, NDEBUG). Linking it from a Debug config (/MDd) is a
    # CRT/ABI mismatch, and a multi-config generator can't promise the chosen config at
    # configure time — so only use the prebuilt for a single-config, non-Debug build.
    if(CMAKE_CONFIGURATION_TYPES OR NOT CMAKE_BUILD_TYPE MATCHES "^(Release|RelWithDebInfo|MinSizeRel)$")
        return()
    endif()

    # explicit override: a consumer (or this repo's self-test) points at an extracted bundle
    if(COMMONLIB_PREBUILT_DIR)
        _commonlib_prebuilt_complete("${COMMONLIB_PREBUILT_DIR}" _ok)
        if(_ok)
            set(${out_dir} "${COMMONLIB_PREBUILT_DIR}" PARENT_SCOPE)
            return()
        endif()
    endif()

    if(NOT (DEFINED ENV{GITHUB_ACTIONS} OR COMMONLIB_PREBUILT))
        return()
    endif()

    # options must be compatible with the baked config (skyrim all + skse_xbyak + rex_ini;
    # rex_json/toml off). The runtime set and skse_xbyak change public-header layout, so they
    # must match exactly. rex_ini/json/toml each only add a self-contained REX::{INI,JSON,TOML}
    # namespace: the lib bakes rex_ini, so it is a superset for ini (a rex_ini-OFF consumer
    # just never sees REX::INI) and rex_ini is not required here — but it LACKS json/toml, so a
    # consumer enabling those would reference missing symbols and must keep them off.
    if(NOT (ENABLE_SKYRIM_SE AND ENABLE_SKYRIM_AE AND ENABLE_SKYRIM_VR AND SKSE_SUPPORT_XBYAK)
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
    _commonlib_prebuilt_complete("${_cache}" _ok)
    if(_ok)
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
    _commonlib_prebuilt_complete("${_cache}" _ok)
    if(NOT _ok)
        file(MAKE_DIRECTORY "${_cache}")
        file(TOUCH "${_cache}/.failed")
        return()
    endif()
    set(${out_dir} "${_cache}" PARENT_SCOPE)
endfunction()

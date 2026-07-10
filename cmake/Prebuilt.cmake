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

# A CRT/config match (checked by the caller) doesn't guarantee the bundle links: its objects
# may reference MSVC STL internal dispatch helpers (e.g. __std_replace_copy_2) that only exist
# in the import libs of a specific toolset/SDK vintage — these aren't part of the stable ABI,
# so a mismatch in EITHER direction can hit a deep LNK2001 at final link (a newer consumer
# toolset isn't safe either: MS can drop an internal helper a preview channel had, as observed
# between a stable release and a newer VS Insiders build). TOOLSET_VERSION.txt (added to the
# bundle by prebuilt.yml's assemble step) records the producer's cl.exe version; require the
# same major.minor toolset (an exact patch/build match would over-trigger on ordinary
# servicing updates that change nothing relevant). Missing stamp (a bundle published before
# this check existed), or CMAKE_CXX_COMPILER_VERSION not yet available (CXX not enabled at
# this point), is treated as compatible — matching prior behavior for already-published tags.
# Gated on CMAKE_CXX_COMPILER_ID rather than the MSVC variable: MSVC is also TRUE for clang-cl,
# whose CMAKE_CXX_COMPILER_VERSION is the Clang version, not the cl.exe version this stamp
# records, so comparing them would be comparing two unrelated numbering schemes.
function(_commonlib_prebuilt_toolset_compatible dir out_var)
    set(${out_var} TRUE PARENT_SCOPE)
    if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" OR NOT CMAKE_CXX_COMPILER_VERSION)
        return()
    endif()
    set(_stamp "${dir}/TOOLSET_VERSION.txt")
    if(NOT EXISTS "${_stamp}")
        return()
    endif()
    file(READ "${_stamp}" _producer_version)
    string(STRIP "${_producer_version}" _producer_version)
    if(NOT _producer_version MATCHES "^[0-9]+\\.[0-9]+(\\.[0-9]+)*$")
        return()
    endif()
    string(REGEX MATCH "^([0-9]+)\\.([0-9]+)" _ignore "${_producer_version}")
    set(_producer_majmin "${CMAKE_MATCH_1}.${CMAKE_MATCH_2}")
    string(REGEX MATCH "^([0-9]+)\\.([0-9]+)" _ignore "${CMAKE_CXX_COMPILER_VERSION}")
    set(_consumer_majmin "${CMAKE_MATCH_1}.${CMAKE_MATCH_2}")
    if(NOT _consumer_majmin STREQUAL _producer_majmin)
        set(${out_var} FALSE PARENT_SCOPE)
        message(STATUS "CommonLibSSE prebuilt bundle was built with a different MSVC toolset "
                        "(${_producer_version}) than this one (${CMAKE_CXX_COMPILER_VERSION}) "
                        "- building from source instead of risking an unresolved-STL-symbol link.")
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

    # The bundle is Release (/MD); a Debug (/MDd) link is a CRT mismatch. Single-config must be
    # non-Debug; a multi-config generator picks the config at build time, so it's skipped unless
    # the consumer promises release-only via COMMONLIB_PREBUILT_MULTICONFIG.
    if(CMAKE_CONFIGURATION_TYPES)
        if(NOT COMMONLIB_PREBUILT_MULTICONFIG)
            return()
        endif()
    elseif(NOT CMAKE_BUILD_TYPE MATCHES "^(Release|RelWithDebInfo|MinSizeRel)$")
        return()
    endif()

    # The bundle is the Release dynamic CRT (/MD). A static CRT (/MT) or the Debug dynamic CRT
    # (/MDd) is a mismatch (→ LNK4098), so fall back to source. Accept any DLL runtime except the
    # always-Debug literal — not a plain STREQUAL "MultiThreadedDLL", since the standard /MD value
    # is the Debug-conditional genex "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL". Unset = /MD default.
    if(DEFINED CMAKE_MSVC_RUNTIME_LIBRARY
       AND (NOT "${CMAKE_MSVC_RUNTIME_LIBRARY}" MATCHES "DLL"
            OR "${CMAKE_MSVC_RUNTIME_LIBRARY}" STREQUAL "MultiThreadedDebugDLL"))
        return()
    endif()

    # explicit override: a consumer (or this repo's self-test) points at an extracted bundle.
    # An incomplete override falls through to auto-fetch (existing behavior); a complete but
    # toolset-incompatible one returns empty rather than silently auto-fetching an unrelated
    # release tag the caller didn't ask for.
    if(COMMONLIB_PREBUILT_DIR)
        _commonlib_prebuilt_complete("${COMMONLIB_PREBUILT_DIR}" _ok)
        if(_ok)
            _commonlib_prebuilt_toolset_compatible("${COMMONLIB_PREBUILT_DIR}" _toolset_ok)
            if(_toolset_ok)
                set(${out_dir} "${COMMONLIB_PREBUILT_DIR}" PARENT_SCOPE)
            endif()
            return()
        endif()
    endif()

    if(NOT (DEFINED ENV{GITHUB_ACTIONS} OR COMMONLIB_PREBUILT))
        return()
    endif()

    # Only the skyrim runtime set is ABI-critical (it changes public-header layout). The lib
    # bakes every REX config + xbyak as additive supersets — and their json/toml parsers live in
    # the lib, not the headers — so a consumer may enable any subset with no extra dependency.
    if(NOT (ENABLE_SKYRIM_SE AND ENABLE_SKYRIM_AE AND ENABLE_SKYRIM_VR))
        return()
    endif()

    find_package(Git QUIET)
    if(NOT Git_FOUND)
        return()
    endif()
    # actions/checkout fetches submodules shallow and without tags, so describe can't see the
    # release tag in CI; pull tags best-effort first (depth 1, ~fast). Still uses --exact-match,
    # so a non-tag commit safely falls back to a source build.
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" -C "${CMAKE_CURRENT_SOURCE_DIR}" fetch --tags --depth=1 origin
        RESULT_VARIABLE _ignore ERROR_QUIET OUTPUT_QUIET)
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
        # A complete-but-toolset-incompatible cache is left as-is (no .failed marker): the
        # completeness check above always wins on a later run, so a marker here would never
        # be read — and leaving the extracted bundle in place lets a later run re-check
        # cheaply if the consumer's toolset changes, without re-downloading.
        _commonlib_prebuilt_toolset_compatible("${_cache}" _toolset_ok)
        if(_toolset_ok)
            set(${out_dir} "${_cache}" PARENT_SCOPE)
        endif()
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
    # No .failed marker on toolset incompatibility here either — see the cached-bundle
    # short-circuit above for why it would never be read back.
    _commonlib_prebuilt_toolset_compatible("${_cache}" _toolset_ok)
    if(NOT _toolset_ok)
        return()
    endif()
    set(${out_dir} "${_cache}" PARENT_SCOPE)
endfunction()

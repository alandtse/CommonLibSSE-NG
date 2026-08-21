set(DIRECTXTK_TAG may2026)

if(VCPKG_TARGET_IS_MINGW)
    message(NOTICE "Building ${PORT} for MinGW requires the HLSL Compiler fxc.exe also be in the PATH. See https://aka.ms/windowssdk.")
endif()

# wine-shader-compile.patch reroutes DirectXTK's shader-compile step
# through `wine cmd /c`, which only makes sense when actually
# cross-compiling from a Linux host. A native Windows build already has
# a real fxc.exe and must not have this patch applied, or its
# shader-compile step would try (and fail) to invoke Wine.
if(CMAKE_HOST_UNIX)
    set(DIRECTXTK_PATCHES PATCHES wine-shader-compile.patch)
else()
    set(DIRECTXTK_PATCHES "")
endif()

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO Microsoft/DirectXTK
    REF ${DIRECTXTK_TAG}
    SHA512 9306774b06f52b4c37938fe4b3a10df8c7a85652188a25dc25e60ae9ff6fbf9d2cf920b114de3fc3945c564054cbb166cc45fca073021129e75ce282a51636e7
    HEAD_REF main
    ${DIRECTXTK_PATCHES}
)

# wine-shader-compile.patch invokes this script rather than inlining its
# logic directly in a CMake COMMAND line: nesting a real shell script
# (needing its own quoting, `;`, `if`) inside a CMake-syntax string that
# a patch file also has to represent as a unified diff is exactly the
# kind of double-escaping that's easy to get subtly wrong. A real file
# just takes plain, unescaped shell.
#
# This derives success/failure from the log content rather than the
# raw exit code of `wine cmd /c CompileShaders.cmd`, for two reasons:
# - `wine cmd`'s own %ERRORLEVEL%/`||` handling is unreliable on at
#   least some Wine versions (confirmed: even Wine's own built-in `ver`
#   command trips a `||` check under `wine cmd /c` on Ubuntu 24.04's
#   packaged Wine 9.0, unrelated to anything this port or fxc2 does),
#   so trusting the exit code would treat every compile as failed even
#   when every shader genuinely compiled correctly. Checking fxc2's own
#   documented error text (see fxc2.cpp's `Got an error (%i) while
#   compiling` printf) is what's actually reliable here.
# - The exit code alone also can't tell "cmd ran fxc2 and it failed"
#   apart from "cmd couldn't invoke fxc2 at all" (e.g. a corrupt/
#   truncated fxc2.exe, confirmed to happen on a real CI run from a
#   race between this port's concurrent debug/release configure
#   invocations racing to build the same fxc2.exe path (see the
#   file(LOCK) above). The second grep catches that failure mode too,
#   which the log otherwise reports identically to a genuine success
#   (no "Got an error" text, since fxc2 never even ran).
if(CMAKE_HOST_UNIX)
    file(WRITE "${SOURCE_PATH}/Src/Shaders/wine-compile-shaders.sh" "#!/bin/sh
set -u
CompileShadersOutput=\"$1\"
FxcTool=\"$2\"
shift 2
\"${CMAKE_COMMAND}\" -E env CompileShadersOutput=\"$CompileShadersOutput\" WINEDEBUG=-all LegacyShaderCompiler=\"$FxcTool\" wine cmd /c CompileShaders.cmd \"$@\" > \"$CompileShadersOutput/compileshaders.log\" 2>&1
if grep -q \"Got an error\" \"$CompileShadersOutput/compileshaders.log\"; then
    echo \"Real shader compilation error(s) detected; see $CompileShadersOutput/compileshaders.log\" >&2
    exit 1
fi
if grep -Eqi \"is not recognized|Can't recognize|cannot find the file\" \"$CompileShadersOutput/compileshaders.log\"; then
    echo \"cmd.exe could not invoke fxc2 at all (a corrupt/truncated fxc2.exe is one known cause); see $CompileShadersOutput/compileshaders.log\" >&2
    exit 1
fi
exit 0
")
endif()

vcpkg_check_features(
    OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    FEATURES
        gameinput BUILD_GAMEINPUT
        windows-gaming-input BUILD_WGI
        spectre ENABLE_SPECTRE_MITIGATION
        tools BUILD_TOOLS
        xaudio2-9 BUILD_XAUDIO_WIN10
        xaudio2-8 BUILD_XAUDIO_WIN8
        xaudio2redist BUILD_XAUDIO_REDIST
)

# Overlay-port-specific: on a real Windows build, DirectXTK's own
# find_program(DIRECTX_FXC_TOOL FXC.EXE ...) locates the Windows SDK's
# fxc.exe and everything works unmodified. Cross-compiling from a Linux
# host, there is no such fxc.exe to find, so fetch and build a stand-in
# from https://github.com/WasabiIceCream/fxc2 (a patched fxc2, MPL-2.0,
# run under Wine against a real d3dcompiler_47.dll) and pre-set
# DIRECTX_FXC_TOOL to it. find_program() never overrides an
# already-set cache variable, so this makes DirectXTK's own
# LegacyShaderCompiler wiring pick it up with no further changes needed
# (that redirection to `wine cmd /c` is what wine-shader-compile.patch
# above does).
if(CMAKE_HOST_UNIX)
    # HINTS on $ENV{LLVM_MINGW_BIN} lets a consumer point at an
    # llvm-mingw install without putting its bin/ on PATH. Deliberately
    # NOT relying on PATH alone here: llvm-mingw bundles its own
    # generic clang-cl/lld-link (for other targets it supports), and if
    # its bin/ is ever on PATH ahead of the real toolchain, find_program
    # calls elsewhere in this same configure (see
    # cmake/toolchain-linux-clangcl.cmake) can silently resolve to
    # llvm-mingw's copies instead of the intended ones, which then fail
    # in confusing ways (e.g. llvm-mingw's lld-link not resolving
    # /winsysroot the same way).
    find_program(FXC2_MINGW_CLANGXX NAMES x86_64-w64-mingw32-clang++ HINTS "$ENV{LLVM_MINGW_BIN}")
    if(NOT FXC2_MINGW_CLANGXX)
        message(FATAL_ERROR "${PORT}: cross-compiling from a Linux host needs an llvm-mingw toolchain (x86_64-w64-mingw32-clang++) on PATH, or pointed at via the LLVM_MINGW_BIN environment variable, to build the fxc2 shader-compiler stand-in. See https://github.com/WasabiIceCream/fxc2.")
    endif()

    vcpkg_from_github(
        OUT_SOURCE_PATH FXC2_SOURCE_PATH
        REPO WasabiIceCream/fxc2
        REF v1.0.0
        SHA512 1d5d67157983058e0bbad3f5fca4c56caa46f29b12c0cdd3efa6a3efc7b3bd5321b4dcbb1c2cdac17569d9271146a8eef61225fb4469f41123584f52178d643e
        HEAD_REF master
    )

    # portfile.cmake genuinely runs more than once per port build,
    # concurrently (confirmed directly via CI logs: two invocations'
    # fxc2 builds interleaved within the same second). A shared, cached
    # ${FXC2_EXE} path with an "if NOT EXISTS, build" check is fragile
    # against that: file(LOCK) still didn't hold up on a real CI run
    # (the second invocation rebuilt from scratch regardless). Two
    # single-source uniqueness attempts after that ALSO both failed on
    # real CI runs, each for a different reason: string(RANDOM) without
    # an explicit seed is time-seeded at whole-second granularity, so
    # both concurrent invocations produced the identical suffix; a
    # freshly-spawned child's OS PID also repeated across both
    # invocations on the actual runner (a real, if unusual, PID-reuse
    # scenario in a low-process-churn environment, confirmed there too,
    # not just theorized). Neither source alone is safe here.
    # Combining three independent, differently-failure-prone sources
    # (nanosecond-resolution wall clock, the PID that already once
    # collided, and a CMake-level pseudo-random string) makes a
    # simultaneous collision across all three vanishingly unlikely,
    # even in this apparently unusual environment.
    execute_process(COMMAND sh -c "echo $$" OUTPUT_VARIABLE FXC2_PID OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process(COMMAND sh -c "date +%s%N" OUTPUT_VARIABLE FXC2_NANOTIME OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(RANDOM LENGTH 12 ALPHABET "0123456789abcdef" FXC2_RAND)
    set(FXC2_EXE "${CURRENT_BUILDTREES_DIR}/fxc2-${FXC2_NANOTIME}-${FXC2_PID}-${FXC2_RAND}.exe")
    execute_process(
        COMMAND "${FXC2_MINGW_CLANGXX}" -static "${FXC2_SOURCE_PATH}/fxc2.cpp" -o "${FXC2_EXE}"
        RESULT_VARIABLE FXC2_BUILD_RESULT
    )
    if(NOT FXC2_BUILD_RESULT EQUAL 0)
        message(FATAL_ERROR "${PORT}: failed to build fxc2.exe from ${FXC2_SOURCE_PATH}")
    endif()
    file(COPY "${FXC2_SOURCE_PATH}/d3dcompiler_47.dll" DESTINATION "${CURRENT_BUILDTREES_DIR}")

    set(DIRECTXTK_FXC2_OPTIONS "-DDIRECTX_FXC_TOOL=${FXC2_EXE}")
else()
    set(DIRECTXTK_FXC2_OPTIONS "")
endif()

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS ${FEATURE_OPTIONS} ${DIRECTXTK_FXC2_OPTIONS}
)

vcpkg_cmake_install()
vcpkg_fixup_pkgconfig()
vcpkg_cmake_config_fixup(CONFIG_PATH share/directxtk)

if("tools" IN_LIST FEATURES)

  vcpkg_download_distfile(
    MAKESPRITEFONT_EXE
    URLS "https://github.com/Microsoft/DirectXTK/releases/download/${DIRECTXTK_TAG}/MakeSpriteFont.exe"
    FILENAME "makespritefont-${DIRECTXTK_TAG}.exe"
    SHA512 1b3f6e2b9394316bfb0ef828850368be9b3ca6227501c28e09a108763f63e2a010588222ee6a3f64233ca8deae663098ca407e41c2a0c93a745078dc24053f5f
  )

  file(MAKE_DIRECTORY "${CURRENT_PACKAGES_DIR}/tools/directxtk/")

  file(INSTALL "${MAKESPRITEFONT_EXE}" DESTINATION "${CURRENT_PACKAGES_DIR}/tools/directxtk/")

  file(RENAME "${CURRENT_PACKAGES_DIR}/tools/directxtk/makespritefont-${DIRECTXTK_TAG}.exe" "${CURRENT_PACKAGES_DIR}/tools/directxtk/makespritefont.exe")

  if(VCPKG_TARGET_ARCHITECTURE STREQUAL x64)

    vcpkg_download_distfile(
      XWBTOOL_EXE
      URLS "https://github.com/Microsoft/DirectXTK/releases/download/${DIRECTXTK_TAG}/XWBTool.exe"
      FILENAME "xwbtool-${DIRECTXTK_TAG}.exe"
      SHA512 1b79d2f2d46a656810e8ef9e2061c9f0071f8304187a144e2aebbfdba2da3d9133a91114e22dcfc178f0bcf8fdb421640252800caea993c27bf987f2e50abafa
    )

    file(INSTALL "${XWBTOOL_EXE}" DESTINATION "${CURRENT_PACKAGES_DIR}/tools/directxtk/")

    file(RENAME "${CURRENT_PACKAGES_DIR}/tools/directxtk/xwbtool-${DIRECTXTK_TAG}.exe" "${CURRENT_PACKAGES_DIR}/tools/directxtk/xwbtool.exe")

  elseif((VCPKG_TARGET_ARCHITECTURE STREQUAL arm64) OR (VCPKG_TARGET_ARCHITECTURE STREQUAL arm64ec))

    vcpkg_download_distfile(
      XWBTOOL_EXE
      URLS "https://github.com/Microsoft/DirectXTK/releases/download/${DIRECTXTK_TAG}/XWBTool_arm64.exe"
      FILENAME "xwbtool-${DIRECTXTK_TAG}-arm64.exe"
      SHA512 dabffcb328f440eb699fcc80f3e33bb093e2f067fa6114bf0a5c521eaa5ab935ac568195a2e25eccb5c228b0ab1b1979121d6936eadae7f3dec8a2aed648a9b4
    )

    file(INSTALL "${XWBTOOL_EXE}" DESTINATION "${CURRENT_PACKAGES_DIR}/tools/directxtk/")

    file(RENAME "${CURRENT_PACKAGES_DIR}/tools/directxtk/xwbtool-${DIRECTXTK_TAG}-arm64.exe" "${CURRENT_PACKAGES_DIR}/tools/directxtk/xwbtool.exe")

  else()

    vcpkg_copy_tools(
          TOOL_NAMES XWBTool
          SEARCH_DIR "${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-rel/bin"
      )

  endif()
endif()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/usage" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")
vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE")

# Cross-compile toolchain for building CommonLibSSE-NG (and consumers of
# it) on a Linux host using clang-cl targeting the real MSVC ABI, via a
# Windows SDK/CRT sysroot obtained with `xwin`
# (https://github.com/Jake-Shadle/xwin). See
# examples/linux-cross-compile/ for the accompanying vcpkg overlay
# triplet/port this is meant to be paired with.
#
# NOTE: assigning a bare command name ("clang-cl") directly to
# CMAKE_C_COMPILER is unreliable here. CMake's cross-compile
# toolchain-file processing doesn't consistently resolve it via PATH
# the way a normal (non-cross) configure does. find_program() sidesteps
# this: it searches PATH itself and hands CMake an already-resolved
# absolute path before EnableLanguage runs, so this stays portable
# across machines without hardcoding install locations.
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR AMD64)

# Distro-packaged LLVM (e.g. Ubuntu/Debian's `clang` apt package) often
# doesn't register a plain "clang-cl"/"lld-link" alias, only versioned
# ones (clang-cl-18, lld-link-18, ...). Listing recent versions as
# fallbacks avoids needing a manual symlink/update-alternatives step on
# those distros; a real install with the plain name (Arch, a manual
# LLVM build, etc.) still matches first.
set(_clangcl_names clang-cl clang-cl-19 clang-cl-18 clang-cl-17 clang-cl-16 clang-cl-15)
set(_lldlink_names lld-link lld-link-19 lld-link-18 lld-link-17 lld-link-16 lld-link-15)
set(_llvmrc_names  llvm-rc llvm-rc-19 llvm-rc-18 llvm-rc-17 llvm-rc-16 llvm-rc-15)

find_program(CMAKE_C_COMPILER NAMES ${_clangcl_names} REQUIRED)
find_program(CMAKE_CXX_COMPILER NAMES ${_clangcl_names} REQUIRED)
find_program(CMAKE_LINKER NAMES ${_lldlink_names} REQUIRED)

# CMake's Ninja generator invokes a resource compiler (via `cmake -E
# vs_link_exe --rc=...`) to embed manifests for every linked
# exe/shared-lib target on this toolset, including CMake's own internal
# compiler-ABI-detection try-compile step, whether or not the project
# itself uses any .rc files. Left unset, it defaults to the literal
# command name "rc", which doesn't exist outside a real MSVC install;
# llvm-rc is the clang-cl-toolchain equivalent. Not REQUIRED: harmless
# to leave unresolved on a host that genuinely has no llvm-rc, since
# CMake only fails on this if a link step's manifest generation is
# actually reached.
find_program(CMAKE_RC_COMPILER NAMES ${_llvmrc_names})

# Override with -DXWIN_SYSROOT=<path> or the XWIN_SYSROOT environment
# variable if your sysroot lives somewhere other than the default.
# Must have been generated with:
#   xwin ... splat --use-winsysroot-style --preserve-ms-arch-notation
# (both flags are required. Without --use-winsysroot-style, /winsysroot
# won't find anything; without --preserve-ms-arch-notation, lld-link
# looks for "lib/x64" but xwin's default output uses "lib/x86_64" and
# nothing resolves.)
if(DEFINED XWIN_SYSROOT)
    set(_xwin_sysroot "${XWIN_SYSROOT}")
elseif(DEFINED ENV{XWIN_SYSROOT})
    set(_xwin_sysroot "$ENV{XWIN_SYSROOT}")
else()
    set(_xwin_sysroot "$ENV{HOME}/xwin-out")
endif()

# Appended (with CACHE ... FORCE) rather than via the usual
# CMAKE_<LANG>_FLAGS_INIT mechanism: CMake only applies *_INIT the first
# time it initializes a cache variable that doesn't already exist, and
# CommonLibSSE-NG's own CMakePresets.json already populates
# CMAKE_CXX_FLAGS directly via a preset (so *_INIT is silently ignored
# for it). Appending unconditionally here works regardless of whether
# the consumer's own presets/CMakeLists.txt already set these. Guarded
# on the sysroot flag not already being present, since this toolchain
# file gets chainloaded more than once per configure (once for compiler
# ABI detection, again for the real build, and again for each vcpkg
# port's own isolated nested configure) and CACHE...FORCE would
# otherwise keep re-appending the same flags on every pass.
#
# /EHsc is included here (not just left to the consumer's own compiler
# flags) because vcpkg builds each dependency in its own isolated CMake
# invocation that does NOT inherit the consuming project's
# CMakeLists.txt/CMakePresets.json compiler flags at all, only whatever
# this chainloaded toolchain file sets. Without it, clang-cl defaults to
# exceptions disabled (matching real cl.exe's default), which breaks
# any dependency that uses try/throw/catch, e.g. spdlog.
if(NOT CMAKE_CXX_FLAGS MATCHES "winsysroot")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} --target=x86_64-pc-windows-msvc /winsysroot${_xwin_sysroot}" CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --target=x86_64-pc-windows-msvc /winsysroot${_xwin_sysroot} /EHsc" CACHE STRING "" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} /winsysroot:${_xwin_sysroot}" CACHE STRING "" FORCE)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /winsysroot:${_xwin_sysroot}" CACHE STRING "" FORCE)
endif()

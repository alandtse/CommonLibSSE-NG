# CommonLibSSE-NG, cross-compiled from Linux to Windows (MSVC ABI) with clang-cl.
#
# How it works
# ------------
# The Windows toolchain is assembled from these pieces:
#
#   * xwin     downloads the Windows SDK and MSVC CRT (headers + import libs).
#   * clang-cl compiles C/C++ for x86_64-pc-windows-msvc, lld-link links it.
#   * Wine     runs fxc2.exe, a shader compiler DirectXTK needs at build time.
#   * vcpkg    builds the C++ dependencies (fmt, spdlog, DirectXTK, ...).
#
# Nix sandboxes have no network, so everything that must be downloaded is a
# fixed-output derivation (FOD, pinned by hash). Everything else builds offline.
#
#   nix build .#xwin-sysroot     # Windows SDK/CRT       (FOD, needs network)
#   nix build .#vcpkg-downloads  # vcpkg source archives (FOD, needs network)
#   nix build .#vcpkg-deps       # vcpkg build           (offline)
#   nix build                    # CommonLibSSE.lib      (offline)
#   nix develop                  # shell with the whole toolchain
#
# To update a pinned hash: set it to `lib.fakeHash`, run the build once, and
# copy the "got:" hash from the error message.
{
  description = "CommonLibSSE-NG: Linux-host cross-compile to Windows PE (MSVC ABI)";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-26.05";
    nixpkgs-unstable.url = "github:NixOS/nixpkgs/nixos-unstable"; # newer vcpkg
    flake-utils.url = "github:numtide/flake-utils";

    # extern/openvr is a git submodule; include it in the flake's source.
    # (Needs Nix >= 2.27.)
    self.submodules = true;
  };

  outputs = { self, nixpkgs, nixpkgs-unstable, flake-utils }:
    # Wine and the xwin sysroot only make sense on an x86_64 Linux host.
    flake-utils.lib.eachSystem [ "x86_64-linux" ] (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        inherit (pkgs) lib;

        # vcpkg comes from unstable (newer than the stable channel).
        vcpkg = nixpkgs-unstable.legacyPackages.${system}.vcpkg;

        # nixpkgs' mingw-w64 cross compiler (only used to build fxc2.exe).
        mingw = pkgs.pkgsCross.mingwW64;

        # Attributes that turn a derivation into a fixed-output derivation.
        fixedOutput = hash: {
          outputHashAlgo = "sha256";
          outputHashMode = "recursive";
          outputHash = hash;
        };

        # ==================================================================
        # Pinned sources (plain tarballs: no .git, stable hashes)
        # ==================================================================

        # The vcpkg ports at the commit the project pins as `builtin-baseline`.
        # The real baseline mechanism needs a git checkout of the registry,
        # which is impossible offline, so these ports are used as overlay
        # ports instead (see `crossEnv` and `commonAttrs.postPatch`).
        vcpkgPorts = pkgs.fetchFromGitHub {
          owner = "microsoft";
          repo = "vcpkg";
          rev = "ee12231b20c95013c6638d845d04c91559a1d1ff";
          hash = "sha256-cCsiADfk1P0iRLIM55IkEkCEFjDLcLaKtXTzqdAONEo=";
        };

        # CMakeLists.txt vendors MinHook's hde64 via FetchContent (GIT_TAG
        # v1.3.4). The sandbox cannot clone it, so Nix fetches it and the
        # build points CMake at it with FETCHCONTENT_SOURCE_DIR_HDE64.
        hde64Src = pkgs.fetchFromGitHub {
          owner = "TsudaKageyu";
          repo = "minhook";
          rev = "v1.3.4";
          hash = "sha256-0eGFfg365bb4zic1WTHMvKHbxuhhGp72/clu8OklHXs=";
        };

        # ==================================================================
        # Toolchain
        # ==================================================================

        # Nix's wrapped clang has no clang-cl, so use the unwrapped one. The
        # wrapper normally supplies the resource dir (builtin headers such as
        # intrin.h), so pass it explicitly. lld-link is put on PATH so it is
        # found in every subprocess, including CMake's try_compile.
        clangCl =
          let
            clang = pkgs.clang.cc;
            resourceDir = "${lib.getLib clang}/lib/clang/${lib.versions.major pkgs.clang.version}";
          in
          pkgs.writeShellScriptBin "clang-cl" ''
            export PATH="${lib.makeBinPath [ pkgs.lld ]}:$PATH"
            exec ${clang}/bin/clang-cl "/clang:-resource-dir=${resourceDir}" "$@"
          '';

        # The directxtk overlay port builds a tiny fxc2.exe and looks for
        # `x86_64-w64-mingw32-clang++`; we answer with nixpkgs' mingw g++.
        # That GCC uses the mcfgthread thread model, so its library must be on
        # the link path. `-static` keeps fxc2.exe runnable in Wine without the
        # mcfgthread DLL next to it.
        fxc2Compiler = pkgs.writeShellScriptBin "x86_64-w64-mingw32-clang++" ''
          exec ${mingw.stdenv.cc}/bin/x86_64-w64-mingw32-g++ \
            -L${mingw.windows.mcfgthreads}/lib \
            -static \
            "$@"
        '';

        # Appended to the repo's own CMake toolchain file (NixOS workarounds).
        toolchainPatch = pkgs.writeText "nixos-toolchain-patch.cmake" ''

          # --- NixOS: use our wrapper, skip the compiler sanity check ---
          set(CMAKE_C_COMPILER   "${clangCl}/bin/clang-cl")
          set(CMAKE_CXX_COMPILER "${clangCl}/bin/clang-cl")
          set(CMAKE_RC_COMPILER  "${pkgs.llvm}/bin/llvm-rc")
          set(CMAKE_C_COMPILER_WORKS 1)
          set(CMAKE_CXX_COMPILER_WORKS 1)

          # --- NixOS: make sure lld-link is used ---
          set(CMAKE_EXE_LINKER_FLAGS_INIT    "-fuse-ld=lld-link")
          set(CMAKE_SHARED_LINKER_FLAGS_INIT "-fuse-ld=lld-link")
          set(CMAKE_MODULE_LINKER_FLAGS_INIT "-fuse-ld=lld-link")
        '';

        # Tools shared by the dev shell and all derivations.
        buildTools = with pkgs; [
          clang lld llvm cmake ninja git pkg-config
          wineWow64Packages.stable cacert jq
        ] ++ [ vcpkg ];

        # ==================================================================
        # Windows SDK/CRT (FOD: downloads from Microsoft)
        # ==================================================================

        # nixpkgs' xwin (0.7.0) is too old for the current SDK manifest, so
        # the pinned 0.10.0 is built with cargo. stdenv, not stdenvNoCC:
        # cargo needs a C linker.
        xwinSysroot = pkgs.stdenv.mkDerivation ({
          pname = "xwin-sysroot";
          version = "0.10.0";

          nativeBuildInputs = [ pkgs.cargo pkgs.rustc pkgs.cacert ];

          buildCommand = ''
            export CARGO_HOME=$(mktemp -d)
            cargo install xwin --version 0.10.0 --locked --root $TMPDIR/xwin

            $TMPDIR/xwin/bin/xwin --accept-license --http-retry 10 \
              --cache-dir $TMPDIR/cache splat \
              --output $out \
              --include-debug-libs \
              --use-winsysroot-style --preserve-ms-arch-notation
          '';
        } // fixedOutput "sha256-PQkDJYviKKRynZ5ARYS+BFcX8cKRitpRrapViTPVQrI=");

        # ==================================================================
        # Shared build environment and attributes
        # ==================================================================

        # Shell snippet sourced by every build step that compiles for Windows.
        crossEnv = ''
          export XWIN_SYSROOT=${xwinSysroot}
          export LLVM_MINGW_BIN=${fxc2Compiler}/bin
          export PATH=${lib.makeBinPath [ clangCl fxc2Compiler ]}:$PATH

          # Headless Wine, used to run fxc2.exe. Skipping Mono/Gecko avoids
          # download prompts.
          export WINEPREFIX="$TMPDIR/wineprefix"
          export WINEARCH=win64
          export WINEDEBUG=-all
          export WINEDLLOVERRIDES="mscoree,mshtml="
          mkdir -p "$WINEPREFIX"

          # vcpkg. VCPKG_ROOT is what the CMake presets use to locate
          # scripts/buildsystems/vcpkg.cmake.
          export VCPKG_ROOT=${vcpkg}/share/vcpkg
          export VCPKG_FORCE_SYSTEM_BINARIES=1
          export VCPKG_DISABLE_METRICS=1
          overlay="$PWD/examples/linux-cross-compile"
          # Overlay ports are searched in order: the repo's directxtk (patched
          # to run fxc2 under Wine) must come before the baseline ports.
          export VCPKG_OVERLAY_PORTS="$overlay/custom-ports:${vcpkgPorts}/ports"
          export VCPKG_OVERLAY_TRIPLETS="$overlay/custom-triplets"
        '';

        # Attributes shared by all three project derivations.
        commonAttrs = {
          version = "0.1.0";
          src = self;
          nativeBuildInputs = buildTools;
          dontConfigure = true;
          dontFixup = true; # nothing to strip/patchelf in Windows binaries
          hardeningDisable = [ "all" ]; # the cc-wrapper's -fPIC etc. break the MSVC target
          HOME = "/tmp"; # vcpkg keeps its buildtrees in $HOME/.vcpkg

          postPatch = ''
            cat ${toolchainPatch} >> cmake/toolchain-linux-clangcl.cmake

            # `builtin-baseline` needs a git checkout of the vcpkg registry.
            # Drop it, the "version>=" bounds (which need a baseline) and the
            # default registry; the ports at the baseline commit are provided
            # as overlay ports instead (see vcpkgPorts).
            jq 'del(."builtin-baseline") | walk(if type == "object" then del(."version>=") else . end)' \
              vcpkg.json > vcpkg.json.new
            mv vcpkg.json.new vcpkg.json
            echo '{ "default-registry": null }' > vcpkg-configuration.json
          '';
        };

        # Arguments common to `vcpkg install` in the download and build steps.
        vcpkgArgs = downloads: ''
          --triplet x64-windows-clangcl \
          --feature-flags=-compilertracking \
          --binarysource=clear \
          --x-manifest-root . \
          --downloads-root "${downloads}" \
          --vcpkg-root "${vcpkg}/share/vcpkg"
        '';

        # ==================================================================
        # vcpkg, in two steps
        #
        # Only the downloaded source archives are hashed (they are identical
        # on every run). The compiled libraries are not: they contain
        # timestamps and would make a fixed-output hash change on each build.
        # ==================================================================

        # Step 1 (FOD): download the source archives of all dependencies.
        vcpkgDownloads = pkgs.stdenv.mkDerivation (commonAttrs // {
          pname = "commonlibsse-ng-vcpkg-downloads";
          dontInstall = true;

          buildPhase = ''
            set -euo pipefail
            ${crossEnv}

            mkdir -p "$out"
            vcpkg install --only-downloads \
              --x-install-root "$TMPDIR/unused-install" \
              ${vcpkgArgs "$out"}

            # Keep only the archives; drop vcpkg's scratch directories.
            rm -rf "$out/temp" "$out/tools"
          '';
        } // fixedOutput "sha256-i5/z2kaBDKlWafb21dpuRfnC9ZadkH7F04fieubvB1A=");

        # Step 2 (offline): build all dependencies from those archives.
        vcpkgDeps = pkgs.stdenv.mkDerivation (commonAttrs // {
          pname = "commonlibsse-ng-vcpkg-deps";
          dontInstall = true;

          buildPhase = ''
            set -euo pipefail
            ${crossEnv}

            # vcpkg wants a writable downloads directory.
            cp -r ${vcpkgDownloads} "$TMPDIR/downloads"
            chmod -R u+w "$TMPDIR/downloads"

            # On failure, print the relevant parts of vcpkg's build logs
            # (the Nix log would otherwise only show the last lines).
            dump_logs() {
              echo "===== vcpkg failed; relevant log excerpts ====="
              find "$HOME/.vcpkg/root/buildtrees" -name '*.log' \
                   ! -name '*CMakeConfigureLog*' ! -name '*CMakeOutput*' -print0 2>/dev/null |
                xargs -0 grep -l -E 'CMake Error|error:|fatal error|FAILED:|wine' |
                while read -r f; do
                  echo "--- $f ---"
                  grep -E -B3 -A8 'CMake Error|error:|fatal error|FAILED:|wine' "$f" | cut -c1-250 | head -60
                done || true
            }

            if ! vcpkg install \
              --x-install-root "$out" \
              ${vcpkgArgs "$TMPDIR/downloads"}
            then
              dump_logs
              exit 1
            fi
          '';
        });

        # ==================================================================
        # The library itself (offline)
        # ==================================================================
        commonlibsse-ng = pkgs.stdenv.mkDerivation (commonAttrs // {
          pname = "commonlibsse-ng";

          buildPhase = ''
            set -euo pipefail
            ${crossEnv}

            # These are CMake variables, not environment variables: without
            # them vcpkg's toolchain file would run `vcpkg install` again.
            # FETCHCONTENT_* make CMake use the Nix-fetched hde64 sources and
            # fail fast on any other download attempt.
            cmake --preset build-release-linux-clangcl-vcpkg-all \
              -DVCPKG_MANIFEST_INSTALL=OFF \
              -DVCPKG_INSTALLED_DIR=${vcpkgDeps} \
              -DFETCHCONTENT_SOURCE_DIR_HDE64=${hde64Src} \
              -DFETCHCONTENT_FULLY_DISCONNECTED=ON

            # Build only the library. The test executable is a Windows .exe,
            # and Catch2's post-link test discovery would try to run it on Linux.
            cmake --build --preset release-linux-clangcl-vcpkg-all --target CommonLibSSE
          '';

          installPhase = ''
            set -euo pipefail
            build=build/release-linux-clangcl-vcpkg-all

            mkdir -p $out/lib
            cp "$build/CommonLibSSE.lib" $out/lib/
          '';
        });

      in
      {
        packages = {
          xwin-sysroot = xwinSysroot;
          vcpkg-downloads = vcpkgDownloads;
          vcpkg-deps = vcpkgDeps;
          inherit commonlibsse-ng;
          default = commonlibsse-ng;
        };

        # Same toolchain, interactively (`nix develop`, run from the repo root).
        # The hook exports the cross environment (sysroot, vcpkg root, overlay
        # ports). The working tree is NOT patched, so use `nix build` for
        # real builds.
        devShells.default = pkgs.mkShell {
          packages = buildTools ++ [ clangCl fxc2Compiler ];
          shellHook = crossEnv;
        };

        formatter = pkgs.nixpkgs-fmt;
      });
}
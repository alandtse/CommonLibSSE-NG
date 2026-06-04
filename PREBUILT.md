# Prebuilt CommonLib bundles

Each release attaches prebuilt **static-library bundles** so downstream projects can
consume CommonLib without recompiling it (CommonLib is the bulk of a plugin's build
time). There is one bundle per build system — **xmake** and **CMake** — both baked with
the same config below. They are produced and self-tested by
`.github/workflows/prebuilt.yml` and attached to the release.

Both build systems **auto-fetch** their bundle on a clean release tag (see the auto-fetch
sections), so in the common case you change nothing in your repo.

## What's in the xmake bundle

`commonlibsse-ng-prebuilt-<tag>-all-msvc.7z` is a drop-in replacement for the
`lib/commonlibsse-ng` source tree:

```
xmake.lua            # the same build script, which auto-detects lib/commonlibsse-ng.lib
                     #   and links it instead of compiling src/ ("prebuilt mode")
include/             # public headers (RE/ REL/ REX/ SKSE/)
res/                 # commonlibsse-ng.plugin rule templates
extern/openvr/headers/   # VR headers (the "all" config enables VR)
lib/commonlibsse-ng.lib  # the prebuilt static library
PREBUILT.md
```

## Baked configuration (must match in the consumer)

The library is compiled **once**, for the config our xmake consumers use:

| Axis | Value |
|------|-------|
| Runtime | **all** — `skyrim_se` + `skyrim_ae` + `skyrim_vr` |
| REX | **`rex_ini`** on |
| Trampoline | **`skse_xbyak`** on |
| Build | `releasedbg`, x64, **MSVC** |
| C++ | C++23 |

A prebuilt static library bakes its config and toolchain in. To link it safely a
consumer **must** build with a compatible setup:

- Same options: set `rex_ini = true` and `skse_xbyak = true` **before** `includes()`
  (the `skyrim_*` runtimes default on). Different options (e.g. `rex_json`, or
  disabling a runtime) are **not** served by this bundle — build from source for those.
- Same mode/ABI: xmake `releasedbg` (release CRT `/MD`, `NDEBUG`). No `debug` bundle
  is published. A true `debug` build must compile from source.
- Same compiler family (**MSVC**) and a compatible MSVC toolset version. Toolset drift
  between this bundle and the consumer is the most common cause of link/ABI errors.

## How to consume (xmake)

Replace the `lib/commonlibsse-ng` **source submodule** with the **extracted bundle**
(same path). Your existing build is otherwise unchanged:

```lua
set_config("rex_ini", true)      -- match the bundle
set_config("skse_xbyak", true)
includes("lib/commonlibsse-ng")  -- now a prebuilt bundle, not source

target("my-plugin")
    add_deps("commonlibsse-ng")
    add_rules("commonlibsse-ng.plugin", { name = "my-plugin", author = "you" })
    add_files("src/**.cpp")
```

`includes()` runs the bundled `xmake.lua`, which sees `lib/commonlibsse-ng.lib` and
switches to prebuilt mode — same target, same `commonlibsse-ng.plugin` rule, same
transitive deps (`directxmath`, `directxtk`, `spdlog`, `simpleini`, `xbyak`,
`rapidcsv`), just no CommonLib recompile.

## Automatic fetch on a clean release tag (no bundle swap needed)

You don't have to extract the bundle by hand. When CommonLib is consumed as a normal
**source submodule** pinned to a clean release **tag**, `xmake.lua` will — in CI
(`GITHUB_ACTIONS`), or anywhere with `COMMONLIB_PREBUILT=1` — download that tag's bundle
from the GitHub release, verify its `.sha256`, and link it instead of compiling. So a
plugin whose `lib/commonlibsse-ng` submodule sits on `vX.Y.Z` gets the prebuilt for free
on CI, with zero changes to its repo.

It falls back to a normal **source build** whenever the prebuilt can't be used safely:
not on an exact tag, a dirty submodule, options that don't match the baked config, a
missing/unverified asset, or no network. The download is cached under
`build/.prebuilt/<tag>` and attempted at most once per tag. Local dev builds stay
source-by-default (set `COMMONLIB_PREBUILT=1` to opt in). The consumer must still set the
options the lib was baked with (`rex_ini`, `skse_xbyak`; runtimes default on).

## Size & cost

The `releasedbg` "all" library carries full debug info for three runtimes, so it is
**~1.2 GB extracted** — but compresses ~24× to a **~52 MB** download. A consumer build
against it is **seconds** (e.g. ~6 s for the self-test plugin) versus a full source
build (minutes cold). The large on-disk size is the trade for keeping CommonLib frames
symbolicatable in crash logs; the extra link cost is negligible.

## CMake bundle

`commonlibsse-ng-prebuilt-<tag>-all-msvc-cmake.zip` serves **`add_subdirectory`**
consumers (the common extern-path setup). It carries just the build outputs the consumer
links against:

```
lib/CommonLibSSE.lib     # the prebuilt static library (Release)
lib/openvr_api.lib       # linked PUBLIC by the target (the "all" config enables VR)
include/                 # public headers (RE/ REL/ REX/ SKSE/)
extern/openvr/headers/   # VR headers
PREBUILT.md
```

It is **not** a `find_package` install tree: instead the consumer's
`add_subdirectory(<commonlib>)` runs `cmake/Prebuilt.cmake`, which resolves the bundle
and defines `CommonLibSSE` as an **IMPORTED** target pointing at these local paths. This
sidesteps `find_package`/`install(EXPORT)` relocatability entirely — the paths are the
just-extracted bundle's own.

The baked configuration is the same as the xmake bundle, with the CMake spelling:
`ENABLE_SKYRIM_SE/AE/VR=ON`, `REX_OPTION_INI=ON`, `SKSE_SUPPORT_XBYAK=ON`
(`REX_OPTION_JSON/TOML=OFF`), MSVC, **`Release`** (`/MD`, `NDEBUG`), C++23.

### Automatic fetch on a clean release tag (CMake)

When CommonLib is consumed via `add_subdirectory` from a source submodule pinned to a
clean release **tag**, `cmake/Prebuilt.cmake` will — in CI (`GITHUB_ACTIONS`), or anywhere
with `-DCOMMONLIB_PREBUILT=ON` — download that tag's `…-cmake.zip`, verify its `.sha256`,
extract it, and expose the IMPORTED target instead of compiling `src/`. A plugin whose
submodule sits on `vX.Y.Z` gets the prebuilt for free on CI, unchanged.

It falls back to a normal **source build** whenever the prebuilt can't be used safely: the
top-level project is CommonLib itself (you only auto-fetch when *consumed*), not on an
exact tag, a dirty tree, options that don't match the baked config, or a missing/unverified
asset. The download is cached under `<build>/.prebuilt/<tag>` and attempted at most once
per tag. Local dev builds stay source-by-default (`-DCOMMONLIB_PREBUILT=ON` to opt in), or
point `-DCOMMONLIB_PREBUILT_DIR=<extracted bundle>` at a bundle to skip the download.

Because the headers are baked with `skse_xbyak` and link `spdlog`/`DirectXTK` PUBLIC, the
consumer must provide those header deps from **its own `vcpkg.json`** (`spdlog`, `fmt`,
`directxtk`, `directxmath`, `xbyak`) — exactly as a source build already requires. As with
any CommonLibSSE-NG plugin, the consumer also supplies a **PCH** that includes
`<SKSE/Impl/PCH.h>` and `using namespace std::literals;` (the headers are PCH-dependent).
See `tests/prebuilt-consumer-cmake/` for a minimal working consumer.

### vcpkg-port consumers

Consumers that pull `"commonlibsse-ng"` through `vcpkg.json` (rather than
`add_subdirectory`) are served by **vcpkg binary caching** (a shared GHA/NuGet/S3 backend)
so the port builds once and is restored across CI — idiomatic, no custom artifact.

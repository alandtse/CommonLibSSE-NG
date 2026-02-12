@echo off
setlocal enabledelayedexpansion
REM Comprehensive build script for CommonLibVR
REM Builds all presets and stops at first failure for faster LLM iteration

REM Try to find Visual Studio installation dynamically
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "VCVARS_PATH="

REM First try vswhere.exe
if exist "%VSWHERE%" (
    for /f "delims=" %%i in ('"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath 2^>nul') do (
        if exist "%%i\VC\Auxiliary\Build\vcvars64.bat" (
            set "VCVARS_PATH=%%i\VC\Auxiliary\Build\vcvars64.bat"
            goto :vcvars_found
        )
    )
)

REM Fallback: Check common paths on all drives
if not defined VCVARS_PATH (
    for %%D in (C D E F G H I J K L M N O P Q R S T U V W X Y Z) do (
        if exist "%%D:\" (
            REM Check VS 2022 Community
            if exist "%%D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
                set "VCVARS_PATH=%%D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
                goto :vcvars_found
            )
            REM Check VS 2022 Professional
            if exist "%%D:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat" (
                set "VCVARS_PATH=%%D:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat"
                goto :vcvars_found
            )
            REM Check VS 2019 Community
            if exist "%%D:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat" (
                set "VCVARS_PATH=%%D:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
                goto :vcvars_found
            )
        )
    )
)

:vcvars_found

REM Check if we found vcvars64.bat
if not defined VCVARS_PATH (
    echo ERROR: Could not find vcvars64.bat. Please ensure Visual Studio is installed.
    echo You can also set the VCVARS64_PATH environment variable to the full path of vcvars64.bat
    exit /b 1
)

REM Allow override via environment variable
if defined VCVARS64_PATH (
    set "VCVARS_PATH=%VCVARS64_PATH%"
)

echo Using Visual Studio environment: %VCVARS_PATH%
call "%VCVARS_PATH%" x64 >nul 2>&1

if !ERRORLEVEL! NEQ 0 (
    echo ERROR: Failed to initialize Visual Studio environment
    exit /b 1
)

echo.
echo ========================================
echo CommonLibVR Build Script
echo ========================================
echo.

REM Build order: SE, AE, VR, Flatrim, All
set "PRESETS=release-msvc-vcpkg-se release-msvc-vcpkg-ae release-msvc-vcpkg-vr release-msvc-vcpkg-flatrim release-msvc-vcpkg-all"

for %%P in (%PRESETS%) do (
    echo Building preset: %%P
    echo ----------------------------------------
    
    REM Build preset
    cmake --build --preset %%P >nul 2>&1
    
    if !ERRORLEVEL! EQU 0 (
        echo [SUCCESS] %%P
        echo.
    ) else (
        echo [FAILED] %%P - showing errors:
        echo.
        cmake --build --preset %%P 2>&1 | findstr /C:"error C" /C:"error LNK" /C:"FAILED"
        echo.
        echo To see full output, run: cmake --build --preset %%P
        exit /b 1
    )
)

echo.
echo ========================================
echo All builds SUCCEEDED
echo ========================================
exit /b 0
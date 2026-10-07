@echo off
REM ============================================================
REM Quick C++ Compiler Helper for Game Dev Practice
REM Usage: build.bat path\to\file.cpp
REM ============================================================

setlocal enabledelayedexpansion

REM Ensure MinGW is on PATH for this terminal
set "PATH=C:\mingw64\bin;%PATH%"

if "%~1"=="" (
    echo [ERROR] No C++ file provided!
    echo Usage: 00_setup_and_tooling\build.bat path\to\main.cpp
    exit /b 1
)

set "SOURCE_FILE=%~1"
set "OUT_EXE=%~dpn1.exe"

echo ------------------------------------------------------------
echo [Compiling] %SOURCE_FILE% -> %OUT_EXE%
echo ------------------------------------------------------------

g++ -std=c++17 -Wall -Wextra -O2 "%SOURCE_FILE%" -o "%OUT_EXE%"

if %ERRORLEVEL% EQU 0 (
    echo [SUCCESS] Compilation succeeded!
    echo [Running] %OUT_EXE%
    echo ------------------------------------------------------------
    "%OUT_EXE%"
) else (
    echo [FAILED] Compilation errors encountered.
)

@echo off
REM Batch file to build DES encryption project on Windows

REM Compiler and flags
set CC=gcc
set CFLAGS=-Wall -Wextra -std=c99 -I%INCLUDE_DIR%

REM Directories
set INCLUDE_DIR=inc
set SRC_DIR=src
set OBJ_DIR=obj
set BIN_DIR=bin

REM Name of the final executable
set TARGET=%BIN_DIR%\des_encryption.exe

REM Create the obj and bin directories if they don't exist
if not exist "%OBJ_DIR%" (
    mkdir "%OBJ_DIR%"
)
if not exist "%BIN_DIR%" (
    mkdir "%BIN_DIR%"
)

REM Compile each .c file in the src directory to an object file in obj directory
echo Compiling source files...
for %%f in (%SRC_DIR%\*.c) do (
    echo Compiling %%f...
    %CC% %CFLAGS% -I%INCLUDE_DIR% -c "%%f" -o "%OBJ_DIR%\%%~nf.o"
    if errorlevel 1 (
        echo Compilation failed for %%f
        exit /b 1
    )
)

REM Link all object files to create the final executable in bin directory
echo Linking object files to create executable...
%CC% -o "%TARGET%" %OBJ_DIR%\*.o
if errorlevel 1 (
    echo Linking failed.
    exit /b 1
)

echo Build completed successfully! Executable created at "%TARGET%"

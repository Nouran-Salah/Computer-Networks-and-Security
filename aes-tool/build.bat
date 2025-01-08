@echo off
REM Batch file for building and cleaning the AES encryption project on Windows

REM Compiler and flags
set CC=gcc
set CFLAGS=-std=c17 -Wall -Wextra -Werror -Iinclude -g

REM Directories
set SRC_DIR=src
set INC_DIR=include
set OBJ_DIR=obj
set BIN_DIR=bin

REM Target executable
set TARGET=%BIN_DIR%\aes_encryption.exe

REM Function: Build the project
:build
echo === Building the project ===

REM Create obj and bin directories if they don't exist
if not exist "%OBJ_DIR%" (
    mkdir "%OBJ_DIR%"
)
if not exist "%BIN_DIR%" (
    mkdir "%BIN_DIR%"
)

REM Compile each .c file into object files
for %%f in (%SRC_DIR%\*.c) do (
    echo Compiling %%f...
    %CC% %CFLAGS% -c "%%f" -o "%OBJ_DIR%\%%~nf.o"
    if errorlevel 1 (
        echo Compilation failed for %%f
        exit /b 1
    )
)

REM Link all object files into the final executable
echo Linking object files...
%CC% -o "%TARGET%" %OBJ_DIR%\*.o
if errorlevel 1 (
    echo Linking failed.
    exit /b 1
)

echo Build completed successfully! Executable created at "%TARGET%"
exit /b 0

REM Function: Clean the project
:clean
echo === Cleaning up build files ===

REM Remove obj and bin directories
if exist "%OBJ_DIR%" (
    echo Removing %OBJ_DIR% directory...
    rmdir /S /Q "%OBJ_DIR%"
)
if exist "%BIN_DIR%" (
    echo Removing %BIN_DIR% directory...
    rmdir /S /Q "%BIN_DIR%"
)

echo Clean completed successfully!
exit /b 0

REM Main logic: Parse input arguments
:main
if "%1"=="clean" goto clean
goto build

REM Start of script
call :main %1

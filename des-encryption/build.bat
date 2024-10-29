@echo off
REM Batch file to build DES encryption project on Windows

REM Compiler and flags
set CC=gcc
set CFLAGS=-Wall -Wextra -std=c99 -Iinc

REM Directories
set INCLUDE_DIR=inc
set SRC_DIR=src
set OBJ_DIR=obj

REM Name of the final executable
set TARGET=des_encryption.exe

REM Create the object directory if it doesn't exist
if not exist "%OBJ_DIR%" (
    mkdir "%OBJ_DIR%"
)

REM Compile each .c file in the src directory
for %%f in (%SRC_DIR%\*.c) do (
    echo Compiling %%f...
    %CC% %CFLAGS% -I%INCLUDE_DIR% -c "%%f" -o "%OBJ_DIR%\%%~nf.o"
)

REM Link object files to create the executable
echo Linking object files...
%CC% -o "%TARGET%" %OBJ_DIR%\*.o

echo Build completed successfully!


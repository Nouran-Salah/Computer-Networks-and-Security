@echo off
REM Batch file to clean build artifacts for DES encryption project

REM Directories and executable
set OBJ_DIR=obj
set BIN_DIR=bin
set TARGET=%BIN_DIR%\des_encryption.exe

REM Remove the obj directory if it exists
if exist %OBJ_DIR% (
    echo Removing %OBJ_DIR% directory...
    rmdir /S /Q %OBJ_DIR%
)

REM Remove the bin directory and executable if they exist
if exist %BIN_DIR% (
    echo Removing %BIN_DIR% directory and executable...
    rmdir /S /Q %BIN_DIR%
)

echo Clean completed successfully!

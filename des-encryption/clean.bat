@echo off
REM Clean build artifacts
if exist obj (
    rmdir /S /Q obj
)
if exist des_encryption.exe (
    del /F /Q des_encryption.exe
)
echo Clean completed successfully!

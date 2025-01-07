# AES Encryption and Decryption Tool

![AES Encryption](https://img.shields.io/badge/AES-Encryption%20%26%20Decryption-blue)

## Table of Contents

- [AES Encryption and Decryption Tool](#aes-encryption-and-decryption-tool)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Features](#features)
  - [Directory Structure](#directory-structure)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Building the Project](#building-the-project)
  - [Usage](#usage)
    - [Basic Command Structure](#basic-command-structure)
    - [Examples](#examples)
    - [Key Management](#key-management)
    - [Help Command](#help-command)
  - [Testing](#testing)
    - [1. Dummy Data Files](#1-dummy-data-files)
      - [a. Text Files](#a-text-files)
      - [b. Binary Files](#b-binary-files)
      - [c. Hexadecimal Data](#c-hexadecimal-data)
    - [2. Automated Testing Scripts](#2-automated-testing-scripts)
      - [a. Shell Script for Automated Testing (`test_aes.sh`)](#a-shell-script-for-automated-testing-test_aessh)
    - [3. Manual Testing](#3-manual-testing)
  - [Contributing](#contributing)
  - [License](#license)

## Introduction

The **AES Encryption and Decryption Tool** is a command-line application developed in C++ that allows users to securely encrypt and decrypt files using the Advanced Encryption Standard (AES) algorithm. This tool supports AES-128 and ensures data integrity through proper padding mechanisms. It is designed to be efficient, easy to use, and easily integrable into other projects.

## Features

- **AES-128 Encryption and Decryption**: Securely encrypt and decrypt files using the AES-128 algorithm.
- **PKCS#7 Padding**: Automatically handles padding for data that isn't a multiple of the AES block size.
- **Static Library Integration**: Utilizes a static library (`libmontgomery.a`) for efficient modular arithmetic operations.
- **Command-Line Interface**: Simple and intuitive commands for encryption and decryption operations.
- **Customizable Prompt**: (Optional) Enhanced shell prompt for development convenience.
- **Comprehensive Testing**: Includes dummy data files and automated testing scripts to verify functionality.

## Directory Structure

```
.
├── build.bat
├── docs
│   ├── A2 - AES.pdf
│   ├── AES test case.pdf
│   ├── project-2-specs.pdf
│   └── task-breakdown.pdf
├── include
│   ├── aes.h
│   ├── aes_tables.h
│   ├── aes_types.h
│   ├── file_io.h
│   ├── help.h
│   ├── key_schedule.h
│   ├── table_gen.h
│   └── utils.h
├── Makefile
├── README.md
└── src
    ├── aes.c
    ├── aes_tables.c
    ├── file_io.c
    ├── help.c
    ├── key_schedule.c
    ├── main.c
    ├── table_gen.c
    └── utils.c
```

## Prerequisites

Before building and running the AES Encryption and Decryption Tool, ensure that your system meets the following requirements:

- **Operating System**: Unix-like systems (Linux, macOS)
- **Compiler**: `g++` with support for C++17
- **Build Tools**: `make`
- **Python**: (Optional) Python 3 for running testing scripts

## Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/Nouran-Salah/Computer-Networks-and-Security.git
   cd Computer-Networks-and-Security/aes-encryption
   ```

2. **Ensure Required Directories Exist**

   The `Makefile` will automatically create necessary directories (`build/`, `lib/`, `bin/`) during the build process. However, ensure you have the following structure:

   ```
   aes-encryption-tool/
   ├── build
   ├── bin
   ├── include
   ├── lib
   ├── src
   ├── tests
   ├── Makefile
   └── README.md
   ```

## Building the Project

The project utilizes a `Makefile` for efficient compilation and linking. Follow the steps below to build the project:

1. **Navigate to the Project Directory**

   ```bash
   cd Computer-Networks-and-Security/aes-encryption-tool
   ```

2. **Build the Executable**

   ```bash
   make
   ```

   **What Happens:**

   - Compiles all `.cpp` files in the `src/` directory into object files in the `build/` directory.
   - Creates the static library `lib/libmontgomery.a`.
   - Links `main.o` with `libmontgomery.a` to produce the executable `bin/montgomery_exp`.

3. **Clean Build Artifacts**

   To remove compiled object files, the static library, and the executable, run:

   ```bash
   make clean
   ```

## Usage

The executable `montgomery_exp` is located in the `bin/` directory. It provides options for encrypting and decrypting files using AES-128.

### **Basic Command Structure**

```bash
./bin/montgomery_exp -m <mode> -k <key> <input_file> <output_file>
```

- **`-m`**: Mode of operation
  - `e`: Encrypt
  - `d`: Decrypt
- **`-k`**: AES key (32 hexadecimal characters for AES-128)
- **`<input_file>`**: Path to the input file
- **`<output_file>`**: Path to the output file

### **Examples**

1. **Encrypting a File**

   ```bash
   ./bin/montgomery_exp -m e -k 00112233445566778899aabbccddeeff plaintext.txt ciphertext.bin
   ```

   **Explanation:**

   - **Mode**: Encryption (`-m e`)
   - **Key**: `00112233445566778899aabbccddeeff` (16 bytes / 32 hex characters)
   - **Input File**: `plaintext.txt`
   - **Output File**: `ciphertext.bin`

2. **Decrypting a File**

   ```bash
   ./bin/montgomery_exp -m d -k 00112233445566778899aabbccddeeff ciphertext.bin decrypted.txt
   ```

   **Explanation:**

   - **Mode**: Decryption (`-m d`)
   - **Key**: `00112233445566778899aabbccddeeff` (same key used for encryption)
   - **Input File**: `ciphertext.bin`
   - **Output File**: `decrypted.txt`

### **Key Management**

- **Key Length**: For AES-128, the key must be **32 hexadecimal characters** (16 bytes).
- **Format**: Ensure the key consists of valid hexadecimal characters (`0-9`, `a-f`, `A-F`).
- **Security**: Do not hardcode keys in scripts or source code. Pass them securely via command-line arguments or environment variables.

### **Help Command**

For assistance and to view usage instructions, run the executable without arguments or with the `-h` flag:

```bash
./bin/montgomery_exp -h
```

**Expected Output:**

```
Usage: montgomery_exp -m <mode> -k <key> <input_file> <output_file>
Modes:
  -m e    Encrypt the input file
  -m d    Decrypt the input file
Options:
  -k      AES key (32 hexadecimal characters for AES-128)
  -h      Display this help message
```

## Testing

Thorough testing ensures that the AES Encryption and Decryption Tool functions correctly across various scenarios. Below are guidelines and scripts to assist in testing.

### **1. Dummy Data Files**

#### **a. Text Files**

- **`plaintext.txt`**: Contains sample text for encryption and decryption.

  ```plaintext
  Hello, World!
  This is a dummy data file.
  1234567890abcdef
  Short
  A longer line of text to test padding mechanisms in AES encryption.
  End of dummy data.
  ```

- **Creating `plaintext.txt`:**

  ```bash
  echo -n "Hello, World!" > plaintext.txt
  cat <<EOL > plaintext.txt
  Hello, World!
  This is a dummy data file.
  1234567890abcdef
  Short
  A longer line of text to test padding mechanisms in AES encryption.
  End of dummy data.
  EOL
  ```

#### **b. Binary Files**

- **`binary_dummy.bin`**: Contains random binary data for encryption and decryption.

  **Creating 1KB of Random Binary Data:**

  ```bash
  head -c 1024 /dev/urandom > binary_dummy.bin
  ```

- **Creating 512 Bytes of `0xFF`:**

  ```bash
  dd if=/dev/zero bs=1 count=512 | tr '\0' '\377' > binary_dummy.bin
  ```

#### **c. Hexadecimal Data**

- **`hex_dummy.txt`**: Contains hexadecimal representations of data.

  **Creating `hex_dummy.txt`:**

  ```bash
  echo -n "48656C6C6F2C20776F726C64210A5468697320697320612068657820646174652066696C652E0A313233343536373839306162636465666768696A6B6C6D6E6F707172737475767778797A0A53686F72740A416C6F6E676572206C696E65206F66207465787420746F20746573742070616464696E67206D656368616E69736D7320696E2041455320656E6372797074696F6E2E0A456E64206F662064756D6D7920646174612E0A" > hex_dummy.txt
  ```

### **2. Automated Testing Scripts**

#### **a. Shell Script for Automated Testing (`test_aes.sh`)**

This script automates the process of encrypting and decrypting multiple test files and verifies their integrity.

```bash
#!/bin/bash

# Define key
KEY="00112233445566778899aabbccddeeff"

# Create dummy data files
echo -n "hello, just a test" > plaintext1.txt
cat <<EOL > plaintext2.txt
Hello, World!
This is a dummy data file.
1234567890abcdef
Short
A longer line of text to test padding mechanisms in AES encryption.
End of dummy data.
EOL

head -c 1024 /dev/urandom > binary_dummy.bin

# Array of test files
TEST_FILES=("plaintext1.txt" "plaintext2.txt" "binary_dummy.bin" "empty.txt")

# Create an empty file
> empty.txt

# Function to encrypt and decrypt a file
process_file() {
    local infile=$1
    local outfile_encrypted="${infile}.bin"
    local outfile_decrypted="${infile}_decrypted"

    echo "Processing file: $infile"

    # Encrypt
    ./bin/montgomery_exp -m e -k $KEY "$infile" "$outfile_encrypted"
    if [ $? -ne 0 ]; then
        echo "Encryption failed for $infile"
        return
    fi

    # Decrypt
    ./bin/montgomery_exp -m d -k $KEY "$outfile_encrypted" "$outfile_decrypted"
    if [ $? -ne 0 ]; then
        echo "Decryption failed for $outfile_encrypted"
        return
    fi

    # Compare original and decrypted files
    if cmp -s "$infile" "$outfile_decrypted"; then
        echo "SUCCESS: $infile encrypted and decrypted correctly."
    else
        echo "FAILURE: $infile decrypted data does not match original."
    fi

    echo "--------------------------------------------"
}

# Iterate over test files
for file in "${TEST_FILES[@]}"; do
    process_file "$file"
done
```

**How to Use:**

1. **Save the Script:**

   Save the above script to a file named `test_aes.sh` in your project's root directory.

2. **Make the Script Executable:**

   ```bash
   chmod +x test_aes.sh
   ```

3. **Run the Script:**

   ```bash
   ./test_aes.sh
   ```

**Expected Output:**

```plaintext
Processing file: plaintext1.txt
Performing encryption...
Padding last block with 15 bytes of value 0x0F.
Operation completed successfully.
Performing decryption...
Padding length detected: 15
Valid padding. Removing 15 bytes.
Writing last block with unpadded length: 17
Operation completed successfully.
SUCCESS: plaintext1.txt encrypted and decrypted correctly.
--------------------------------------------
Processing file: plaintext2.txt
Performing encryption...
Padding last block with 1 bytes of value 0x01.
Operation completed successfully.
Performing decryption...
Padding length detected: 1
Valid padding. Removing 1 bytes.
Writing last block with unpadded length: [Original Length]
Operation completed successfully.
SUCCESS: plaintext2.txt encrypted and decrypted correctly.
--------------------------------------------
Processing file: binary_dummy.bin
Performing encryption...
Padding last block with [N] bytes of value 0x0F.
Operation completed successfully.
Performing decryption...
Padding length detected: [N]
Valid padding. Removing [N] bytes.
Writing last block with unpadded length: 1024
Operation completed successfully.
SUCCESS: binary_dummy.bin encrypted and decrypted correctly.
--------------------------------------------
Processing file: empty.txt
Performing encryption...
Padding last block with 16 bytes of value 0x10.
Operation completed successfully.
Performing decryption...
Padding length detected: 16
Valid padding. Removing 16 bytes.
Writing last block with unpadded length: 0
Operation completed successfully.
SUCCESS: empty.txt encrypted and decrypted correctly.
--------------------------------------------
```

_(Note: `[N]` and `[Original Length]` will vary based on the file size and padding applied.)_

### **3. Manual Testing**

You can manually test encryption and decryption using the provided dummy data files.

1. **Encrypt a File**

   ```bash
   ./bin/montgomery_exp -m e -k 00112233445566778899aabbccddeeff plaintext.txt ciphertext.bin
   ```

2. **Decrypt the Ciphertext**

   ```bash
   ./bin/montgomery_exp -m d -k 00112233445566778899aabbccddeeff ciphertext.bin decrypted.txt
   ```

3. **Verify the Decrypted File**

   ```bash
   cmp plaintext.txt decrypted.txt && echo "Files are identical." || echo "Files differ."
   ```

   **Expected Output:**

   ```
   Files are identical.
   ```

## Contributing

Contributions are welcome! If you'd like to contribute to the AES Encryption and Decryption Tool, please follow these steps:

1. **Fork the Repository**

   Click the "Fork" button at the top-right corner of the repository page to create a personal copy.

2. **Clone Your Fork**

   ```bash
   git clone https://github.com/Nouran-Salah/Computer-Networks-and-Security.git
   cd Computer-Networks-and-Security/aes-encryption-tool
   ```

3. **Create a New Branch**

   ```bash
   git checkout -b feature/YourFeatureName
   ```

4. **Make Your Changes**

   Implement your feature or bug fix.

5. **Commit Your Changes**

   ```bash
   git commit -m "Add feature: YourFeatureName"
   ```

6. **Push to Your Fork**

   ```bash
   git push origin feature/YourFeatureName
   ```

7. **Create a Pull Request**

   Navigate to your fork on GitHub and click the "Compare & pull request" button. Provide a clear description of your changes and submit the pull request.

## License

This project is licensed under the [MIT License](../LICENSE).

# **DES Encryption/Decryption Project**

## **Overview**

This project implements the **Data Encryption Standard (DES)** algorithm for encrypting and decrypting files. DES processes 64-bit data blocks using a 56-bit key and performs 16 rounds of Feistel structure transformations. This implementation includes encryption and decryption functionalities, robust file error handling, prompts for overwriting files, and a flexible command-line interface with support for both short and long options.

Key features:

- File encryption and decryption
- Command-line interface with short and long options
- Support for hexadecimal keys and file-based keys
- Comprehensive file error handling and prompts for existing files

---

## **Project Structure**

```plaintext
des-encryption/
├── graph_images/                # Contains generated images from graph files
│   ├── callgraph.png            # PNG image of the caller graph
│   ├── callee_graph.png         # PNG image of the callee graph
├── docs/                        # Documentation and project specifications
│   ├── fips46-3.pdf             # FIPS standard document for DES
│   ├── project-1-specs.pdf      # Project specifications
│   └── the-des-algorithm-illustrated.pdf  # Visual guide to DES algorithm
├── graph/                       # Intermediate graph files
│   ├── callgraph.dot            # Generated DOT file for caller graph
│   ├── callgraph.txt            # Caller graph output from `cflow`
│   ├── callee_graph.dot         # Generated DOT file for callee graph
│   ├── callee_graph.txt         # Callee graph output from `cflow`
│   └── scripts/                 # Scripts for generating graphs
│       ├── cflow_to_callee_dot.py # Script to convert cflow to callee graph in .dot
│       ├── cflow_to_caller_dot.py # Script to convert cflow to caller graph in .dot
│       └── generate_graphs.sh   # Script to automate graph generation
├── inc/                         # Header files
│   ├── des.h                    # Header file for DES functions
│   └── utils.h                  # Header file for utility functions
├── src/                         # Source files for the project
│   ├── des.c                    # Implementation of the DES algorithm
│   ├── main.c                   # Main function for CLI handling
│   └── utils.c                  # Utility functions
├── test/                        # Directory for test cases and test files
│   ├── test_input.txt           # Sample input file for testing encryption
│   ├── test_key.txt             # Sample key file for testing
│   └── test_output.txt          # Expected output file for validation
├── .gitignore                   # Ignore build, generated files, and temporary files
├── Makefile                     # Makefile for building the project on Linux
├── README.md                    # Project documentation and instructions
└── plaintext.txt                # Sample plaintext file for testing encryption (could be moved to `test/`)
```

---

## **Files and Directories**

### **`inc/` Directory**

- **`des.h`**: Contains function declarations for DES, including `des()`, `key_schedule()`, `initial_permutation()`, `final_permutation()`, and other essential DES components.
- **`utils.h`**: Contains utility function declarations such as `print_usage()`, `file_exists()`, `hex_to_bytes()`, and other helper functions.

### **`src/` Directory**

- **`des.c`**: Implements the DES algorithm, including key scheduling, permutations, Feistel rounds, and the main `des()` function for encryption and decryption.
- **`main.c`**: Contains the `main` function for handling command-line arguments, user input, and orchestrating encryption or decryption based on user commands.
- **`utils.c`**: Implements utility functions for file checking (`file_exists()`), hex-to-byte conversion (`hex_to_bytes()`), file reading/writing, usage display (`print_usage()`), and other support functions.

### **`Makefile`**

- **Purpose**: Automates the build process on Linux.
- **Functionality**:
  - Compiles source files in `src/` and outputs object files to `obj/`.
  - Links object files to generate the executable `des_encryption`.
  - Provides a `clean` target to remove build artifacts and generated graph images.

### **`build.bat`**

- **Purpose**: Automates the build process on Windows.
- **Functionality**:
  - Compiles source files in `src\` using GCC and places object files in `obj\`.
  - Links object files to produce `des_encryption.exe`.
  - Provides feedback to indicate the build progress.

### **`docs/` Directory**

Contains documentation and reference materials:

- **`fips46-3.pdf`**: The official FIPS 46-3 standard document for DES, detailing algorithm specifications.
- **`project-1-specs.pdf`**: Project specifications, including requirements and objectives.
- **`the-des-algorithm-illustrated.pdf`**: A visual guide to DES for easier understanding.

### **`graph_images/` Directory**

- **Purpose**: Stores generated graph images (e.g., caller and callee graphs).
- **Contents**: PNG images of the call graph and callee graph generated from source files.

### **`graph/` Directory**

Contains files and scripts related to graph generation:

- **`.dot` and `.txt` Files**: Generated DOT and text files for caller and callee graphs.
- **`scripts/`**: Python scripts and shell scripts for generating graphs using `cflow` and `dot`.

### **`plaintext.txt`**

- **Purpose**: Sample plaintext file for testing DES encryption and decryption functionality.

### **`README.md`**

- **Purpose**: Provides comprehensive project documentation, including usage instructions, project structure, and build guidance.

---

## **Features**

1. **DES Algorithm**: Implements DES with initial/final permutations, Feistel rounds, key scheduling, and S-box substitutions.
2. **Command-Line Interface (CLI)**: Supports short and long options for specifying encryption/decryption, keys, and file paths.
3. **File Handling**: Allows file-based encryption and decryption, with user prompts to manage existing output files.
4. **Hexadecimal Key Input**: Accepts either a direct hexadecimal key or a key file (binary or hex).

---

## **Usage**

### **Command-Line Arguments**

```bash
# On Linux
./des_encryption -m <mode> -k <key> -f <keyfile> <input_file> <output_file>

# On Windows
des_encryption.exe -m <mode> -k <key> -f <keyfile> <input_file> <output_file>
```

- **`mode`** (`-m` or `--mode`): Use `"e"` for encryption or `"d"` for decryption.
- **`key`** (`-k` or `--key`): 8-byte hexadecimal key (e.g., `0123456789ABCDEF`).
- **`keyfile`** (`-f` or `--keyfile`): Path to a file containing an 8-byte binary or hexadecimal key.
- **`input_file`**: File to be encrypted or decrypted.
- **`output_file`**: Output file for ciphertext (encryption) or plaintext (decryption).

### **Examples**

#### **Encryption**

```bash
# On Linux
./des_encryption -m e -k 0123456789ABCDEF plaintext.txt ciphertext.bin

# On Windows
des_encryption.exe -m e -k 0123456789ABCDEF plaintext.txt ciphertext.bin
```

#### **Decryption**

```bash
# On Linux
./des_encryption -m d -k 0123456789ABCDEF ciphertext.bin decrypted.txt

# On Windows
des_encryption.exe -m d -k 0123456789ABCDEF ciphertext.bin decrypted.txt
```

#### **Using a Key File**

```bash
./des_encryption -m e -f keyfile.bin plaintext.txt ciphertext.bin
```

This example uses `keyfile.bin` instead of specifying a key directly.

---

## **Handling Existing Output Files**

When the output file already exists, the program prompts:

```plaintext
Warning: ciphertext.bin already exists. Append or (c)lear the contents? (a/c):
```

- Choose **`a`** to append.
- Choose **`c`** to clear before writing.

---

## **Build Instructions**

### **Linux**

To build the project, navigate to the root directory and run:

```bash
make
```

### **Windows**

Ensure GCC is installed (e.g., MinGW-w64), then run:

```batch
build.bat
```

To remove compiled artifacts, run `make clean` on Linux or `clean.bat` on Windows.

---

## **Running the Program**

After building, run the program as follows:

```bash
# On Linux
./des_encryption -m e -k 0123456789ABCDEF plaintext.txt ciphertext.bin

# On Windows
des_encryption.exe -m e -k 0123456789ABCDEF plaintext.txt ciphertext.bin
```

---

## **Error Handling**

1. **Invalid Number of Arguments**:

   - Displays usage if incorrect arguments are provided.

2. **Invalid Mode**:
   - Ensures mode is `"e"` or `"d"` only,

with an error otherwise.

3. **Invalid Key Format**:

   - Validates that the key is a 16-character hexadecimal string.

4. **File Errors**:
   - Displays an error if files cannot be accessed.

---

## **Testing**

1. **Test Vectors**: Use known DES test vectors (e.g., from **FIPS PUB 81**) to verify correctness.
2. **Unit Tests**: Include tests for key generation, permutations, Feistel functions, and utility functions.
3. **Cross-Platform Testing**: Confirm the program’s compatibility on both Linux and Windows.

---

## **License**

This project is licensed under the **MIT License**. Refer to the `LICENSE` file for details.

---

## **References**

- **FIPS 46-3**: Data Encryption Standard (DES).
- **The DES Algorithm Illustrated**: Visual guide to DES.
- **Project Specifications**: Detailed project requirements.
- **Task Breakdown**: Document outlining project tasks and milestones.

---

## **Contributing**

Contributions are welcome! Please follow these guidelines:

- Fork the repository and create a new branch for your feature or bug fix.
- Ensure your code follows project coding standards.
- Update documentation as necessary.
- Submit a pull request with a clear description of your changes.

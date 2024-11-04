# **DES Encryption/Decryption Project**

## **Overview**

This project implements the **Data Encryption Standard (DES)** algorithm for encrypting and decrypting files. The DES algorithm processes 64-bit data blocks using a 56-bit key and performs 16 rounds of Feistel structure transformations. This project includes encryption and decryption functionalities, error handling for file operations, user prompts for overwriting files, and a flexible command-line interface that supports both short and long options.

Key features:

- Encryption and decryption of files
- Command-line interface for user interaction with short and long options
- Handling of hexadecimal keys and file-based keys
- File error handling and warnings for existing files

---

## **Project Structure**

```plaintext
des-encryption/
├── build/                         # Compiled output and generated graph images
│   ├── callgraph.png              # PNG image of the caller graph
│   ├── callee_graph.png           # PNG image of the callee graph
├── docs/                          # Documentation and project specifications
│   ├── fips46-3.pdf               # FIPS standard document for DES
│   ├── project-1-specs.pdf        # Project specifications
│   └── the-des-algorithm-illustrated.pdf  # Visual guide to DES algorithm
├── graph/                         # Intermediate graph files
│   ├── callgraph.dot              # Generated DOT file for caller graph
│   ├── callgraph.txt              # Caller graph output from `cflow`
│   ├── callee_graph.dot           # Generated DOT file for callee graph
│   ├── callee_graph.txt           # Callee graph output from `cflow`
│   └── scripts/                   # Scripts for generating graphs
│       ├── cflow_to_callee_dot.py # Script to convert cflow to callee graph in .dot
│       ├── cflow_to_caller_dot.py # Script to convert cflow to caller graph in .dot
│       └── generate_graphs.sh     # Script to automate graph generation
├── inc/                           # Header files
│   ├── des.h                      # Header file for DES functions
│   └── utils.h                    # Header file for utility functions
├── src/                           # Source files for the project
│   ├── des.c                      # Implementation of the DES algorithm
│   ├── main.c                     # Main function for CLI handling
│   └── utils.c                    # Utility functions
├── test/                          # Directory for test cases and test files
│   ├── test_input.txt             # Sample input file for testing encryption
│   ├── test_key.txt               # Sample key file for testing
│   └── test_output.txt            # Expected output file for validation
├── .gitignore                     # Ignore build, generated files, and temporary files
├── Makefile                       # Makefile for building the project
├── README.md                      # Project documentation and instructions
└── plaintext.txt                  # Sample plaintext file for testing encryption (could be moved to `test/`)
```

---

## **Files and Directories**

### **`inc/` Directory**

- **`des.h`**: Contains function declarations for DES-related functions such as `des()`, `key_schedule()`, `initial_permutation()`, `final_permutation()`, and other essential components of the DES algorithm.
- **`utils.h`**: Contains utility function declarations for functions such as `print_usage()`, `file_exists()`, `hex_to_bytes()`, `bytes_to_hex()`, and other helper functions used throughout the project.

### **`src/` Directory**

- **`des.c`**: Implements the DES algorithm, including key scheduling, initial permutation, final permutation, Feistel functions, and the main `des()` function that orchestrates the encryption and decryption processes.
- **`main.c`**: Contains the `main` function that handles command-line arguments, user input, and drives the encryption and decryption workflows based on user commands.
- **`utils.c`**: Implements utility functions such as checking if a file exists (`file_exists()`), converting hexadecimal keys to bytes (`hex_to_bytes()`), reading and writing files, displaying usage information (`print_usage()`), and other supportive tasks.

### **`Makefile`**

- **Purpose**: Automates the build process for the project on Linux systems.
- **Functionality**:
  - Compiles the source files in the `src/` directory.
  - Places the compiled object files in the `obj/` directory (created if it doesn't exist).
  - Links the object files to generate the executable file named `des_encryption`.
  - Provides a `clean` target to remove build artifacts.

### **`build.bat`**

- **Purpose**: Automates the build process for the project on Windows systems.
- **Functionality**:
  - Compiles the source files in the `src\` directory using GCC.
  - Places the compiled object files in the `obj\` directory (created if it doesn't exist).
  - Links the object files to generate the executable file named `des_encryption.exe`.
  - Echoes messages to indicate the progress of the build process.

### **`docs/` Directory**

- **Contains documentation and reference materials relevant to the project**:
  - **`fips46-3.pdf`**: The official FIPS 46-3 standard document for the Data Encryption Standard (DES), providing detailed specifications of the algorithm.
  - **`project-1-specs.pdf`**: The project's specification document outlining requirements, objectives, and deliverables.
  - **`task-breakdown.pdf`**: A document that breaks down the project into tasks and milestones, helping in project management and tracking progress.
  - **`the-des-algorithm-illustrated.pdf`**: An illustrated guide that explains the DES algorithm visually, aiding in understanding the encryption and decryption processes.

### **`plaintext.txt`**

- **Purpose**: A sample plaintext file used for testing the encryption and decryption functionalities of the program.
- **Contents**: Contains text data that can be encrypted using the DES algorithm implemented in the project. Serves as an example input for demonstration and testing purposes.

### **`README.md`**

- **Purpose**: Provides comprehensive documentation for the project.
- **Contents**:
  - **Project Overview**: An introduction to the project, its goals, and its significance.
  - **Installation Instructions**: Steps on how to set up the development environment and dependencies.
  - **Building the Project**:
    - Instructions for building the project on **Linux** using the `Makefile`.
    - Instructions for building the project on **Windows** using `build.bat`.
  - **Usage Guide**: How to run the executable, command-line options, and examples of encrypting and decrypting files.
  - **Project Structure**: An outline of the project's directory structure and explanations of each file and directory.
  - **Contributing**: Guidelines for contributing to the project, if applicable.
  - **License Information**: Details about the project's license.
  - **References**: Links to resources and documents in the `docs/` directory for further reading.

---

## **Features**

1. **DES Algorithm**: Implements the full DES algorithm including initial and final permutation, Feistel rounds, key scheduling, and S-box substitutions.
2. **Command-Line Interface (CLI)**: Allows users to provide inputs for encryption and decryption via command-line arguments with both short and long options.
3. **File Handling**: Supports reading plaintext or ciphertext from files and writing the output to files. It also prompts users for handling existing output files.
4. **Hexadecimal Key Input**: Takes an 8-byte (64-bit) key in hexadecimal format or as a file (binary or hexadecimal) from the command line.

---

## **Usage**

### **Command-Line Arguments**

```bash
# On Linux
./des_encryption -m <mode> -k <key> -f <keyfile> <input_file> <output_file>

# On Windows
des_encryption.exe -m <mode> -k <key> -f <keyfile> <input_file> <output_file>
```

- **`mode`** (`-m` or `--mode`): Either `"e"` for encryption or `"d"` for decryption.
- **`key`** (`-k` or `--key`): An 8-byte hexadecimal key (e.g., `0123456789ABCDEF`).
- **`keyfile`** (`-f` or `--keyfile`): Path to a file containing an 8-byte key (either in binary or 16-character hex string).
- **`input_file`**: The file to be encrypted or decrypted.
- **`output_file`**: The file where the output (ciphertext for encryption, plaintext for decryption) will be saved.

### **Encryption Example**

```bash
# On Linux
./des_encryption -m e -k 0123456789ABCDEF plaintext.txt ciphertext.bin

# On Windows
des_encryption.exe -m e -k 0123456789ABCDEF plaintext.txt ciphertext.bin
```

### **Decryption Example**

```bash
# On Linux
./des_encryption -m d -k 0123456789ABCDEF ciphertext.bin decrypted.txt

# On Windows
des_encryption.exe -m d -k 0123456789ABCDEF ciphertext.bin decrypted.txt
```

### **Using a Key File**

```bash
./des_encryption -m e -f keyfile.bin plaintext.txt ciphertext.bin
```

This command uses a key from `keyfile.bin` instead of directly specifying it with `-k`.

---

## **Handling Existing Output Files**

When running the program, if the output file (e.g., `ciphertext.bin` or `decrypted.txt`) already exists, the user will be prompted:

```plaintext
Warning: ciphertext.bin already exists. Append or (c)lear the contents? (a/c):
```

- Choose **`a`** to append to the existing file.
- Choose **`c`** to clear the file before writing the new output.

---

## **Build Instructions**

### **Linux**

To build the project, navigate to the project’s root directory and run:

```bash
make
```

### **Windows**

Ensure you have installed GCC (e.g., MinGW-w64) and run:

```batch
build.bat
```

To remove compiled artifacts, run `make clean` (Linux) or `clean.bat` (Windows).

---

## **Running the Program**

After building, you can run:

```bash
# On Linux
./des_encryption -m e -k 0123456789ABCDEF plaintext.txt

 ciphertext.bin

# On Windows
des_encryption.exe -m e -k 0123456789ABCDEF plaintext.txt ciphertext.bin
```

---

## **Error Handling**

1. **Invalid Number of Arguments**:

   - Displays usage instructions if the correct number of arguments is not provided.

2. **Invalid Mode**:

   - Ensures mode is `"e"` or `"d"` only; otherwise, shows an error.

3. **Invalid Key Format**:

   - Validates that the key is in hexadecimal format and the correct length.

4. **File Errors**:
   - Displays an error if input or output files cannot be opened.

---

## **Testing**

1. **Test Vectors**: Use known test vectors from standards like **FIPS PUB 81** to verify the correctness of the implementation.
2. **Unit Tests**: Create tests for key generation, permutations, Feistel function, and utility functions to ensure each component works correctly.
3. **Cross-Platform Testing**: Verify that the program works as expected on both Linux and Windows systems.

---

## **License**

This project is licensed under the **MIT License**. See the `LICENSE` file for details.

---

## **References**

- **FIPS 46-3**: Data Encryption Standard (DES).
- **The DES Algorithm Illustrated**: Visual guide to understanding DES.
- **Project Specifications**: Detailed project requirements and objectives.
- **Task Breakdown**: Document outlining project tasks and milestones.

---

## **Contributing**

Contributions are welcome! Please follow these guidelines:

- Fork the repository and create a new branch for your feature or bug fix.
- Ensure your code follows the project's coding standards.
- Update documentation as necessary.
- Submit a pull request with a clear description of your changes.

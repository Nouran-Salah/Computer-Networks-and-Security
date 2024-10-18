# **DES Encryption/Decryption Project**

## **Overview**

This project implements the **Data Encryption Standard (DES)** algorithm for encrypting and decrypting files. The DES algorithm processes 64-bit data blocks using a 56-bit key and performs 16 rounds of Feistel structure transformations. This project provides both encryption and decryption functionalities, along with error handling for file operations, user prompts for overwriting/clearing files, and command-line usage.

The project includes:

- Encryption and decryption of files
- Command-line interface for user interaction
- Handling of hexadecimal keys
- File error handling and warnings for existing files

---

## **Project Structure**

```plaintext
DES_Project/
├── inc/
│   ├── des.h               # Header file for DES functions
│   ├── utils.h             # Header file for utility functions
├── src/
│   ├── des.c               # Source file implementing DES algorithm
│   ├── main.c              # Source file with the main function and CLI handling
│   ├── utils.c             # Source file with utility functions
├── Makefile                # Makefile for building the project
└── README.md               # Project documentation
```

---

## **Files and Directories**

### **`inc/` Directory**

- **`des.h`**: Contains function declarations for DES-related functions such as `des()`, `key_schedule()`, `initial_permutation()`, etc.
- **`utils.h`**: Contains utility function declarations for functions such as `print_usage()`, `file_exists()`, `hex_to_bytes()`, etc.

### **`src/` Directory**

- **`des.c`**: Implements the DES algorithm, including key scheduling, initial permutation, final permutation, and Feistel functions.
- **`main.c`**: Contains the main function that handles command-line arguments and drives the encryption and decryption processes.
- **`utils.c`**: Implements utility functions such as file existence checking, hexadecimal key conversion, file handling, and user prompts.

### **`Makefile`**

- The Makefile automates the build process for the project. It compiles the source files and generates an executable file.

### **`README.md`**

- This file provides comprehensive documentation for the project.

---

## **Features**

1. **DES Algorithm**: Implements the full DES algorithm including initial and final permutation, Feistel rounds, key scheduling, and S-box substitutions.
2. **Command-Line Interface (CLI)**: Allows users to provide inputs for encryption and decryption via command-line arguments.
3. **File Handling**: Supports reading plaintext or ciphertext from files and writing the output to files. It also prompts users for handling existing ciphertext files.
4. **Hexadecimal Key Input**: Takes an 8-byte (64-bit) key in hexadecimal format from the command line.

---

## **Usage**

### **Command-Line Arguments**

```bash
./program <mode> <key> <input_file> <output_file>
```

- **`mode`**: Either `"e"` for encryption or `"d"` for decryption.
- **`key`**: An 8-byte hexadecimal key (e.g., `0123456789ABCDEF`).
- **`input_file`**: The file to be encrypted or decrypted.
- **`output_file`**: The file where the output (ciphertext for encryption, plaintext for decryption) will be saved.

### **Encryption Example**

```bash
./program e 0123456789ABCDEF plaintext.txt ciphertext.bin
```

This command encrypts `plaintext.txt` using the key `0123456789ABCDEF` and saves the result to `ciphertext.bin`.

### **Decryption Example**

```bash
./program d 0123456789ABCDEF ciphertext.bin decrypted.txt
```

This command decrypts `ciphertext.bin` using the key `0123456789ABCDEF` and saves the result to `decrypted.txt`.

---

## **Key Input Format**

The key must be provided as a **16-character hexadecimal string** (representing 8 bytes). Each pair of hexadecimal digits corresponds to one byte of the DES key.

Example: `0123456789ABCDEF` is a valid 64-bit DES key.

---

## **Handling Existing Output Files**

When running the program, if the output file (e.g., `ciphertext.bin` or `decrypted.txt`) already exists, the user will be prompted:

```plaintext
Warning: ciphertext.bin already exists. Append or (c)lear the contents? (a/c):
```

- Choose **`a`** to append to the existing file.
- Choose **`c`** to clear the file before writing the new output.

---

## **File Not Found Handling**

If the input file does not exist, the program will display an error message and terminate:

```plaintext
Plaintext file does not exist.
```

---

## **Build Instructions**

To build the project, simply run the following command from the project’s root directory:

```bash
make
```

This will compile all the source files (`des.c`, `main.c`, `utils.c`) and generate the `program` executable.

### **Cleaning Up**

To remove all the compiled object files and the executable, run:

```bash
make clean
```

---

## **Sample Input and Output**

### **Example Input:**

- **Key**: `0123456789ABCDEF`
- **Plaintext File** (`plaintext.txt`):
  ```plaintext
  Hello, this is a test message.
  ```

### **Example Output (Hex)**:

- **Ciphertext File** (`ciphertext.bin`):
  ```plaintext
  7A38A9451F52A3B2186B6E4D2B6C13F2
  ```

---

## **Error Handling**

1. **Invalid Number of Arguments**:

   - If the user does not provide exactly 5 arguments (including the program name), the program will display usage instructions:

   ```plaintext
   Usage: ./program e|d <key> <input_file> <output_file>
   ```

2. **Invalid Mode**:

   - If the user provides an invalid mode (anything other than "e" for encryption or "d" for decryption), the program will show an error message.

3. **Invalid Key Format**:
   - If the key is not provided in hexadecimal format or is of incorrect length, the program will exit with an error.

---

## **Development Workflow**

### **Team Member Tasks**

The project was divided into several tasks for team members:

1. **Task 1: Initial Permutation (IP) and Final Permutation (FP)** – Handled in `des.c`
2. **Task 2: Key Scheduling and Round Key Generation** – Handled in `des.c`
3. **Task 3: Feistel Function and S-Box Substitution** – Handled in `des.c`
4. **Task 4: DES Encryption/Decryption Logic** – Handled in `des.c`
5. **Task 5: File Handling, Command-Line Interface, and Build System** – Handled in `main.c` and `utils.c`

---

## **Testing**

1. **Test Vectors**: You can test the encryption and decryption using known test vectors from standards like **FIPS PUB 81**.
2. **Unit Tests**: Write tests to ensure the correctness of key generation, permutations, and file handling functions.

---

## **License**

This project is licensed under the **MIT License**. See the `LICENSE` file for details.

p# **Computer-Networks-and-Security**

This repository is dedicated to the course projects and tasks for **Computer Networks and Security** at the **Faculty of Engineering, Ain Shams University**. Throughout this course, we will be exploring key concepts in computer networks and cybersecurity through various coding assignments, security implementations, and practical tasks.

The repository will cover several key areas of security, including:

- Encryption algorithms (e.g., DES, AES)
- Network security protocols
- Authentication mechanisms
- Firewalls, VPNs, and IDS/IPS systems
- Public and private key cryptography
- Secure socket layer (SSL) and transport layer security (TLS)
- Penetration testing and security auditing

---

## **Table of Contents**

1. [Introduction](#introduction)
2. [Course Overview](#course-overview)
3. [Projects and Tasks](#projects-and-tasks)
4. [Project Structure](#project-structure)
5. [Setup and Installation](#setup-and-installation)
6. [Contributors](#contributors)
7. [License](#license)

---

## **Introduction**

This repository will be continuously updated throughout the course as we work on different projects and complete various tasks that aim to enhance our understanding of network security and its importance in today's digital world. The projects included will involve both theoretical and practical implementations of security concepts, with a focus on **C programming**, **cryptography**, **network protocols**, and **secure communication**.

Each project will include:

- Full documentation
- Sample inputs and outputs
- Test cases
- Complete source code
- Instructions for compiling and running the code

---

## **Course Overview**

This course introduces students to the fundamentals of computer networks and cybersecurity. It covers various topics such as:

- **Network layers**: Understand how each layer (from physical to application) contributes to secure communication.
- **Cryptography**: Dive into encryption algorithms, such as DES and AES, and explore both symmetric and asymmetric key cryptography.
- **Network Security**: Learn about securing networks with firewalls, IDS/IPS, and implementing secure communication protocols like SSL/TLS.
- **Security Protocols**: Understand key security protocols, including IPsec, SSH, and VPNs.
- **Penetration Testing**: Practice ethical hacking and vulnerability testing techniques to strengthen defenses.
- **Authentication**: Learn about multi-factor authentication and secure login mechanisms.

---

## **Projects and Tasks**

### **1. DES Encryption Algorithm**

- **Task**: Implement the Data Encryption Standard (DES) in C.
- **Description**: Develop a command-line tool for encrypting and decrypting files using DES.
- **Files**: Includes full implementation, handling of plaintext and ciphertext, key generation, and user prompts.
- **Topics Covered**: Symmetric key cryptography, encryption, decryption, and file handling.

### **2. Secure Communication Protocols**

- **Task**: Implement basic secure communication using socket programming.
- **Description**: Use socket programming to demonstrate secure client-server communication with encryption.
- **Topics Covered**: Network programming, TLS, SSL, encryption.

### **3. Firewall Configuration and Rules**

- **Task**: Configure a basic firewall with iptables.
- **Description**: Set up firewall rules to protect a local network.
- **Topics Covered**: Firewall, iptables, packet filtering.

### **4. Penetration Testing**

- **Task**: Conduct penetration testing on a vulnerable network.
- **Description**: Simulate attacks and vulnerabilities using tools like Wireshark and nmap.
- **Topics Covered**: Vulnerability testing, network monitoring, ethical hacking.

... 

---

## **Project Structure**

Each project in this repository will follow a similar structure to ensure consistency and ease of use.

```
/Computer-Networks-and-Security/
    ├── /des-encryption/               # Folder for the DES project
    │    ├── /src/                     # Source files for DES project
    │    ├── /inc/                     # Header files
    │    ├── Makefile                  # Makefile to compile the project
    │    └── README.md                 # Documentation for the project
    ├── /firewall-setup/               # Folder for firewall project
    │    ├── rules.txt                 # Firewall rules file
    │    └── README.md                 # Documentation for firewall setup
    ├── /secure-communication/         # Folder for the secure communication project
    │    └── ...                       # Relevant files for this project
    └── README.md                      # Main README for the entire repo
```

Each project will include:

- **Source code**: Organized in `src/` directory
- **Headers**: Located in the `inc/` directory
- **Makefile**: For easy compilation and building of the project
- **README**: Detailing how the project works, usage, input/output format, etc.

---

## **Setup and Installation**

### **Prerequisites**

- A C compiler (GCC recommended)
- Linux environment (Ubuntu recommended)
- Git for version control

### **Clone the Repository**

```bash
git clone https://github.com/Nouran-Salah/Computer-Networks-and-Security.git
cd Computer-Networks-and-Security
```

### **Compile and Run Projects**

Each project will come with its own `Makefile`. To compile a project:

```bash
cd des-encryption
make
./program "e" <key> <plaintext_file> <ciphertext_file>  # Encrypt
./program "d" <key> <ciphertext_file> <plaintext_file>  # Decrypt
```

---

## **Contributors**

This repository is maintained and contributed to by students from **Faculty of Engineering, Ain Shams University** as part of the **Computer Networks and Security** course.

- [Nouran Salah](https://github.com/Nouran-Salah)
- [Omnia Fathy](https://github.com/AGX18)
- [Rodaina Mohamed](https://github.com/wiserODec)
- [Sarah Tarek](https://github.com/Sarah-Tarek)
- [CodeNinja](https://github.com/CodeNinja)

---

## **License**

This repository and its contents are licensed under the **MIT License**. Please refer to the `LICENSE` file for more details.

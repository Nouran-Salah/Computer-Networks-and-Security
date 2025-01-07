/**
 * @file file_io.h
 * @brief File input/output operations for AES encryption and decryption.
 */

#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Reads the entire content of a file into a buffer.
 *
 * @param[in]   filename  Path to the file to read.
 * @param[out]  data      Pointer to a buffer that will hold the file content (allocated inside the function).
 * @param[out]  length    Pointer to a size_t variable that will hold the size of the data.
 * @return      0 on success, non-zero on failure.
 *
 * @note The caller is responsible for freeing the allocated memory for `data`.
 */
int read_file(const char *filename, uint8_t **data, size_t *length);

/**
 * @brief Writes data to a file.
 *
 * @param[in]  filename  Path to the file to write.
 * @param[in]  data      Pointer to the buffer containing data to write.
 * @param[in]  length    Size of the data to write.
 * @return     0 on success, non-zero on failure.
 */
int write_file(const char *filename, const uint8_t *data, size_t length);

/**
 * @brief Reads an AES key from a file in hexadecimal format.
 *
 * @param[in]   filename  Path to the key file.
 * @param[out]  key       Buffer to store the key (must be pre-allocated).
 * @param[in]   key_size  Expected size of the key in bytes.
 * @return      0 on success, non-zero on failure.
 */
int read_key(const char *filename, uint8_t *key, size_t key_size);

#endif // FILE_IO_H

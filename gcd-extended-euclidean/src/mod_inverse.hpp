#ifndef MOD_INVERSE_HPP
#define MOD_INVERSE_HPP

/**
 * @brief Finds the Modular Inverse of an integer x modulo y.
 *
 * This function uses the Extended Euclidean Algorithm to find the modular inverse of x modulo y.
 * The modular inverse of x is an integer m such that \f$ (x \cdot m) \mod y = 1 \f$.
 * If the modular inverse exists (i.e., gcd(x, y) = 1), the function returns it. Otherwise, it returns -1.
 *
 * @param[in] x The integer whose modular inverse is to be found.
 * @param[in] y The modulus.
 * @return The modular inverse of x modulo y if it exists; otherwise, -1.
 */
int mod_inverse(int x, int y);

#endif // MOD_INVERSE_HPP

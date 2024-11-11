#ifndef GCD_HPP
#define GCD_HPP

#include <tuple>

/**
 * @brief Computes the Greatest Common Divisor (GCD) of two integers using the Euclidean Algorithm.
 *
 * This function implements the Euclidean Algorithm to find the GCD of two non-negative integers.
 * The GCD of two integers is the largest integer that divides both of them without leaving a remainder.
 *
 * @param[in] a The first integer.
 * @param[in] b The second integer.
 * @return The GCD of a and b.
 */
int gcd(int a, int b);

/**
 * @brief Computes the Extended Euclidean Algorithm.
 *
 * This function calculates the GCD of two integers, a and b, and also finds coefficients x and y
 * that satisfy Bézout's identity: \f$ ax + by = \text{gcd}(a, b) \f$.
 * The Extended Euclidean Algorithm is useful for applications such as finding modular inverses.
 *
 * @param[in] a The first integer.
 * @param[in] b The second integer.
 * @return A tuple containing:
 *         - gcd (int): The GCD of a and b.
 *         - x (int): The coefficient of a in Bézout's identity.
 *         - y (int): The coefficient of b in Bézout's identity.
 */
std::tuple<int, int, int> extended_gcd(int a, int b);

#endif // GCD_HPP

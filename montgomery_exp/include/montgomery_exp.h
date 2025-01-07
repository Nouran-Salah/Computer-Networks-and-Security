#ifndef MONTGOMERY_EXP_H
#define MONTGOMERY_EXP_H

/**
 * @class MontgomeryExp
 * @brief Encapsulates modular exponentiation (Montgomery) in an OOP manner.
 *
 * The class provides:
 * - A method to compute (a^b) % n using an iterative square-and-multiply approach.
 * - Automatic tracking of the number of multiplications performed.
 */
class MontgomeryExp
{
public:
    /**
     * @brief Default constructor initializes statistics.
     */
    MontgomeryExp();

    /**
     * @brief Compute (a^b) mod n.
     *
     * The function also counts the number of multiplications
     * (including those for squaring).
     *
     * @param a Base (the number to be exponentiated)
     * @param b Exponent (the power to which the base is raised)
     * @param n Modulus (the divisor for modular reduction)
     * @return long long The result of (a^b) % n
     */
    long long compute(long long a, long long b, long long n);

    /**
     * @brief Prints the result and statistics to standard output.
     *
     * @param a The original base (for reference in the printout)
     * @param b The original exponent
     * @param n The original modulus
     */
    void printStats(long long a, long long b, long long n) const;

    /**
     * @brief Get the last computed result.
     * @return long long
     */
    long long getResult() const;

    /**
     * @brief Get how many multiplications were performed in the last computation.
     * @return long long
     */
    long long getMultiplicationCount() const;

private:
    long long result_;              ///< Stores the result of the last computation
    long long multiplicationCount_; ///< Tracks how many multiplications were performed
};

#endif // MONTGOMERY_EXP_H

#include "montgomery_exp.hpp"
#include <iostream>

MontgomeryExp::MontgomeryExp()
    : result_(0),
      multiplicationCount_(0)
{
    // Constructor body (if needed, otherwise it’s enough to have the initializer list)
}

long long MontgomeryExp::compute(long long a, long long b, long long n)
{
    // Reset statistics for a fresh computation
    result_ = 1;
    multiplicationCount_ = 0;

    // Standard iterative square-and-multiply
    a = a % n; // Reduce base 'a' modulo 'n'
    while (b > 0)
    {
        if (b & 1)
        {
            result_ = (result_ * a) % n;
            multiplicationCount_++; // Count the multiplication
        }
        a = (a * a) % n;
        multiplicationCount_++; // Count the squaring
        b >>= 1;
    }
    return result_;
}

void MontgomeryExp::printStats(long long a, long long b, long long n) const
{
    std::cout << "[MontgomeryExp::printStats]" << std::endl;
    std::cout << a << "^" << b << " mod " << n << " = " << result_ << std::endl;
    std::cout << "Number of multiplications performed: "
              << multiplicationCount_ << std::endl;
}

long long MontgomeryExp::getResult() const
{
    return result_;
}

long long MontgomeryExp::getMultiplicationCount() const
{
    return multiplicationCount_;
}

#include "montgomery_exp.hpp"
#include <iostream>

int main()
{
    // Create an object of MontgomeryExp
    MontgomeryExp montExp;

    // Example values
    long long a = 7;
    long long b = 560;
    long long n = 561;

    // Perform modular exponentiation
    montExp.compute(a, b, n);

    // Print result and stats
    montExp.printStats(a, b, n);

    return 0;
}

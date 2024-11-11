#include "gcd.hpp"
#include "mod_inverse.hpp"

int mod_inverse(int x, int y)
{
    int gcd_val, inverse, dummy;
    std::tie(gcd_val, inverse, dummy) = extended_gcd(x, y);
    if (gcd_val != 1)
        return -1; // Inverse doesn't exist
    else
    {
        // Ensure the inverse is positive
        inverse = (inverse % y + y) % y;
        return inverse;
    }
}

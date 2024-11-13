#include "gcd.hpp"

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

std::tuple<int, int, int> extended_gcd(int a, int b)
{
    if (a == 0)
        return std::make_tuple(b, 0, 1);
    else
    {
        int gcd_val, x1, y1;
        std::tie(gcd_val, x1, y1) = extended_gcd(b % a, a);
        int x = y1 - (b / a) * x1;
        int y = x1;
        return std::make_tuple(gcd_val, x, y);
    }
}

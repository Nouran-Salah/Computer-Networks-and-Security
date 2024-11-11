#include <iostream>
#include "gcd.hpp"
#include "mod_inverse.hpp"
#include "utilities.hpp"

using namespace std;

int main()
{
    int x, y;

    display_welcome_message();

    do
    {
        // Prompt user for input
        prompt_user_for_input(x, y);

        // Compute GCD
        int gcd_val = gcd(x, y);

        // Compute Modular Inverse if GCD is 1
        int inverse = (gcd_val == 1) ? mod_inverse(x, y) : -1;

        // Display results
        display_results(x, y, gcd_val, inverse);

    } while (ask_to_continue());

    cout << "Thank you for using the calculator. Goodbye!\n";
    return 0;
}

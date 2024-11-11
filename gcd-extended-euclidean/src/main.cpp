#include <iostream>
#include "gcd.hpp"
#include "mod_inverse.hpp"

using namespace std;

int main()
{
    int x, y;
    char choice;

    cout << "=== GCD and Modular Inverse Calculator ===\n\n";

    do
    {
        // Input Prompt
        cout << "This program computes the Greatest Common Divisor (GCD) of two positive integers x and y,\n";
        cout << "and finds the Modular Inverse of x modulo y, if it exists.\n\n";
        cout << "Please enter two positive integers separated by a space.\n";
        cout << "Example: To compute GCD and modular inverse of 3 modulo 7, enter: 3 7\n\n";
        cout << "Enter values for x and y: ";
        cin >> x >> y;

        if (x <= 0 || y <= 0)
        {
            cout << "\nError: Both x and y must be positive integers greater than zero.\n\n";
            continue;
        }

        // Compute GCD
        int gcd_val = gcd(x, y);
        cout << "\nResults:\n";
        cout << "GCD(" << x << ", " << y << ") = " << gcd_val << "\n";

        // Compute Modular Inverse if GCD is 1
        if (gcd_val == 1)
        {
            int inverse = mod_inverse(x, y);
            cout << "Modular Inverse of " << x << " modulo " << y << " is " << inverse << "\n";
        }
        else
        {
            cout << "Modular Inverse does not exist since GCD(" << x << ", " << y << ") != 1.\n";
        }

        // Ask user if they want to perform another calculation
        cout << "\nDo you want to perform another calculation? (y/n): ";
        cin >> choice;
        cout << "\n";

    } while (choice == 'y' || choice == 'Y');

    cout << "Thank you for using the calculator. Goodbye!\n";
    return 0;
}

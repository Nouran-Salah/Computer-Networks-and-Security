#include <iostream>
#include "utilities.hpp"

using namespace std;

void prompt_user_for_input(int &x, int &y)
{
    do
    {
        cout << "Please enter two positive integers separated by a space.\n";
        cout << "Example: To compute GCD and modular inverse of 3 modulo 7, enter: 3 7\n\n";
        cout << "Enter values for x and y: ";
        cin >> x >> y;

        if (x <= 0 || y <= 0)
        {
            cout << "\nError: Both x and y must be positive integers greater than zero.\n\n";
        }
    } while (x <= 0 || y <= 0);
}

void display_results(int x, int y, int gcd_val, int inverse)
{
    cout << "\nResults:\n";
    cout << "GCD(" << x << ", " << y << ") = " << gcd_val << "\n";

    if (inverse != -1)
    {
        cout << "Modular Inverse of " << x << " modulo " << y << " is " << inverse << "\n";
    }
    else
    {
        cout << "Modular Inverse does not exist since GCD(" << x << ", " << y << ") != 1.\n";
    }
}

bool ask_to_continue()
{
    char choice;
    cout << "\nDo you want to perform another calculation? (y/n): ";
    cin >> choice;
    cout << "\n";
    return (choice == 'y' || choice == 'Y');
}

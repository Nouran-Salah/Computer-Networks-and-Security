// utilities.cpp

#include <iostream>
#include "utilities.hpp"

using namespace std;

void display_welcome_message()
{
    cout << BLUE << BOLD;
    cout << "=============================================================\n";
    cout << "             GCD and Modular Inverse Calculator              \n";
    cout << "=============================================================\n\n";
    cout << RESET;
}

void prompt_user_for_input(int &x, int &y)
{
    cout << CYAN << BOLD << "\n==================== Input Required ====================\n"
         << RESET;
    do
    {
        cout << YELLOW;
        cout << "\nPlease enter two positive integers separated by a space.\n";
        cout << "Example: To compute GCD and modular inverse of 3 modulo 7, enter: 3 7\n\n";
        cout << "Enter values for x and y: " << RESET;
        cin >> x >> y;

        if (x <= 0 || y <= 0)
        {
            cout << RED << BOLD;
            cout << "\nError: Both x and y must be positive integers greater than zero.\n";
            cout << "------------------------------------------------------------------\n"
                 << RESET;
        }
    } while (x <= 0 || y <= 0);
}

void display_results(int x, int y, int gcd_val, int inverse)
{
    cout << GREEN << BOLD;
    cout << "\n==================== Calculation Results ====================\n"
         << RESET;
    cout << MAGENTA << "GCD(" << x << ", " << y << ") = " << gcd_val << "\n"
         << RESET;

    if (inverse != -1)
    {
        cout << MAGENTA;
        cout << "Modular Inverse of " << x << " modulo " << y << " is " << inverse << "\n"
             << RESET;
    }
    else
    {
        cout << RED << BOLD;
        cout << "Modular Inverse does not exist since GCD(" << x << ", " << y << ") != 1.\n"
             << RESET;
    }
    cout << GREEN << BOLD << "=============================================================\n"
         << RESET;
}

bool ask_to_continue()
{
    char choice;
    cout << CYAN << "\n------------------------------------------------------------------\n"
         << RESET;
    cout << YELLOW << "Do you want to perform another calculation? (y/n): " << RESET;
    cin >> choice;
    cout << CYAN << "------------------------------------------------------------------\n\n"
         << RESET;
    return (choice == 'y' || choice == 'Y');
}

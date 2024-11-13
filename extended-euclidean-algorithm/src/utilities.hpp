#ifndef UTILITIES_HPP
#define UTILITIES_HPP

/**
 * @brief Displays a welcome message for the GCD and Modular Inverse Calculator.
 *
 * This function prints a visually structured title screen with borders to welcome
 * the user to the program, providing a clear indication of the program's purpose.
 */
void display_welcome_message();

/**
 * @brief Prompts the user for two positive integers and stores them in the provided references.
 *
 * This function prompts the user to enter two positive integers and performs basic
 * validation. If the input is invalid, it displays an error message and re-prompts
 * the user until valid input is received.
 *
 * @param[out] x Reference to the first integer input by the user.
 * @param[out] y Reference to the second integer input by the user.
 */
void prompt_user_for_input(int &x, int &y);

/**
 * @brief Displays the results of the GCD and modular inverse calculations.
 *
 * This function prints the calculated GCD and, if applicable, the modular inverse of x modulo y.
 *
 * @param[in] x The first integer.
 * @param[in] y The second integer.
 * @param[in] gcd_val The calculated GCD of x and y.
 * @param[in] inverse The modular inverse of x modulo y, or -1 if it does not exist.
 */
void display_results(int x, int y, int gcd_val, int inverse);

/**
 * @brief Asks the user if they want to perform another calculation.
 *
 * This function prompts the user to enter 'y' to continue or 'n' to exit.
 *
 * @return true if the user wants to perform another calculation; false otherwise.
 */
bool ask_to_continue();

#endif // UTILITIES_HPP

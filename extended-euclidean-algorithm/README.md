# GCD and Modular Inverse Calculator

## Table of Contents

1. [Introduction](#introduction)
2. [Code Overview](#code-overview)
   - [GCD Function](#gcd-function)
   - [Extended GCD Function](#extended-gcd-function)
   - [Modular Inverse Function](#modular-inverse-function)
   - [Main Function](#main-function)
3. [Explanation of Swapping Arguments in Extended GCD](#explanation-of-swapping-arguments-in-extended-gcd)
   - [Euclidean Algorithm Basics](#euclidean-algorithm-basics)
   - [Extended Euclidean Algorithm](#extended-euclidean-algorithm)
   - [Recursive Call with Swapped Arguments](#recursive-call-with-swapped-arguments)
   - [Derivation of Coefficients](#derivation-of-coefficients)
   - [Algorithm Flow](#algorithm-flow)
   - [Example](#example)
4. [Conclusion](#conclusion)
5. [References](#references)

---

## Introduction

This document provides an in-depth explanation of the C++ program that calculates the Greatest Common Divisor (GCD) of two integers and finds the Modular Inverse of one integer modulo another, if it exists. It includes detailed reasoning behind the implementation of the Extended Euclidean Algorithm, specifically the swapping of arguments in the recursive function call.

---

## Code Overview

Below is the complete code of the program:

```cpp
#include <iostream>
#include <tuple>

using namespace std;

/**
 * Function to compute the Greatest Common Divisor (GCD) of two integers
 * using the Euclidean Algorithm.
 *
 * @param a First integer
 * @param b Second integer
 * @return The GCD of a and b
 */
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/**
 * Function to compute the Extended Euclidean Algorithm.
 * It returns a tuple containing the GCD of a and b,
 * and the coefficients x and y such that ax + by = gcd(a, b).
 *
 * @param a First integer
 * @param b Second integer
 * @return A tuple (gcd, x, y)
 */
tuple<int, int, int> extended_gcd(int a, int b) {
    if (a == 0)
        return make_tuple(b, 0, 1);
    else {
        int gcd_val, x1, y1;
        tie(gcd_val, x1, y1) = extended_gcd(b % a, a);
        int x = y1 - (b / a) * x1;
        int y = x1;
        return make_tuple(gcd_val, x, y);
    }
}

/**
 * Function to find the Modular Inverse of x modulo y.
 * It returns the inverse if it exists, otherwise returns -1.
 *
 * @param x The integer whose inverse is to be found
 * @param y The modulus
 * @return The modular inverse of x modulo y, or -1 if it doesn't exist
 */
int mod_inverse(int x, int y) {
    int gcd_val, inverse, dummy;
    tie(gcd_val, inverse, dummy) = extended_gcd(x, y);
    if (gcd_val != 1)
        return -1; // Inverse doesn't exist
    else {
        // Ensure the inverse is positive
        inverse = (inverse % y + y) % y;
        return inverse;
    }
}

/**
 * Main function to interact with the user.
 */
int main() {
    int x, y;
    char choice;

    cout << "=== GCD and Modular Inverse Calculator ===\n\n";

    do {
        // Enhanced Input Prompt
        cout << "This program computes the Greatest Common Divisor (GCD) of two positive integers x and y,\n";
        cout << "and finds the Modular Inverse of x modulo y, if it exists.\n\n";
        cout << "Please enter two positive integers separated by a space.\n";
        cout << "Example: To compute GCD and modular inverse of 3 modulo 7, enter: 3 7\n\n";
        cout << "Enter values for x and y: ";
        cin >> x >> y;

        if (x <= 0 || y <= 0) {
            cout << "\nError: Both x and y must be positive integers greater than zero.\n\n";
            continue;
        }

        // Compute GCD
        int gcd_val = gcd(x, y);
        cout << "\nResults:\n";
        cout << "GCD(" << x << ", " << y << ") = " << gcd_val << "\n";

        // Compute Modular Inverse if GCD is 1
        if (gcd_val == 1) {
            int inverse = mod_inverse(x, y);
            cout << "Modular Inverse of " << x << " modulo " << y << " is " << inverse << "\n";
        } else {
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
```

### GCD Function

The `gcd` function calculates the GCD of two integers using the standard Euclidean Algorithm.

```cpp
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
```

### Extended GCD Function

The `extended_gcd` function computes the GCD of two integers and finds integers `x` and `y` satisfying Bézout's identity:

\[
ax + by = \gcd(a, b)
\]

```cpp
tuple<int, int, int> extended_gcd(int a, int b) {
    if (a == 0)
        return make_tuple(b, 0, 1);
    else {
        int gcd_val, x1, y1;
        tie(gcd_val, x1, y1) = extended_gcd(b % a, a);
        int x = y1 - (b / a) * x1;
        int y = x1;
        return make_tuple(gcd_val, x, y);
    }
}
```

### Modular Inverse Function

The `mod_inverse` function finds the modular inverse of `x` modulo `y` if it exists.

```cpp
int mod_inverse(int x, int y) {
    int gcd_val, inverse, dummy;
    tie(gcd_val, inverse, dummy) = extended_gcd(x, y);
    if (gcd_val != 1)
        return -1; // Inverse doesn't exist
    else {
        // Ensure the inverse is positive
        inverse = (inverse % y + y) % y;
        return inverse;
    }
}
```

### Main Function

The `main` function interacts with the user, prompting for input and displaying the results.

---

## Explanation of Swapping Arguments in Extended GCD

### Euclidean Algorithm Basics

The **Euclidean Algorithm** computes the GCD of two integers \( a \) and \( b \) through a series of division steps:

\[
\gcd(a, b) = \gcd(b \mod a, a)
\]

This process repeats until \( a = 0 \), at which point the GCD is \( b \).

### Extended Euclidean Algorithm

The **Extended Euclidean Algorithm** not only computes the GCD but also finds integers \( x \) and \( y \) such that:

\[
ax + by = \gcd(a, b)
\]

This equation is known as **Bézout's Identity**.

### Recursive Call with Swapped Arguments

In the recursive implementation, the function calls itself with swapped arguments:

```cpp
tie(gcd_val, x1, y1) = extended_gcd(b % a, a);
```

#### Reason for Swapping Arguments

1. **Alignment with the Euclidean Algorithm:**

   - The Euclidean Algorithm reduces the problem size by replacing \( (a, b) \) with \( (b \mod a, a) \).
   - Swapping arguments ensures that the first parameter decreases with each recursive call, moving towards the base case \( a = 0 \).

2. **Correct Coefficient Calculation:**

   - Swapping maintains the correct relationships between coefficients \( x \) and \( y \) when backtracking through recursion.
   - It ensures the formulas for updating \( x \) and \( y \) are valid.

### Derivation of Coefficients

#### From the Recursive Call

Assume we have:

\[
\text{extended\_gcd}(b \mod a, a) \rightarrow (\gcd, x_1, y_1)
\]

Which satisfies:

\[
(b \mod a) x_1 + a y_1 = \gcd(a, b)
\]

#### Express \( b \mod a \) in Terms of \( a \) and \( b \)

Since:

\[
b \mod a = b - q a \quad \text{where} \quad q = \left\lfloor \frac{b}{a} \right\rfloor
\]

#### Substitute Back into the Equation

\[
(b - q a) x_1 + a y_1 = \gcd(a, b)
\]

#### Simplify the Equation

\[
b x_1 - a q x_1 + a y_1 = \gcd(a, b)
\]

\[
b x_1 + a (y_1 - q x_1) = \gcd(a, b)
\]

#### Update Coefficients

Set:

- \( x = y_1 - q x_1 \)
- \( y = x_1 \)

This maintains Bézout's identity:

\[
a x + b y = \gcd(a, b)
\]

### Algorithm Flow

1. **Recursive Calls:**

   - Each call reduces the value of \( a \) since \( b \mod a < a \).
   - The recursion proceeds until \( a = 0 \).

2. **Base Case:**

   - When \( a = 0 \), return \( (\gcd, x, y) = (b, 0, 1) \).

3. **Backtracking:**

   - On returning from recursion, update \( x \) and \( y \) using the derived formulas.
   - This ensures that at each level, \( a x + b y = \gcd(a, b) \) holds.

### Example

Let's illustrate with \( a = 30 \) and \( b = 50 \).

#### Recursive Calls:

1. **First Call:**

   \[
   \text{extended\_gcd}(30, 50)
   \]

2. **Second Call:**

   \[
   \text{extended\_gcd}(50 \mod 30, 30) = \text{extended\_gcd}(20, 30)
   \]

3. **Third Call:**

   \[
   \text{extended\_gcd}(30 \mod 20, 20) = \text{extended\_gcd}(10, 20)
   \]

4. **Fourth Call (Base Case):**

   \[
   \text{extended\_gcd}(20 \mod 10, 10) = \text{extended\_gcd}(0, 10)
   \]

   - Returns \( (\gcd, x, y) = (10, 0, 1) \).

#### Backtracking:

1. **From \( \text{extended\_gcd}(10, 20) \):**

   - \( b = 20 \), \( a = 10 \), \( q = \left\lfloor \frac{20}{10} \right\rfloor = 2 \).
   - \( x = y_1 - q x_1 = 1 - 2 \times 0 = 1 \).
   - \( y = x_1 = 0 \).
   - Equation: \( 10 \times 1 + 20 \times 0 = 10 \).

2. **From \( \text{extended\_gcd}(20, 30) \):**

   - \( b = 30 \), \( a = 20 \), \( q = \left\lfloor \frac{30}{20} \right\rfloor = 1 \).
   - \( x = y_1 - q x_1 = 0 - 1 \times 1 = -1 \).
   - \( y = x_1 = 1 \).
   - Equation: \( 20 \times -1 + 30 \times 1 = 10 \).

3. **From \( \text{extended\_gcd}(30, 50) \):**

   - \( b = 50 \), \( a = 30 \), \( q = \left\lfloor \frac{50}{30} \right\rfloor = 1 \).
   - \( x = y_1 - q x_1 = 1 - 1 \times -1 = 2 \).
   - \( y = x_1 = -1 \).
   - Equation: \( 30 \times 2 + 50 \times -1 = 10 \).

#### Verification:

- Final coefficients: \( x = 2 \), \( y = -1 \).
- Bézout's identity holds: \( 30 \times 2 + 50 \times (-1) = 10 \).

---

## Conclusion

Swapping the arguments in the recursive call of the `extended_gcd` function is essential for:

- **Ensuring Correct Progression:** The algorithm reduces the first argument \( a \) towards zero, reaching the base case efficiently.
- **Maintaining Valid Coefficients:** The method of updating \( x \) and \( y \) relies on the arguments being in this specific order to satisfy Bézout's identity.

Understanding this mechanism is crucial for implementing the Extended Euclidean Algorithm correctly and for computing modular inverses, which are fundamental in number theory and cryptography.

---

## References

- **"Introduction to Algorithms"** by Cormen, Leiserson, Rivest, and Stein.
- **"Elementary Number Theory and Its Applications"** by Kenneth H. Rosen.
- **Khan Academy:** [The Extended Euclidean Algorithm](https://www.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/the-extended-euclidean-algorithm)
- **Wikipedia:** [Extended Euclidean Algorithm](https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm)
- **GeeksforGeeks:** [Euclidean Algorithms (Basic and Extended)](https://www.geeksforgeeks.org/euclidean-algorithms-basic-and-extended/)

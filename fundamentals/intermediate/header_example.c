/**
 * header_example.c - Demonstrates Header File Usage
 * 
 * This program demonstrates:
 * - Including custom header files
 * - Using functions from separate compilation units
 * - Multi-file program structure
 * - Why headers are essential
 */

#include <stdio.h>
#include "math_utils.h"  // Include our custom header

#ifdef _WIN32
#include <windows.h>
#endif

// Function declarations for this file
void demonstrate_arithmetic(void);
void demonstrate_prime_numbers(void);
void demonstrate_sequences(void);
void demonstrate_geometry(void);
void demonstrate_utilities(void);

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IOFBF, 1000);
#endif

    printf("========================================\n");
    printf("     HEADER FILES DEMONSTRATION        \n");
    printf("========================================\n\n");

    printf("Using functions from math_utils.h\n");
    printf("This demonstrates multi-file programs!\n\n");

    demonstrate_arithmetic();
    demonstrate_prime_numbers();
    demonstrate_sequences();
    demonstrate_geometry();
    demonstrate_utilities();

    printf("========================================\n");
    printf("     ALL DEMONSTRATIONS COMPLETED      \n");
    printf("========================================\n");

    return 0;
}

/**
 * Demonstrate arithmetic functions
 */
void demonstrate_arithmetic(void) {
    printf("========================================\n");
    printf("1. ARITHMETIC OPERATIONS\n");
    printf("========================================\n\n");

    int a = 15, b = 4;

    printf("Numbers: a = %d, b = %d\n\n", a, b);
    printf("Basic Operations:\n");
    printf("  add(a, b) = %d\n", add(a, b));
    printf("  subtract(a, b) = %d\n", subtract(a, b));
    printf("  multiply(a, b) = %d\n", multiply(a, b));
    printf("  divide(a, b) = %.2f\n\n", divide(a, b));

    printf("Power Operations:\n");
    printf("  square(5.0) = %.2f\n", square(5.0));
    printf("  cube(3.0) = %.2f\n", cube(3.0));
    printf("  power(2.0, 10) = %.0f\n\n", power(2.0, 10));

    printf("Inline Functions:\n");
    printf("  is_even(10) = %s\n", is_even(10) ? "true" : "false");
    printf("  is_odd(10) = %s\n", is_odd(10) ? "true" : "false");
    printf("  square_inline(7.0) = %.2f\n\n", square_inline(7.0));

    printf("Macros:\n");
    printf("  MAX(a, b) = %d\n", MAX(a, b));
    printf("  MIN(a, b) = %d\n", MIN(a, b));
    printf("  ABS(-25) = %d\n\n", ABS(-25));
}

/**
 * Demonstrate prime number functions
 */
void demonstrate_prime_numbers(void) {
    printf("========================================\n");
    printf("2. PRIME NUMBERS\n");
    printf("========================================\n\n");

    printf("Testing Prime Numbers:\n");
    int test_numbers[] = {2, 3, 4, 17, 20, 29, 100};
    for (int i = 0; i < 7; i++) {
        int n = test_numbers[i];
        printf("  is_prime(%d) = %s\n", n, is_prime(n) ? "Yes ✓" : "No ✗");
    }

    printf("\nNext Prime After:\n");
    printf("  next_prime(10) = %d\n", next_prime(10));
    printf("  next_prime(50) = %d\n", next_prime(50));
    printf("  next_prime(100) = %d\n\n", next_prime(100));
}

/**
 * Demonstrate sequence functions
 */
void demonstrate_sequences(void) {
    printf("========================================\n");
    printf("3. SEQUENCES\n");
    printf("========================================\n\n");

    printf("Factorial Sequence:\n");
    for (int i = 0; i <= 10; i++) {
        printf("  %2d! = %d\n", i, factorial(i));
    }

    printf("\nFibonacci Sequence:\n");
    for (int i = 0; i <= 15; i++) {
        printf("  fib(%2d) = %d\n", i, fibonacci(i));
    }
    printf("\n");
}

/**
 * Demonstrate geometric calculations
 */
void demonstrate_geometry(void) {
    printf("========================================\n");
    printf("4. GEOMETRY\n");
    printf("========================================\n\n");

    double radius = 5.0;
    printf("Circle (radius = %.1f):\n", radius);
    printf("  Area = %.2f\n", circle_area(radius));
    printf("  Circumference = %.2f\n\n", circle_circumference(radius));

    Point p1 = {0.0, 0.0};
    Point p2 = {3.0, 4.0};
    printf("Points:\n");
    printf("  p1 = (%.1f, %.1f)\n", p1.x, p1.y);
    printf("  p2 = (%.1f, %.1f)\n", p2.x, p2.y);
    printf("  Distance = %.2f\n\n", distance_between_points(p1, p2));

    Circle c = {
        .center = {10.0, 10.0},
        .radius = 7.5
    };
    printf("Circle Structure:\n");
    printf("  Center: (%.1f, %.1f)\n", c.center.x, c.center.y);
    printf("  Radius: %.1f\n", c.radius);
    printf("  Area: %.2f\n\n", circle_area(c.radius));
}

/**
 * Demonstrate utility functions
 */
void demonstrate_utilities(void) {
    printf("========================================\n");
    printf("5. UTILITY FUNCTIONS\n");
    printf("========================================\n\n");

    int a = 48, b = 18;
    printf("Numbers: a = %d, b = %d\n", a, b);
    printf("  GCD(a, b) = %d\n", gcd(a, b));
    printf("  LCM(a, b) = %d\n\n", lcm(a, b));

    int x = 100, y = 200;
    printf("Swap Function:\n");
    printf("  Before: x = %d, y = %d\n", x, y);
    swap_int(&x, &y);
    printf("  After:  x = %d, y = %d\n\n", x, y);

    printf("Constants from Header:\n");
    printf("  PI = %.10f\n", PI);
    printf("  E = %.10f\n\n", E);
}

/**
 * math_utils.h - Mathematical Utility Functions
 * 
 * Demonstrates proper header file structure:
 * - Include guards to prevent multiple inclusion
 * - Function declarations (prototypes)
 * - Macro definitions
 * - Type definitions
 * - Documentation
 * 
 * This is a typical C header file that would be included
 * in multiple source files.
 */

#ifndef MATH_UTILS_H  // Include guard start
#define MATH_UTILS_H

// Standard library includes
#include <stdbool.h>

// ========================================
// CONSTANTS
// ========================================

#define PI 3.14159265359
#define E 2.71828182846

// ========================================
// MACROS
// ========================================

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(x) ((x) < 0 ? -(x) : (x))

// ========================================
// TYPE DEFINITIONS
// ========================================

// Structure to represent a 2D point
typedef struct {
    double x;
    double y;
} Point;

// Structure to represent a circle
typedef struct {
    Point center;
    double radius;
} Circle;

// ========================================
// FUNCTION DECLARATIONS
// ========================================

/**
 * Basic arithmetic operations
 */
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
double divide(int a, int b);

/**
 * Power and square operations
 */
double power(double base, int exponent);
double square(double x);
double cube(double x);

/**
 * Prime number operations
 */
bool is_prime(int n);
int next_prime(int n);

/**
 * Factorial and Fibonacci
 */
int factorial(int n);
int fibonacci(int n);

/**
 * Geometric calculations
 */
double circle_area(double radius);
double circle_circumference(double radius);
double distance_between_points(Point p1, Point p2);

/**
 * Utility functions
 */
int gcd(int a, int b);  // Greatest common divisor
int lcm(int a, int b);  // Least common multiple
void swap_int(int* a, int* b);

// ========================================
// INLINE FUNCTIONS (C99+)
// ========================================

/**
 * Inline functions for simple operations
 * These are small enough to be inlined by the compiler
 */
static inline int is_even(int n) {
    return (n % 2) == 0;
}

static inline int is_odd(int n) {
    return (n % 2) != 0;
}

static inline double square_inline(double x) {
    return x * x;
}

#endif  // MATH_UTILS_H - Include guard end

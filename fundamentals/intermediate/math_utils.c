/**
 * math_utils.c - Implementation of Mathematical Utilities
 * 
 * This file implements the functions declared in math_utils.h
 * Demonstrates:
 * - Separation of interface (header) and implementation
 * - How to implement header functions
 * - Proper documentation
 */

#include "math_utils.h"
#include <math.h>

// ========================================
// BASIC ARITHMETIC
// ========================================

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

double divide(int a, int b) {
    if (b == 0) {
        return 0.0;  // Handle division by zero
    }
    return (double)a / b;
}

// ========================================
// POWER OPERATIONS
// ========================================

double power(double base, int exponent) {
    if (exponent == 0) return 1.0;
    if (exponent < 0) return 1.0 / power(base, -exponent);
    
    double result = 1.0;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

double square(double x) {
    return x * x;
}

double cube(double x) {
    return x * x * x;
}

// ========================================
// PRIME NUMBER OPERATIONS
// ========================================

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int next_prime(int n) {
    if (n < 2) return 2;
    
    int candidate = n + 1;
    while (!is_prime(candidate)) {
        candidate++;
    }
    return candidate;
}

// ========================================
// FACTORIAL AND FIBONACCI
// ========================================

int factorial(int n) {
    if (n < 0) return 0;  // Undefined for negative
    if (n == 0 || n == 1) return 1;
    
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    
    int prev = 0, curr = 1;
    for (int i = 2; i <= n; i++) {
        int next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

// ========================================
// GEOMETRIC CALCULATIONS
// ========================================

double circle_area(double radius) {
    return PI * radius * radius;
}

double circle_circumference(double radius) {
    return 2 * PI * radius;
}

double distance_between_points(Point p1, Point p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

// ========================================
// UTILITY FUNCTIONS
// ========================================

int gcd(int a, int b) {
    // Euclidean algorithm
    a = ABS(a);
    b = ABS(b);
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return ABS(a * b) / gcd(a, b);
}

void swap_int(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

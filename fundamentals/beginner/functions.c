/**
 * Functions in C
 * 
 * This program demonstrates:
 * - Function declaration and definition
 * - Function parameters and return values
 * - Pass by value
 * - Scope of variables
 * - Recursion
 * - Function prototypes
 */

#include <stdio.h>

// Function prototypes (declarations)
void greet(void);
void greet_person(char *name);
int add(int a, int b);
int max(int a, int b);
double calculate_area(double radius);
void swap_wrong(int a, int b);
void swap_correct(int *a, int *b);
int factorial(int n);
int fibonacci(int n);
void print_array(int arr[], int size);

int main(void) {
    printf("=== Functions in C ===\n\n");
    
    // PART 1: Simple function without parameters
    printf("1. SIMPLE FUNCTION\n");
    greet();
    printf("\n");
    
    // PART 2: Function with parameters
    printf("2. FUNCTION WITH PARAMETERS\n");
    greet_person("Alice");
    greet_person("Bob");
    printf("\n");
    
    // PART 3: Function with return value
    printf("3. FUNCTION WITH RETURN VALUE\n");
    int sum = add(5, 3);
    printf("  5 + 3 = %d\n", sum);
    printf("  10 + 20 = %d\n", add(10, 20));
    printf("\n");
    
    // PART 4: Using return value in expressions
    printf("4. RETURN VALUE IN EXPRESSIONS\n");
    int a = 15, b = 20;
    printf("  a = %d, b = %d\n", a, b);
    printf("  max(a, b) = %d\n", max(a, b));
    printf("  max(a, b) + 10 = %d\n", max(a, b) + 10);
    printf("\n");
    
    // PART 5: Function with floating-point return
    printf("5. FLOATING-POINT RETURN\n");
    double radius = 5.0;
    double area = calculate_area(radius);
    printf("  Circle with radius %.1f has area %.2f\n", radius, area);
    printf("\n");
    
    // PART 6: Pass by value (doesn't modify original)
    printf("6. PASS BY VALUE\n");
    int x = 10, y = 20;
    printf("  Before swap_wrong: x = %d, y = %d\n", x, y);
    swap_wrong(x, y);
    printf("  After swap_wrong:  x = %d, y = %d (unchanged!)\n", x, y);
    printf("\n");
    
    // PART 7: Pass by reference (modifies original)
    printf("7. PASS BY REFERENCE\n");
    printf("  Before swap_correct: x = %d, y = %d\n", x, y);
    swap_correct(&x, &y);
    printf("  After swap_correct:  x = %d, y = %d (swapped!)\n", x, y);
    printf("\n");
    
    // PART 8: Recursive functions
    printf("8. RECURSIVE FUNCTIONS\n");
    int num = 5;
    printf("  Factorial of %d = %d\n", num, factorial(num));
    
    printf("  Fibonacci sequence (first 10): ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n\n");
    
    // PART 9: Functions with arrays
    printf("9. FUNCTIONS WITH ARRAYS\n");
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    printf("  Array: ");
    print_array(numbers, size);
    printf("\n");
    
    // PART 10: Multiple function calls
    printf("10. NESTED FUNCTION CALLS\n");
    int result = add(max(5, 10), max(15, 20));
    printf("  add(max(5, 10), max(15, 20)) = %d\n", result);
    printf("\n");
    
    return 0;
}

// Function definitions

// Simple function with no parameters or return value
void greet(void) {
    printf("  Hello, World!\n");
}

// Function with string parameter
void greet_person(char *name) {
    printf("  Hello, %s!\n", name);
}

// Function that returns sum of two integers
int add(int a, int b) {
    return a + b;
}

// Function that returns maximum of two integers
int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
    // Alternative: return (a > b) ? a : b;
}

// Function that calculates circle area
double calculate_area(double radius) {
    const double PI = 3.14159;
    return PI * radius * radius;
}

// Wrong way to swap (pass by value) - doesn't work!
void swap_wrong(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    // Changes are local to this function only
}

// Correct way to swap (pass by reference) - works!
void swap_correct(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Recursive function to calculate factorial
int factorial(int n) {
    // Base case
    if (n <= 1) {
        return 1;
    }
    // Recursive case
    return n * factorial(n - 1);
}

// Recursive function to calculate Fibonacci number
int fibonacci(int n) {
    // Base cases
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    // Recursive case
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Function that accepts an array
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}

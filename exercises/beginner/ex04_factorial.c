/**
 * Exercise 4: Factorial Calculator
 * 
 * Description:
 * Calculate the factorial of a number (n!)
 * 
 * Formula: n! = n × (n-1) × (n-2) × ... × 2 × 1
 * Example: 5! = 5 × 4 × 3 × 2 × 1 = 120
 */

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Iterative factorial
long long factorial_iterative(int n) {
    if (n < 0) return -1;  // Error indicator
    if (n == 0 || n == 1) return 1;

    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Recursive factorial
long long factorial_recursive(int n) {
    if (n < 0) return -1;
    if (n == 0 || n == 1) return 1;
    return n * factorial_recursive(n - 1);
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IOFBF, 1000);
#endif

    int number;
    long long result;

    printf("========================================\n");
    printf("      FACTORIAL CALCULATOR             \n");
    printf("========================================\n\n");

    printf("Enter a number (0-20): ");
    scanf("%d", &number);

    printf("\n");

    if (number < 0) {
        printf("Factorial is not defined for negative numbers.\n");
    } else if (number > 20) {
        printf("Number too large (overflow risk). Please enter 0-20.\n");
    } else {
        result = factorial_iterative(number);
        printf("%d! = %lld\n\n", number, result);

        // Show calculation steps for small numbers
        if (number <= 10 && number > 0) {
            printf("Calculation: %d", number);
            for (int i = number - 1; i >= 1; i--) {
                printf(" × %d", i);
            }
            printf(" = %lld\n", result);
        }

        // Verify with recursive version
        long long recursive_result = factorial_recursive(number);
        printf("\nVerification (recursive): %d! = %lld ✓\n", 
               number, recursive_result);
    }

    return 0;
}

/**
 * Exercise 5: Fibonacci Sequence
 * 
 * Description:
 * Generate the Fibonacci sequence up to n terms.
 * 
 * Sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...
 * Each term is the sum of the two preceding terms.
 */

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

void print_fibonacci(int n) {
    if (n <= 0) {
        printf("Please enter a positive number.\n");
        return;
    }

    long long prev = 0, curr = 1, next;

    printf("Fibonacci sequence (%d terms):\n", n);
    
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            printf("%lld", prev);
        } else if (i == 1) {
            printf(", %lld", curr);
        } else {
            next = prev + curr;
            printf(", %lld", next);
            prev = curr;
            curr = next;
        }

        // Line break every 10 numbers for readability
        if ((i + 1) % 10 == 0 && i < n - 1) {
            printf(",\n");
        }
    }
    printf("\n");
}

// Recursive Fibonacci (for single term)
long long fib_recursive(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IOFBF, 1000);
#endif

    int terms;

    printf("========================================\n");
    printf("      FIBONACCI SEQUENCE               \n");
    printf("========================================\n\n");

    printf("How many terms to generate? ");
    scanf("%d", &terms);

    printf("\n");

    if (terms <= 0) {
        printf("Please enter a positive number.\n");
    } else if (terms > 50) {
        printf("Limited to 50 terms to prevent overflow.\n");
        terms = 50;
        print_fibonacci(terms);
    } else {
        print_fibonacci(terms);
        
        // Show a specific term calculation
        if (terms >= 10) {
            int specific = 10;
            printf("\nSpecific term: fib(%d) = %lld\n", 
                   specific, fib_recursive(specific));
        }
    }

    return 0;
}

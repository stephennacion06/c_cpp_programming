/**
 * Exercise 3: Prime Number Checker
 * 
 * Description:
 * Determine if a number is prime (only divisible by 1 and itself).
 * 
 * Requirements:
 * - Read a number from user
 * - Check if it's prime
 * - Display appropriate message
 */

#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#endif

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    // Check divisors up to √n
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IOFBF, 1000);
#endif

    int number;

    printf("========================================\n");
    printf("      PRIME NUMBER CHECKER             \n");
    printf("========================================\n\n");

    printf("Enter a positive integer: ");
    scanf("%d", &number);

    printf("\n");

    if (number < 0) {
        printf("Please enter a positive number.\n");
    } else if (is_prime(number)) {
        printf("%d is a PRIME number! ✓\n", number);
        printf("It is only divisible by 1 and %d.\n", number);
    } else {
        printf("%d is NOT a prime number. ✗\n", number);
        
        // Show first factor found
        if (number > 1) {
            for (int i = 2; i <= number / 2; i++) {
                if (number % i == 0) {
                    printf("It is divisible by %d (and others).\n", i);
                    break;
                }
            }
        }
    }

    return 0;
}

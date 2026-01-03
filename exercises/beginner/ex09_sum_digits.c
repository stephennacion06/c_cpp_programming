/**
 * Exercise 9: Sum of Digits
 * 
 * Description:
 * Calculate the sum of all digits in a number.
 * 
 * Example: 
 * - Input: 12345
 * - Output: 1 + 2 + 3 + 4 + 5 = 15
 */

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

int sum_of_digits(int n) {
    int sum = 0;
    n = (n < 0) ? -n : n;  // Handle negative numbers

    while (n > 0) {
        sum += n % 10;  // Add last digit
        n /= 10;        // Remove last digit
    }

    return sum;
}

void show_calculation(int n) {
    int original = n;
    n = (n < 0) ? -n : n;
    
    printf("Calculation: ");
    int first = 1;
    while (n > 0) {
        if (!first) printf(" + ");
        printf("%d", n % 10);
        n /= 10;
        first = 0;
    }
    printf(" = %d\n", sum_of_digits(original));
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IOFBF, 1000);
#endif

    int number;

    printf("========================================\n");
    printf("        SUM OF DIGITS                  \n");
    printf("========================================\n\n");

    printf("Enter a number: ");
    scanf("%d", &number);

    printf("\n");

    if (number < 0) {
        printf("Input: %d (using absolute value)\n", number);
        number = -number;
    } else {
        printf("Input: %d\n", number);
    }

    printf("\n");
    show_calculation(number);

    printf("\nSum of digits: %d\n", sum_of_digits(number));

    return 0;
}

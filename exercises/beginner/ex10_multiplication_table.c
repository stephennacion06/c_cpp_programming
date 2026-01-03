/**
 * Exercise 10: Multiplication Table
 * 
 * Description:
 * Generate and display a multiplication table for a given number.
 * 
 * Requirements:
 * - Ask user for a number
 * - Display multiplication table (1-10)
 * - Format output nicely
 */

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

void print_multiplication_table(int number, int limit) {
    printf("Multiplication Table for %d:\n", number);
    printf("─────────────────────────────\n");

    for (int i = 1; i <= limit; i++) {
        printf("%2d × %2d = %4d\n", number, i, number * i);
    }
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IOFBF, 1000);
#endif

    int number;
    int limit = 10;

    printf("========================================\n");
    printf("      MULTIPLICATION TABLE             \n");
    printf("========================================\n\n");

    printf("Enter a number: ");
    scanf("%d", &number);

    printf("\n");

    print_multiplication_table(number, limit);

    printf("\n✓ Table generated successfully!\n");

    return 0;
}

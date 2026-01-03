/**
 * Exercise 1: Simple Calculator
 * 
 * Description:
 * Create a calculator that performs basic arithmetic operations.
 * 
 * Requirements:
 * - Ask user for two numbers
 * - Ask for operation (+, -, *, /)
 * - Display the result
 * - Handle division by zero
 */

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IOFBF, 1000);
#endif

    double num1, num2, result;
    char operation;

    printf("========================================\n");
    printf("       SIMPLE CALCULATOR               \n");
    printf("========================================\n\n");

    // Get first number
    printf("Enter first number: ");
    scanf("%lf", &num1);

    // Get second number
    printf("Enter second number: ");
    scanf("%lf", &num2);

    // Get operation
    printf("Enter operation (+, -, *, /): ");
    scanf(" %c", &operation);  // Space before %c to consume newline

    printf("\n");

    // Perform calculation
    switch (operation) {
        case '+':
            result = num1 + num2;
            printf("Result: %.2f + %.2f = %.2f\n", num1, num2, result);
            break;

        case '-':
            result = num1 - num2;
            printf("Result: %.2f - %.2f = %.2f\n", num1, num2, result);
            break;

        case '*':
            result = num1 * num2;
            printf("Result: %.2f * %.2f = %.2f\n", num1, num2, result);
            break;

        case '/':
            if (num2 == 0) {
                printf("Error: Division by zero!\n");
            } else {
                result = num1 / num2;
                printf("Result: %.2f / %.2f = %.2f\n", num1, num2, result);
            }
            break;

        default:
            printf("Error: Invalid operation '%c'\n", operation);
            printf("Please use +, -, *, or /\n");
            break;
    }

    return 0;
}

/**
 * Exercise 2: Temperature Converter
 * 
 * Description:
 * Convert temperature between Celsius and Fahrenheit.
 * 
 * Formulas:
 * - Celsius to Fahrenheit: F = (C × 9/5) + 32
 * - Fahrenheit to Celsius: C = (F - 32) × 5/9
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

    int choice;
    double temperature, converted;

    printf("========================================\n");
    printf("     TEMPERATURE CONVERTER             \n");
    printf("========================================\n\n");

    printf("Choose conversion:\n");
    printf("1. Celsius to Fahrenheit\n");
    printf("2. Fahrenheit to Celsius\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);

    printf("Enter temperature: ");
    scanf("%lf", &temperature);

    printf("\n");

    if (choice == 1) {
        // Celsius to Fahrenheit
        converted = (temperature * 9.0 / 5.0) + 32.0;
        printf("%.2f°C = %.2f°F\n", temperature, converted);
    } else if (choice == 2) {
        // Fahrenheit to Celsius
        converted = (temperature - 32.0) * 5.0 / 9.0;
        printf("%.2f°F = %.2f°C\n", temperature, converted);
    } else {
        printf("Error: Invalid choice!\n");
        printf("Please enter 1 or 2.\n");
    }

    return 0;
}

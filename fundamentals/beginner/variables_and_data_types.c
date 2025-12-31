/**
 * Variables and Data Types in C
 * 
 * This program demonstrates the fundamental data types in C:
 * - int: Integer numbers
 * - float: Floating-point numbers (single precision)
 * - double: Floating-point numbers (double precision)
 * - char: Single characters
 */

#include <stdio.h>

int main(void) {
    printf("=== Variables and Data Types Demo ===\n\n");
    
    // Integer types
    int age = 25;
    short small_number = 100;
    long large_number = 1000000L;
    
    printf("Integer Types:\n");
    printf("  int age = %d\n", age);
    printf("  short small_number = %hd\n", small_number);
    printf("  long large_number = %ld\n", large_number);
    printf("  Size of int: %zu bytes\n", sizeof(int));
    printf("\n");
    
    // Floating-point types
    float pi_float = 3.14159f;
    double pi_double = 3.14159265358979;
    
    printf("Floating-Point Types:\n");
    printf("  float pi = %.5f\n", pi_float);
    printf("  double pi = %.15lf\n", pi_double);
    printf("  Size of float: %zu bytes\n", sizeof(float));
    printf("  Size of double: %zu bytes\n", sizeof(double));
    printf("\n");
    
    // Character type
    char grade = 'A';
    char initial = 'J';
    
    printf("Character Type:\n");
    printf("  char grade = '%c'\n", grade);
    printf("  char initial = '%c'\n", initial);
    printf("  Size of char: %zu byte\n", sizeof(char));
    printf("  ASCII value of '%c': %d\n", grade, grade);
    printf("\n");
    
    // Unsigned types (only positive values)
    unsigned int positive_only = 4294967295U;
    
    printf("Unsigned Types:\n");
    printf("  unsigned int positive_only = %u\n", positive_only);
    printf("\n");
    
    // Constants
    const int DAYS_IN_WEEK = 7;
    const double SPEED_OF_LIGHT = 299792458.0; // m/s
    
    printf("Constants:\n");
    printf("  DAYS_IN_WEEK = %d\n", DAYS_IN_WEEK);
    printf("  SPEED_OF_LIGHT = %.0lf m/s\n", SPEED_OF_LIGHT);
    printf("\n");
    
    // Type casting
    int integer = 10;
    double result = (double)integer / 3;
    
    printf("Type Casting:\n");
    printf("  integer / 3 = %d (integer division)\n", integer / 3);
    printf("  (double)integer / 3 = %.5lf (float division)\n", result);
    printf("\n");
    
    return 0;
}

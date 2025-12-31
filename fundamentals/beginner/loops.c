/**
 * Loops in C
 * 
 * This program demonstrates all loop types in C:
 * - for loop
 * - while loop
 * - do-while loop
 * - Nested loops
 * - Loop control statements (break, continue)
 */

#include <stdio.h>

int main(void) {
    printf("=== Loops in C ===\n\n");
    
    // PART 1: for loop
    printf("1. FOR LOOP\n");
    printf("  Counting 1 to 5: ");
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n\n");
    
    // PART 2: for loop with different increments
    printf("2. FOR LOOP - DIFFERENT INCREMENTS\n");
    printf("  Even numbers 0 to 10: ");
    for (int i = 0; i <= 10; i += 2) {
        printf("%d ", i);
    }
    printf("\n");
    
    printf("  Counting down 5 to 1: ");
    for (int i = 5; i >= 1; i--) {
        printf("%d ", i);
    }
    printf("\n\n");
    
    // PART 3: while loop
    printf("3. WHILE LOOP\n");
    printf("  Counting 1 to 5: ");
    int count = 1;
    while (count <= 5) {
        printf("%d ", count);
        count++;
    }
    printf("\n\n");
    
    // PART 4: do-while loop
    printf("4. DO-WHILE LOOP\n");
    printf("  Counting 1 to 5: ");
    int num = 1;
    do {
        printf("%d ", num);
        num++;
    } while (num <= 5);
    printf("\n\n");
    
    // PART 5: Difference between while and do-while
    printf("5. WHILE vs DO-WHILE DIFFERENCE\n");
    int x = 10;
    
    printf("  While loop (condition false initially):\n");
    printf("    ");
    while (x < 5) {
        printf("%d ", x);  // This won't execute
        x++;
    }
    printf("(Nothing printed)\n");
    
    printf("  Do-while loop (condition false initially):\n");
    printf("    ");
    x = 10;
    do {
        printf("%d ", x);  // This executes once
        x++;
    } while (x < 5);
    printf("(Executed once)\n\n");
    
    // PART 6: Nested loops
    printf("6. NESTED LOOPS\n");
    printf("  Multiplication table (3x3):\n");
    for (int i = 1; i <= 3; i++) {
        printf("    ");
        for (int j = 1; j <= 3; j++) {
            printf("%2d ", i * j);
        }
        printf("\n");
    }
    printf("\n");
    
    // PART 7: Pattern printing
    printf("7. PATTERN PRINTING\n");
    printf("  Right triangle:\n");
    for (int i = 1; i <= 5; i++) {
        printf("    ");
        for (int j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
    printf("\n");
    
    // PART 8: break statement
    printf("8. BREAK STATEMENT\n");
    printf("  Searching for number 7: ");
    for (int i = 1; i <= 10; i++) {
        if (i == 7) {
            printf("Found!\n");
            break;  // Exit loop when 7 is found
        }
        printf("%d ", i);
    }
    printf("\n");
    
    // PART 9: continue statement
    printf("9. CONTINUE STATEMENT\n");
    printf("  Odd numbers from 1 to 10: ");
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // Skip even numbers
        }
        printf("%d ", i);
    }
    printf("\n\n");
    
    // PART 10: Infinite loop with break
    printf("10. INFINITE LOOP WITH BREAK\n");
    printf("  Counting until condition met: ");
    int counter = 0;
    while (1) {  // Infinite loop
        printf("%d ", counter);
        counter++;
        if (counter >= 5) {
            break;  // Exit condition
        }
    }
    printf("\n\n");
    
    // PART 11: Practical example - Sum of numbers
    printf("11. PRACTICAL EXAMPLE - SUM OF NUMBERS\n");
    int sum = 0;
    for (int i = 1; i <= 10; i++) {
        sum += i;
    }
    printf("  Sum of 1 to 10: %d\n\n", sum);
    
    // PART 12: Factorial calculation
    printf("12. PRACTICAL EXAMPLE - FACTORIAL\n");
    int n = 5;
    int factorial = 1;
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }
    printf("  %d! = %d\n\n", n, factorial);
    
    // PART 13: Finding prime numbers
    printf("13. PRACTICAL EXAMPLE - PRIME NUMBERS (2-20)\n");
    printf("  Primes: ");
    for (int num_to_test = 2; num_to_test <= 20; num_to_test++) {
        int is_prime = 1;
        for (int divisor = 2; divisor * divisor <= num_to_test; divisor++) {
            if (num_to_test % divisor == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            printf("%d ", num_to_test);
        }
    }
    printf("\n\n");
    
    // PART 14: Floyd's Triangle
    printf("14. FLOYD'S TRIANGLE (5 rows)\n");
    int value = 1;
    for (int i = 1; i <= 5; i++) {
        printf("  ");
        for (int j = 1; j <= i; j++) {
            printf("%2d ", value);
            value++;
        }
        printf("\n");
    }
    printf("\n");
    
    // PART 15: Fibonacci sequence
    printf("15. FIBONACCI SEQUENCE (first 10 numbers)\n");
    printf("  ");
    int fib1 = 0, fib2 = 1;
    printf("%d %d ", fib1, fib2);
    
    for (int i = 3; i <= 10; i++) {
        int next = fib1 + fib2;
        printf("%d ", next);
        fib1 = fib2;
        fib2 = next;
    }
    printf("\n\n");
    
    return 0;
}

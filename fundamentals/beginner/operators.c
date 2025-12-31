/**
 * Operators in C
 * 
 * This program demonstrates all the main types of operators in C:
 * - Arithmetic operators
 * - Relational operators
 * - Logical operators
 * - Bitwise operators
 * - Assignment operators
 * - Increment/Decrement operators
 */

#include <stdio.h>

int main(void) {
    printf("=== Operators in C ===\n\n");
    
    // Arithmetic Operators
    printf("1. ARITHMETIC OPERATORS\n");
    int a = 10, b = 3;
    printf("  a = %d, b = %d\n", a, b);
    printf("  Addition: a + b = %d\n", a + b);
    printf("  Subtraction: a - b = %d\n", a - b);
    printf("  Multiplication: a * b = %d\n", a * b);
    printf("  Division: a / b = %d\n", a / b);
    printf("  Modulus: a %% b = %d\n", a % b);
    printf("\n");
    
    // Relational Operators
    printf("2. RELATIONAL OPERATORS\n");
    int x = 5, y = 10;
    printf("  x = %d, y = %d\n", x, y);
    printf("  x == y: %d (equal to)\n", x == y);
    printf("  x != y: %d (not equal to)\n", x != y);
    printf("  x > y: %d (greater than)\n", x > y);
    printf("  x < y: %d (less than)\n", x < y);
    printf("  x >= y: %d (greater than or equal)\n", x >= y);
    printf("  x <= y: %d (less than or equal)\n", x <= y);
    printf("\n");
    
    // Logical Operators
    printf("3. LOGICAL OPERATORS\n");
    int true_val = 1, false_val = 0;
    printf("  true_val = %d, false_val = %d\n", true_val, false_val);
    printf("  true_val && false_val: %d (AND)\n", true_val && false_val);
    printf("  true_val || false_val: %d (OR)\n", true_val || false_val);
    printf("  !true_val: %d (NOT)\n", !true_val);
    printf("\n");
    
    // Bitwise Operators
    printf("4. BITWISE OPERATORS\n");
    unsigned int p = 12;  // 1100 in binary
    unsigned int q = 10;  // 1010 in binary
    printf("  p = %u (1100 in binary)\n", p);
    printf("  q = %u (1010 in binary)\n", q);
    printf("  p & q = %u (AND: 1000 = 8)\n", p & q);
    printf("  p | q = %u (OR: 1110 = 14)\n", p | q);
    printf("  p ^ q = %u (XOR: 0110 = 6)\n", p ^ q);
    printf("  ~p = %u (NOT: inverts all bits)\n", ~p);
    printf("  p << 1 = %u (Left shift: 11000 = 24)\n", p << 1);
    printf("  p >> 1 = %u (Right shift: 0110 = 6)\n", p >> 1);
    printf("\n");
    
    // Assignment Operators
    printf("5. ASSIGNMENT OPERATORS\n");
    int num = 10;
    printf("  num = %d (simple assignment)\n", num);
    num += 5;
    printf("  num += 5 => num = %d\n", num);
    num -= 3;
    printf("  num -= 3 => num = %d\n", num);
    num *= 2;
    printf("  num *= 2 => num = %d\n", num);
    num /= 4;
    printf("  num /= 4 => num = %d\n", num);
    num %= 5;
    printf("  num %%= 5 => num = %d\n", num);
    printf("\n");
    
    // Increment and Decrement Operators
    printf("6. INCREMENT/DECREMENT OPERATORS\n");
    int i = 5;
    printf("  i = %d\n", i);
    printf("  i++ (post-increment): %d, then i = %d\n", i++, i);
    printf("  ++i (pre-increment): %d\n", ++i);
    printf("  i-- (post-decrement): %d, then i = %d\n", i--, i);
    printf("  --i (pre-decrement): %d\n", --i);
    printf("\n");
    
    // Ternary Operator
    printf("7. TERNARY OPERATOR\n");
    int age = 20;
    char *status = (age >= 18) ? "Adult" : "Minor";
    printf("  age = %d\n", age);
    printf("  status = %s (using condition ? true : false)\n", status);
    printf("\n");
    
    // Operator Precedence Example
    printf("8. OPERATOR PRECEDENCE\n");
    int result = 2 + 3 * 4;
    printf("  2 + 3 * 4 = %d (multiplication before addition)\n", result);
    result = (2 + 3) * 4;
    printf("  (2 + 3) * 4 = %d (parentheses first)\n", result);
    printf("\n");
    
    return 0;
}

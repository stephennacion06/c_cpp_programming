/**
 * Control Flow in C
 * 
 * This program demonstrates control flow statements:
 * - if statement
 * - if-else statement
 * - if-else if-else ladder
 * - Nested if statements
 * - switch statement
 * - Ternary operator
 */

#include <stdio.h>

int main(void) {
    printf("=== Control Flow in C ===\n\n");
    
    // PART 1: Simple if statement
    printf("1. SIMPLE IF STATEMENT\n");
    int age = 20;
    printf("  Age: %d\n", age);
    
    if (age >= 18) {
        printf("  Result: You are an adult.\n");
    }
    printf("\n");
    
    // PART 2: if-else statement
    printf("2. IF-ELSE STATEMENT\n");
    int score = 75;
    printf("  Score: %d\n", score);
    
    if (score >= 60) {
        printf("  Result: Pass\n");
    } else {
        printf("  Result: Fail\n");
    }
    printf("\n");
    
    // PART 3: if-else if-else ladder
    printf("3. IF-ELSE IF-ELSE LADDER\n");
    int marks = 85;
    printf("  Marks: %d\n", marks);
    printf("  Grade: ");
    
    if (marks >= 90) {
        printf("A (Excellent)\n");
    } else if (marks >= 80) {
        printf("B (Very Good)\n");
    } else if (marks >= 70) {
        printf("C (Good)\n");
    } else if (marks >= 60) {
        printf("D (Pass)\n");
    } else {
        printf("F (Fail)\n");
    }
    printf("\n");
    
    // PART 4: Nested if statements
    printf("4. NESTED IF STATEMENTS\n");
    int temperature = 25;
    int is_raining = 0;
    
    printf("  Temperature: %d°C, Raining: %s\n", 
           temperature, is_raining ? "Yes" : "No");
    
    if (temperature > 30) {
        printf("  It's hot outside.\n");
        if (is_raining) {
            printf("  Take an umbrella!\n");
        } else {
            printf("  Don't forget sunscreen!\n");
        }
    } else if (temperature > 20) {
        printf("  Weather is pleasant.\n");
    } else {
        printf("  It's cold outside.\n");
        if (is_raining) {
            printf("  Take an umbrella and wear a jacket!\n");
        } else {
            printf("  Wear a jacket!\n");
        }
    }
    printf("\n");
    
    // PART 5: switch statement
    printf("5. SWITCH STATEMENT\n");
    int day = 3;
    printf("  Day number: %d\n", day);
    printf("  Day name: ");
    
    switch (day) {
        case 1:
            printf("Monday\n");
            break;
        case 2:
            printf("Tuesday\n");
            break;
        case 3:
            printf("Wednesday\n");
            break;
        case 4:
            printf("Thursday\n");
            break;
        case 5:
            printf("Friday\n");
            break;
        case 6:
            printf("Saturday\n");
            break;
        case 7:
            printf("Sunday\n");
            break;
        default:
            printf("Invalid day\n");
    }
    printf("\n");
    
    // PART 6: switch with fall-through
    printf("6. SWITCH WITH FALL-THROUGH\n");
    char grade = 'B';
    printf("  Grade: %c\n", grade);
    printf("  Result: ");
    
    switch (grade) {
        case 'A':
        case 'B':
        case 'C':
            printf("Passed\n");
            break;
        case 'D':
        case 'F':
            printf("Failed\n");
            break;
        default:
            printf("Invalid grade\n");
    }
    printf("\n");
    
    // PART 7: Ternary operator
    printf("7. TERNARY OPERATOR\n");
    int num = -5;
    printf("  Number: %d\n", num);
    
    char *result = (num >= 0) ? "Positive or Zero" : "Negative";
    printf("  Result: %s\n", result);
    
    // Nested ternary (use sparingly)
    int value = 42;
    char *category = (value < 0) ? "Negative" : 
                     (value == 0) ? "Zero" : "Positive";
    printf("  Value: %d is %s\n", value, category);
    printf("\n");
    
    // PART 8: Logical operators in conditions
    printf("8. LOGICAL OPERATORS IN CONDITIONS\n");
    int x = 15;
    printf("  x = %d\n", x);
    
    if (x > 10 && x < 20) {
        printf("  x is between 10 and 20\n");
    }
    
    if (x == 15 || x == 25) {
        printf("  x is either 15 or 25\n");
    }
    
    if (!(x < 0)) {
        printf("  x is not negative\n");
    }
    printf("\n");
    
    // PART 9: Multiple conditions example
    printf("9. REAL-WORLD EXAMPLE: TICKET PRICING\n");
    int person_age = 25;
    int is_student = 1;
    int is_senior = 0;
    
    printf("  Age: %d, Student: %s, Senior: %s\n", 
           person_age, 
           is_student ? "Yes" : "No",
           is_senior ? "Yes" : "No");
    
    float ticket_price;
    
    if (person_age < 5) {
        ticket_price = 0.0f;
        printf("  Ticket: FREE (Under 5)\n");
    } else if (is_senior) {
        ticket_price = 8.0f;
        printf("  Ticket: $%.2f (Senior discount)\n", ticket_price);
    } else if (is_student) {
        ticket_price = 10.0f;
        printf("  Ticket: $%.2f (Student discount)\n", ticket_price);
    } else {
        ticket_price = 15.0f;
        printf("  Ticket: $%.2f (Regular price)\n", ticket_price);
    }
    printf("\n");
    
    return 0;
}

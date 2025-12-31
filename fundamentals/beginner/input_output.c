/**
 * Input and Output in C
 * 
 * This program demonstrates standard input/output functions:
 * - printf() for formatted output
 * - scanf() for formatted input
 * - getchar() and putchar() for single characters
 * - gets() and puts() for strings (with safer alternatives)
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    printf("=== Input and Output in C ===\n\n");
    
    // PART 1: printf() - Formatted Output
    printf("1. PRINTF - FORMATTED OUTPUT\n");
    
    int age = 25;
    float height = 5.9f;
    char grade = 'A';
    
    printf("  Basic output: Hello, World!\n");
    printf("  Integer: %d\n", age);
    printf("  Float: %.2f\n", height);
    printf("  Character: %c\n", grade);
    printf("  String: %s\n", "C Programming");
    printf("\n");
    
    // Format specifiers with width and precision
    printf("2. PRINTF - FORMAT SPECIFIERS\n");
    printf("  Right-aligned: |%10d|\n", 42);
    printf("  Left-aligned:  |%-10d|\n", 42);
    printf("  Zero-padded:   |%05d|\n", 42);
    printf("  Float precision: %.2f\n", 3.14159);
    printf("  Scientific:    %e\n", 1234.56);
    printf("  Hexadecimal:   %x\n", 255);
    printf("\n");
    
    // PART 2: scanf() - Formatted Input
    printf("3. SCANF - FORMATTED INPUT\n");
    printf("Enter your age: ");
    
    int user_age;
    if (scanf("%d", &user_age) == 1) {
        printf("  You entered: %d years old\n", user_age);
    }
    
    // Clear input buffer
    while (getchar() != '\n');
    
    printf("Enter your name: ");
    char name[50];
    if (scanf("%49s", name) == 1) {
        printf("  Hello, %s!\n", name);
    }
    
    // Clear input buffer again
    while (getchar() != '\n');
    printf("\n");
    
    // PART 3: Character I/O
    printf("4. CHARACTER INPUT/OUTPUT\n");
    printf("Enter a single character: ");
    
    char ch = getchar();
    printf("  You entered: ");
    putchar(ch);
    putchar('\n');
    
    // Clear input buffer
    while (getchar() != '\n');
    printf("\n");
    
    // PART 4: Multiple inputs
    printf("5. MULTIPLE INPUTS\n");
    printf("Enter your age and height (e.g., 25 5.9): ");
    
    int input_age;
    float input_height;
    
    if (scanf("%d %f", &input_age, &input_height) == 2) {
        printf("  Age: %d, Height: %.1f\n", input_age, input_height);
    }
    
    // Clear input buffer
    while (getchar() != '\n');
    printf("\n");
    
    // PART 5: Safe string input with fgets
    printf("6. SAFE STRING INPUT\n");
    printf("Enter a sentence: ");
    
    char sentence[100];
    if (fgets(sentence, sizeof(sentence), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(sentence);
        if (len > 0 && sentence[len-1] == '\n') {
            sentence[len-1] = '\0';
        }
        printf("  You entered: \"%s\"\n", sentence);
    }
    printf("\n");
    
    return 0;
}

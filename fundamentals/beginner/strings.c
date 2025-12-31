/**
 * Strings in C
 * 
 * This program demonstrates:
 * - String declaration and initialization
 * - String input/output
 * - String library functions
 * - String manipulation
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    printf("=== Strings in C ===\n\n");
    
    // PART 1: String declaration and initialization
    printf("1. STRING DECLARATION\n");
    
    // Method 1: Character array
    char str1[10] = "Hello";
    
    // Method 2: String literal
    char str2[] = "World";
    
    // Method 3: Character by character
    char str3[6];
    str3[0] = 'H';
    str3[1] = 'e';
    str3[2] = 'l';
    str3[3] = 'l';
    str3[4] = 'o';
    str3[5] = '\0';  // Null terminator
    
    printf("  str1: %s\n", str1);
    printf("  str2: %s\n", str2);
    printf("  str3: %s\n", str3);
    printf("\n");
    
    // PART 2: String length
    printf("2. STRING LENGTH\n");
    char message[] = "Hello, World!";
    printf("  String: \"%s\"\n", message);
    printf("  Length: %zu characters\n", strlen(message));
    printf("  Size in memory: %zu bytes\n", sizeof(message));
    printf("\n");
    
    // PART 3: String copy
    printf("3. STRING COPY\n");
    char source[] = "Copy me";
    char destination[50];
    
    strcpy(destination, source);
    printf("  Source: %s\n", source);
    printf("  Destination: %s\n", destination);
    printf("\n");
    
    // PART 4: String concatenation
    printf("4. STRING CONCATENATION\n");
    char first[50] = "Hello";
    char second[] = " World";
    
    strcat(first, second);
    printf("  Result: %s\n", first);
    printf("\n");
    
    // PART 5: String comparison
    printf("5. STRING COMPARISON\n");
    char word1[] = "apple";
    char word2[] = "banana";
    char word3[] = "apple";
    
    int cmp1 = strcmp(word1, word2);
    int cmp2 = strcmp(word1, word3);
    
    printf("  strcmp(\"%s\", \"%s\") = %d ", word1, word2, cmp1);
    if (cmp1 < 0) printf("(apple < banana)\n");
    else if (cmp1 > 0) printf("(apple > banana)\n");
    else printf("(equal)\n");
    
    printf("  strcmp(\"%s\", \"%s\") = %d (equal)\n", word1, word3, cmp2);
    printf("\n");
    
    // PART 6: Character access
    printf("6. CHARACTER ACCESS\n");
    char text[] = "Programming";
    printf("  String: %s\n", text);
    printf("  First character: %c\n", text[0]);
    printf("  Last character: %c\n", text[strlen(text) - 1]);
    printf("\n");
    
    // PART 7: Modifying strings
    printf("7. MODIFYING STRINGS\n");
    char modify[] = "hello";
    printf("  Original: %s\n", modify);
    
    modify[0] = 'H';  // Change first character to uppercase
    printf("  Modified: %s\n", modify);
    printf("\n");
    
    // PART 8: String search
    printf("8. STRING SEARCH\n");
    char search_text[] = "The quick brown fox";
    char *found = strstr(search_text, "quick");
    
    if (found != NULL) {
        printf("  Found \"quick\" in \"%s\"\n", search_text);
        printf("  Position: %td\n", found - search_text);
    }
    printf("\n");
    
    // PART 9: String tokenization
    printf("9. STRING TOKENIZATION\n");
    char sentence[] = "apple,banana,cherry,date";
    char *token;
    
    printf("  Original: %s\n", sentence);
    printf("  Tokens: ");
    
    token = strtok(sentence, ",");
    while (token != NULL) {
        printf("%s ", token);
        token = strtok(NULL, ",");
    }
    printf("\n\n");
    
    // PART 10: String formatting
    printf("10. STRING FORMATTING\n");
    char buffer[100];
    int age = 25;
    char name[] = "Alice";
    
    sprintf(buffer, "%s is %d years old", name, age);
    printf("  Formatted: %s\n", buffer);
    printf("\n");
    
    return 0;
}

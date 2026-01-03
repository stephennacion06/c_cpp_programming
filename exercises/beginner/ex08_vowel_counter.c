/**
 * Exercise 8: Count Vowels and Consonants
 * 
 * Description:
 * Count the number of vowels and consonants in a string.
 * 
 * Requirements:
 * - Read a string from user
 * - Count vowels (a, e, i, o, u) - case insensitive
 * - Count consonants (other letters)
 * - Display the counts
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#endif

int is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

void count_vowels_consonants(const char* str, int* vowels, int* consonants) {
    *vowels = 0;
    *consonants = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            if (is_vowel(str[i])) {
                (*vowels)++;
            } else {
                (*consonants)++;
            }
        }
    }
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IOFBF, 1000);
#endif

    char text[200];
    int vowels, consonants;

    printf("========================================\n");
    printf("    COUNT VOWELS AND CONSONANTS        \n");
    printf("========================================\n\n");

    printf("Enter a string: ");
    fgets(text, sizeof(text), stdin);
    
    // Remove newline if present
    text[strcspn(text, "\n")] = '\0';

    count_vowels_consonants(text, &vowels, &consonants);

    printf("\nString: \"%s\"\n\n", text);
    printf("Results:\n");
    printf("  Vowels: %d\n", vowels);
    printf("  Consonants: %d\n", consonants);
    printf("  Total letters: %d\n", vowels + consonants);

    return 0;
}

# Strings in C

## Concept

In C, strings are arrays of characters terminated by a null character (`'\0'`). Unlike many other languages, C doesn't have a built-in string type, so strings are handled as character arrays.

## String Declaration and Initialization

### Method 1: String Literal
```c
char str[] = "Hello";  // {'H', 'e', 'l', 'l', 'o', '\0'}
```

### Method 2: Character Array with Size
```c
char str[10] = "Hello";  // Rest filled with '\0'
```

### Method 3: Character by Character
```c
char str[6];
str[0] = 'H';
str[1] = 'e';
str[2] = 'l';
str[3] = 'l';
str[4] = 'o';
str[5] = '\0';  // Must include null terminator!
```

## Null Terminator

**Critical:** Every C string must end with `'\0'` (null character):

```c
char str1[] = "Hello";      // ✅ Automatically adds '\0'
char str2[6] = {'H', 'e', 'l', 'l', 'o', '\0'};  // ✅ Manual '\0'
char str3[5] = {'H', 'e', 'l', 'l', 'o'};        // ❌ No '\0', not a valid string!
```

## String Input/Output

### Output
```c
char name[] = "Alice";
printf("%s\n", name);      // Print entire string
printf("%c\n", name[0]);   // Print first character
puts(name);                // Print string + newline
```

### Input

**scanf() - Reads until whitespace:**
```c
char word[50];
scanf("%49s", word);  // Stops at space/newline
```

**fgets() - Recommended for strings:**
```c
char line[100];
fgets(line, sizeof(line), stdin);  // Reads entire line, includes '\n'

// Remove newline
size_t len = strlen(line);
if (len > 0 && line[len-1] == '\n') {
    line[len-1] = '\0';
}
```

## String Library Functions

Include `<string.h>` to use these functions:

### strlen() - String Length
```c
char str[] = "Hello";
size_t len = strlen(str);  // Returns 5 (doesn't count '\0')
```

### strcpy() - String Copy
```c
char source[] = "Hello";
char dest[50];
strcpy(dest, source);  // dest becomes "Hello"
```

**Safe version:**
```c
strncpy(dest, source, sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';  // Ensure null termination
```

### strcat() - String Concatenation
```c
char str1[50] = "Hello";
char str2[] = " World";
strcat(str1, str2);  // str1 becomes "Hello World"
```

**Safe version:**
```c
strncat(str1, str2, sizeof(str1) - strlen(str1) - 1);
```

### strcmp() - String Comparison
```c
char str1[] = "apple";
char str2[] = "banana";

int result = strcmp(str1, str2);
// Returns: < 0 if str1 < str2
//          = 0 if str1 == str2
//          > 0 if str1 > str2

if (strcmp(str1, str2) == 0) {
    printf("Strings are equal\n");
}
```

### strchr() - Find Character
```c
char str[] = "Hello World";
char *ptr = strchr(str, 'W');  // Returns pointer to 'W'

if (ptr != NULL) {
    printf("Found at position: %ld\n", ptr - str);
}
```

### strstr() - Find Substring
```c
char text[] = "The quick brown fox";
char *found = strstr(text, "quick");

if (found != NULL) {
    printf("Found: %s\n", found);  // Prints: "quick brown fox"
}
```

### strtok() - Tokenize String
```c
char str[] = "apple,banana,cherry";
char *token = strtok(str, ",");

while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, ",");
}
// Prints: apple
//         banana
//         cherry
```

**Warning:** `strtok()` modifies the original string!

## Common String Operations

### 1. Convert to Uppercase
```c
for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
        str[i] = str[i] - 'a' + 'A';
    }
}
```

### 2. Reverse String
```c
int len = strlen(str);
for (int i = 0; i < len / 2; i++) {
    char temp = str[i];
    str[i] = str[len - 1 - i];
    str[len - 1 - i] = temp;
}
```

### 3. Count Words
```c
int count = 0;
int in_word = 0;

for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] != ' ' && !in_word) {
        count++;
        in_word = 1;
    } else if (str[i] == ' ') {
        in_word = 0;
    }
}
```

### 4. Check Palindrome
```c
int len = strlen(str);
int is_palindrome = 1;

for (int i = 0; i < len / 2; i++) {
    if (str[i] != str[len - 1 - i]) {
        is_palindrome = 0;
        break;
    }
}
```

## String Formatting

### sprintf() - Format to String
```c
char buffer[100];
int age = 25;
char name[] = "Alice";

sprintf(buffer, "%s is %d years old", name, age);
// buffer now contains: "Alice is 25 years old"
```

### sscanf() - Parse from String
```c
char input[] = "25 3.14 Hello";
int num;
float flt;
char word[50];

sscanf(input, "%d %f %s", &num, &flt, word);
// num = 25, flt = 3.14, word = "Hello"
```

## Best Practices

1. **Always allocate enough space** for strings (including '\0')
2. **Use `sizeof()` or `strlen()` to prevent buffer overflow**
3. **Prefer `fgets()` over `gets()` or `scanf("%s")`**
4. **Use safe versions**: `strncpy()`, `strncat()`, `snprintf()`
5. **Check for `NULL` after `strchr()`, `strstr()`, etc.**
6. **Remember strings are mutable** - changes affect the original

## Common Pitfalls

⚠️ **Buffer overflow**
```c
char str[5];
strcpy(str, "Hello World");  // ❌ Overflow! str can only hold 4 chars + '\0'
```

⚠️ **Forgetting null terminator**
```c
char str[5] = {'H', 'e', 'l', 'l', 'o'};  // ❌ No '\0'!
printf("%s\n", str);  // Undefined behavior
```

⚠️ **Comparing with ==**
```c
char str1[] = "hello";
char str2[] = "hello";
if (str1 == str2) {  // ❌ Compares pointers, not content!
    // ...
}

// ✅ Correct
if (strcmp(str1, str2) == 0) {
    // ...
}
```

⚠️ **Not checking buffer size with scanf**
```c
char name[10];
scanf("%s", name);  // ❌ Can overflow if input > 9 chars

// ✅ Better
scanf("%9s", name);  // Limit to 9 chars
```

⚠️ **Modifying string literals**
```c
char *str = "Hello";  // String literal (read-only)
str[0] = 'h';         // ❌ Undefined behavior!

// ✅ Correct
char str[] = "Hello";  // Mutable array
str[0] = 'h';          // ✅ OK
```

⚠️ **Not removing newline from fgets()**
```c
char input[100];
fgets(input, sizeof(input), stdin);  // Includes '\n'!

// ✅ Remove it
size_t len = strlen(input);
if (len > 0 && input[len-1] == '\n') {
    input[len-1] = '\0';
}
```

## Complete Examples

### Example 1: String Reversal
```c
#include <stdio.h>
#include <string.h>

void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int main(void) {
    char text[] = "Hello";
    printf("Original: %s\n", text);
    reverse_string(text);
    printf("Reversed: %s\n", text);
    return 0;
}
```

### Example 2: Word Counter
```c
#include <stdio.h>
#include <ctype.h>

int count_words(char *str) {
    int count = 0;
    int in_word = 0;
    
    while (*str) {
        if (isspace(*str)) {
            in_word = 0;
        } else if (!in_word) {
            count++;
            in_word = 1;
        }
        str++;
    }
    
    return count;
}

int main(void) {
    char sentence[] = "The quick brown fox";
    printf("Word count: %d\n", count_words(sentence));
    return 0;
}
```

### Example 3: Case Conversion
```c
#include <stdio.h>
#include <ctype.h>

void to_upper(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

int main(void) {
    char text[] = "hello world";
    printf("Original: %s\n", text);
    to_upper(text);
    printf("Uppercase: %s\n", text);
    return 0;
}
```

## Exercise

Modify `strings.c` to:
1. Implement a function to count vowels in a string
2. Create a function to check if a string is a palindrome
3. Write a function to remove all spaces from a string
4. Implement substring extraction

## Next Steps

- Learn about [Pointers](../intermediate/pointers.md) for advanced string manipulation
- Explore [Dynamic Memory](../intermediate/dynamic-memory.md) for variable-length strings
- Study [File I/O](../intermediate/file-io.md) for reading/writing text files

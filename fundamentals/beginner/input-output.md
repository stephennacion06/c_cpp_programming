# Input and Output in C

## Concept

Input and output (I/O) operations allow programs to interact with users and external data sources. C provides several functions for I/O operations through the `<stdio.h>` standard library.

## Output Functions

### printf() - Formatted Output

The most versatile output function in C:

```c
printf("format string", argument1, argument2, ...);
```

#### Common Format Specifiers

| Specifier | Data Type | Example |
|-----------|-----------|---------|
| `%d` or `%i` | int (decimal) | `printf("%d", 42)` → `42` |
| `%f` | float/double | `printf("%f", 3.14)` → `3.140000` |
| `%c` | char | `printf("%c", 'A')` → `A` |
| `%s` | string (char array) | `printf("%s", "Hello")` → `Hello` |
| `%u` | unsigned int | `printf("%u", 100)` → `100` |
| `%x` | hexadecimal | `printf("%x", 255)` → `ff` |
| `%o` | octal | `printf("%o", 8)` → `10` |
| `%p` | pointer | `printf("%p", &var)` → `0x7ffc...` |
| `%%` | percent sign | `printf("100%%")` → `100%` |

#### Format Modifiers

```c
// Width and precision
printf("%5d", 42);        // "   42" (right-aligned, width 5)
printf("%-5d", 42);       // "42   " (left-aligned, width 5)
printf("%05d", 42);       // "00042" (zero-padded)
printf("%.2f", 3.14159);  // "3.14" (2 decimal places)
printf("%10.2f", 3.14);   // "      3.14" (width 10, 2 decimals)
```

### puts() - String Output

Simpler function for printing strings (adds newline automatically):

```c
puts("Hello, World!");  // Equivalent to printf("Hello, World!\n");
```

### putchar() - Character Output

Outputs a single character:

```c
putchar('A');  // Prints: A
putchar('\n'); // Prints: newline
```

## Input Functions

### scanf() - Formatted Input

Reads formatted input from stdin:

```c
scanf("format string", &variable1, &variable2, ...);
```

**Important:** Use the `&` (address-of) operator for variables!

```c
int age;
scanf("%d", &age);  // ✅ Correct

char name[50];
scanf("%s", name);  // ✅ Correct (arrays don't need &)
```

#### Common Format Specifiers

| Specifier | Data Type | Example |
|-----------|-----------|---------|
| `%d` | int | `scanf("%d", &num)` |
| `%f` | float | `scanf("%f", &price)` |
| `%lf` | double | `scanf("%lf", &value)` |
| `%c` | char | `scanf("%c", &ch)` |
| `%s` | string | `scanf("%s", str)` |

#### Reading Multiple Values

```c
int day, month, year;
scanf("%d %d %d", &day, &month, &year);  // Input: 31 12 2025
```

### getchar() - Character Input

Reads a single character:

```c
char ch = getchar();
```

### fgets() - Safe String Input

**Recommended** for reading strings (prevents buffer overflow):

```c
char str[100];
fgets(str, sizeof(str), stdin);  // Safer than gets()
```

**Note:** `fgets()` includes the newline character in the string. Remove it:

```c
char str[100];
fgets(str, sizeof(str), stdin);

// Remove newline
size_t len = strlen(str);
if (len > 0 && str[len-1] == '\n') {
    str[len-1] = '\0';
}
```

## Escape Sequences

Special characters in strings:

| Sequence | Description |
|----------|-------------|
| `\n` | Newline |
| `\t` | Tab |
| `\\` | Backslash |
| `\"` | Double quote |
| `\'` | Single quote |
| `\0` | Null character |

```c
printf("Line 1\nLine 2\n");
printf("Name:\tJohn\n");
printf("Quote: \"Hello\"\n");
```

## Input Buffer Issues

### Problem: Leftover newline

```c
int num;
char ch;

scanf("%d", &num);   // User types: 42<Enter>
scanf("%c", &ch);    // ❌ Reads the newline, not next char!
```

### Solution: Clear the buffer

```c
// Method 1: Consume newline
scanf("%d", &num);
while (getchar() != '\n');  // Clear buffer
scanf("%c", &ch);

// Method 2: Add space before %c
scanf("%d", &num);
scanf(" %c", &ch);  // Space skips whitespace
```

## Error Checking

Always check if `scanf()` succeeded:

```c
int num;
if (scanf("%d", &num) == 1) {
    printf("Successfully read: %d\n", num);
} else {
    printf("Invalid input!\n");
}
```

## Best Practices

1. **Always validate input** - Check return values of `scanf()`
2. **Use `fgets()` for strings** - Safer than `gets()` or `scanf("%s")`
3. **Clear input buffer** when mixing `scanf()` and `getchar()`
4. **Specify field width** in `scanf()` to prevent buffer overflow
   ```c
   char name[50];
   scanf("%49s", name);  // Prevents overflow
   ```
5. **Use meaningful prompts** - Tell users what input you expect

## Common Pitfalls

⚠️ **Forgetting & in scanf()**
```c
int x;
scanf("%d", x);   // ❌ Wrong! Should be &x
scanf("%d", &x);  // ✅ Correct
```

⚠️ **Buffer overflow with scanf()**
```c
char name[10];
scanf("%s", name);  // ❌ Dangerous if user enters >9 chars
scanf("%9s", name); // ✅ Safer, limits to 9 chars
```

⚠️ **Mixing %c with other specifiers**
```c
int num;
char ch;
scanf("%d", &num);
scanf("%c", &ch);   // ❌ Reads newline!
scanf(" %c", &ch);  // ✅ Space skips whitespace
```

⚠️ **Using gets()**
```c
gets(str);  // ❌ Deprecated, unsafe!
fgets(str, sizeof(str), stdin);  // ✅ Use this instead
```

## Complete Example

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char name[50];
    int age;
    float height;
    
    // Get user input
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    
    // Remove newline
    size_t len = strlen(name);
    if (len > 0 && name[len-1] == '\n') {
        name[len-1] = '\0';
    }
    
    printf("Enter your age: ");
    if (scanf("%d", &age) != 1) {
        printf("Invalid age!\n");
        return 1;
    }
    
    printf("Enter your height in meters: ");
    if (scanf("%f", &height) != 1) {
        printf("Invalid height!\n");
        return 1;
    }
    
    // Display results
    printf("\n=== Your Information ===\n");
    printf("Name: %s\n", name);
    printf("Age: %d years\n", age);
    printf("Height: %.2f meters\n", height);
    
    return 0;
}
```

## Exercise

Modify `input_output.c` to:
1. Create a simple calculator that takes two numbers and an operator
2. Validate all user inputs and display appropriate error messages
3. Use formatted output to create a neat table display

## Next Steps

- Learn about [Control Flow](control-flow.md) to make decisions based on input
- Explore [Functions](functions.md) to organize input/output code

# Variables and Data Types in C

## Concept

Variables are named storage locations in memory that hold values. Every variable in C has a specific **data type** that determines what kind of data it can store and how much memory it uses.

## Basic Data Types

### Integer Types

| Type | Size | Range (typical) |
|------|------|----------------|
| `char` | 1 byte | -128 to 127 or 0 to 255 |
| `short` | 2 bytes | -32,768 to 32,767 |
| `int` | 4 bytes | -2,147,483,648 to 2,147,483,647 |
| `long` | 4 or 8 bytes | Platform dependent |
| `long long` | 8 bytes | ±9 quintillion |

### Floating-Point Types

| Type | Size | Precision |
|------|------|-----------|
| `float` | 4 bytes | ~6-7 decimal digits |
| `double` | 8 bytes | ~15-16 decimal digits |
| `long double` | 8-16 bytes | Platform dependent |

### Character Type

- `char`: Stores a single character (uses ASCII or Unicode values)
- Can also be used as a small integer (-128 to 127)

## Variable Declaration and Initialization

```c
// Declaration only
int age;

// Declaration with initialization
int year = 2025;

// Multiple declarations
int x, y, z;

// Multiple declarations with initialization
int a = 1, b = 2, c = 3;
```

## Constants

Constants are values that cannot be changed after initialization:

```c
// Using const keyword
const double PI = 3.14159;

// Using #define preprocessor directive
#define MAX_SIZE 100
```

## Type Modifiers

### Signed vs Unsigned

```c
signed int num1 = -100;      // Can be negative
unsigned int num2 = 100;     // Only positive
```

### Short and Long

```c
short int small = 100;       // Smaller range
long int big = 1000000L;     // Larger range
```

## Type Casting

Converting one data type to another:

```c
// Implicit casting (automatic)
int x = 10;
float y = x;  // int converted to float

// Explicit casting (manual)
int a = 10;
int b = 3;
float result = (float)a / b;  // Forces float division
```

## sizeof Operator

Returns the size of a data type in bytes:

```c
printf("Size of int: %zu bytes\n", sizeof(int));
printf("Size of double: %zu bytes\n", sizeof(double));
```

## Best Practices

1. **Initialize variables** when you declare them
2. **Use meaningful names**: `user_age` instead of `ua`
3. **Use `const` for values that won't change**
4. **Choose appropriate types**: Don't use `long long` if `int` is sufficient
5. **Be aware of integer overflow** with unsigned types

## Common Pitfalls

⚠️ **Uninitialized variables**: Always initialize variables before use
```c
int x;
printf("%d", x);  // ❌ Undefined behavior
```

⚠️ **Integer overflow**: Be careful with calculations
```c
int x = 2147483647;  // Max int value
x = x + 1;           // ❌ Overflow: wraps around to negative
```

⚠️ **Float precision**: Floating-point numbers are approximations
```c
float x = 0.1 + 0.2;  // May not equal exactly 0.3
```

## Exercise

Try modifying `variables_and_data_types.c` to:
1. Add variables for your name (as a char array), height (float), and birth year (int)
2. Calculate and display your approximate age
3. Experiment with different format specifiers in `printf()`

## Next Steps

- Learn about [Operators](operators.md) to perform calculations with variables
- Explore [Input/Output](input-output.md) to get user input

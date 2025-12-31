# Operators in C

## Concept

Operators are special symbols that perform operations on operands (variables or values). C provides a rich set of operators for various operations.

## 1. Arithmetic Operators

Used for mathematical calculations:

| Operator | Description | Example | Result |
|----------|-------------|---------|--------|
| `+` | Addition | `5 + 3` | `8` |
| `-` | Subtraction | `5 - 3` | `2` |
| `*` | Multiplication | `5 * 3` | `15` |
| `/` | Division | `5 / 3` | `1` (integer division) |
| `%` | Modulus (remainder) | `5 % 3` | `2` |

```c
int a = 10, b = 3;
int sum = a + b;        // 13
int diff = a - b;       // 7
int product = a * b;    // 30
int quotient = a / b;   // 3 (integer division)
int remainder = a % b;  // 1
```

## 2. Relational Operators

Compare two values and return `1` (true) or `0` (false):

| Operator | Description | Example |
|----------|-------------|---------|
| `==` | Equal to | `5 == 3` → `0` |
| `!=` | Not equal to | `5 != 3` → `1` |
| `>` | Greater than | `5 > 3` → `1` |
| `<` | Less than | `5 < 3` → `0` |
| `>=` | Greater than or equal | `5 >= 5` → `1` |
| `<=` | Less than or equal | `5 <= 3` → `0` |

```c
int x = 5, y = 10;
if (x < y) {
    printf("x is less than y\n");
}
```

## 3. Logical Operators

Used to combine conditional statements:

| Operator | Description | Example |
|----------|-------------|---------|
| `&&` | Logical AND | `(5 > 3) && (2 < 4)` → `1` |
| `\|\|` | Logical OR | `(5 > 3) \|\| (2 > 4)` → `1` |
| `!` | Logical NOT | `!(5 > 3)` → `0` |

```c
int age = 25;
int has_license = 1;

if (age >= 18 && has_license) {
    printf("Can drive\n");
}
```

## 4. Bitwise Operators

Operate on individual bits:

| Operator | Description | Example (binary) |
|----------|-------------|------------------|
| `&` | AND | `1100 & 1010 = 1000` |
| `\|` | OR | `1100 \| 1010 = 1110` |
| `^` | XOR | `1100 ^ 1010 = 0110` |
| `~` | NOT | `~1100 = 0011` |
| `<<` | Left shift | `1100 << 1 = 11000` |
| `>>` | Right shift | `1100 >> 1 = 0110` |

```c
unsigned int a = 12;  // 1100 in binary
unsigned int b = 10;  // 1010 in binary
unsigned int result = a & b;  // 8 (1000 in binary)
```

## 5. Assignment Operators

Assign values to variables:

| Operator | Description | Equivalent |
|----------|-------------|------------|
| `=` | Simple assignment | `x = 5` |
| `+=` | Add and assign | `x += 5` → `x = x + 5` |
| `-=` | Subtract and assign | `x -= 5` → `x = x - 5` |
| `*=` | Multiply and assign | `x *= 5` → `x = x * 5` |
| `/=` | Divide and assign | `x /= 5` → `x = x / 5` |
| `%=` | Modulus and assign | `x %= 5` → `x = x % 5` |

```c
int x = 10;
x += 5;  // x is now 15
x *= 2;  // x is now 30
```

## 6. Increment and Decrement Operators

| Operator | Description | Example |
|----------|-------------|---------|
| `++` | Increment by 1 | `++x` or `x++` |
| `--` | Decrement by 1 | `--x` or `x--` |

**Important difference:**
- **Pre-increment** (`++x`): Increment first, then use value
- **Post-increment** (`x++`): Use value first, then increment

```c
int x = 5;
int y = ++x;  // x = 6, y = 6 (increment first)
int z = x++;  // x = 7, z = 6 (use first, then increment)
```

## 7. Ternary Operator

A shorthand for `if-else`:

```c
condition ? expression_if_true : expression_if_false;
```

```c
int age = 20;
char *status = (age >= 18) ? "Adult" : "Minor";
```

## 8. sizeof Operator

Returns the size of a data type or variable in bytes:

```c
printf("Size of int: %zu bytes\n", sizeof(int));
printf("Size of array: %zu bytes\n", sizeof(array));
```

## Operator Precedence

Operators are evaluated in a specific order:

1. `()` - Parentheses (highest)
2. `!`, `~`, `++`, `--` - Unary operators
3. `*`, `/`, `%` - Multiplication, division, modulus
4. `+`, `-` - Addition, subtraction
5. `<<`, `>>` - Bitwise shifts
6. `<`, `<=`, `>`, `>=` - Relational
7. `==`, `!=` - Equality
8. `&` - Bitwise AND
9. `^` - Bitwise XOR
10. `|` - Bitwise OR
11. `&&` - Logical AND
12. `||` - Logical OR
13. `?:` - Ternary
14. `=`, `+=`, `-=`, etc. - Assignment (lowest)

## Best Practices

1. **Use parentheses** for clarity, even when not strictly needed
2. **Avoid complex expressions** - break them into multiple steps
3. **Be careful with `==` vs `=`** - common mistake in conditions
4. **Use pre-increment** when the result isn't used (slightly more efficient)

## Common Pitfalls

⚠️ **Assignment in condition**
```c
if (x = 5)  // ❌ Always true, assigns 5 to x
if (x == 5) // ✅ Correct comparison
```

⚠️ **Integer division**
```c
int result = 5 / 2;      // ❌ result = 2 (not 2.5)
float result = 5.0 / 2;  // ✅ result = 2.5
```

⚠️ **Operator precedence**
```c
int x = 5 + 3 * 2;  // x = 11, not 16
```

## Exercise

Modify `operators.c` to:
1. Calculate the area of a circle given radius (use `*` operator and `PI`)
2. Check if a number is even using modulus operator
3. Swap two numbers using bitwise XOR
4. Practice pre and post increment in a loop

## Next Steps

- Learn about [Control Flow](control-flow.md) to use operators in conditions
- Explore [Input/Output](input-output.md) to get values from users

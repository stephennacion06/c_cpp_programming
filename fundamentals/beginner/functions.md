# Functions in C

## Concept

Functions are reusable blocks of code that perform specific tasks. They help organize code, avoid repetition, and make programs easier to understand and maintain.

## Function Structure

```c
return_type function_name(parameter_list) {
    // Function body
    return value;  // If return_type is not void
}
```

**Components:**
- **return_type**: Data type of the value returned (or `void` if no return)
- **function_name**: Identifier for the function
- **parameter_list**: Input values (or `void` if no parameters)
- **Function body**: Code to execute
- **return**: Returns a value to the caller

## Function Declaration vs Definition

### Declaration (Prototype)
Tells the compiler the function exists (usually in header or top of file):

```c
int add(int a, int b);  // Declaration
```

### Definition
Provides the actual implementation:

```c
int add(int a, int b) {  // Definition
    return a + b;
}
```

### Complete Example
```c
#include <stdio.h>

// Declaration (prototype)
int multiply(int x, int y);

int main(void) {
    int result = multiply(5, 3);
    printf("Result: %d\n", result);
    return 0;
}

// Definition
int multiply(int x, int y) {
    return x * y;
}
```

## Types of Functions

### 1. No Parameters, No Return Value

```c
void greet(void) {
    printf("Hello, World!\n");
}

int main(void) {
    greet();  // Just calls the function
    return 0;
}
```

### 2. With Parameters, No Return Value

```c
void print_sum(int a, int b) {
    printf("Sum: %d\n", a + b);
}

int main(void) {
    print_sum(5, 3);  // Output: Sum: 8
    return 0;
}
```

### 3. No Parameters, With Return Value

```c
int get_lucky_number(void) {
    return 7;
}

int main(void) {
    int num = get_lucky_number();
    printf("Lucky number: %d\n", num);
    return 0;
}
```

### 4. With Parameters and Return Value

```c
int add(int a, int b) {
    return a + b;
}

int main(void) {
    int sum = add(10, 20);
    printf("Sum: %d\n", sum);
    return 0;
}
```

## Function Parameters

### Pass by Value

C passes arguments by value (copies the value):

```c
void modify(int x) {
    x = 100;  // Changes local copy only
}

int main(void) {
    int num = 50;
    modify(num);
    printf("%d\n", num);  // Still prints 50!
    return 0;
}
```

### Pass by Reference (using pointers)

To modify the original variable, pass its address:

```c
void modify(int *x) {
    *x = 100;  // Changes original value
}

int main(void) {
    int num = 50;
    modify(&num);  // Pass address
    printf("%d\n", num);  // Prints 100
    return 0;
}
```

### Example: Swap Function

**Wrong way (pass by value):**
```c
void swap_wrong(int a, int b) {
    int temp = a;
    a = b;
    b = temp;  // Only swaps local copies!
}
```

**Correct way (pass by reference):**
```c
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;  // Swaps original values
}

int main(void) {
    int x = 10, y = 20;
    swap(&x, &y);
    printf("x=%d, y=%d\n", x, y);  // x=20, y=10
    return 0;
}
```

## Return Statement

### Single Return
```c
int absolute(int x) {
    if (x < 0) {
        return -x;
    }
    return x;
}
```

### Multiple Returns (use carefully)
```c
int sign(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}
```

### Early Return
```c
int divide(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero!\n");
        return 0;  // Early exit
    }
    return a / b;
}
```

## Recursion

A function that calls itself:

### Example 1: Factorial
```c
int factorial(int n) {
    // Base case
    if (n <= 1) {
        return 1;
    }
    // Recursive case
    return n * factorial(n - 1);
}

// factorial(5) = 5 * factorial(4)
//              = 5 * 4 * factorial(3)
//              = 5 * 4 * 3 * factorial(2)
//              = 5 * 4 * 3 * 2 * factorial(1)
//              = 5 * 4 * 3 * 2 * 1 = 120
```

### Example 2: Fibonacci
```c
int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

**Important:** Always have a base case to prevent infinite recursion!

## Functions with Arrays

Arrays are passed by reference (automatically):

```c
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void modify_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;  // Modifies original array!
    }
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    print_array(numbers, size);
    modify_array(numbers, size);
    print_array(numbers, size);  // Array is modified
    
    return 0;
}
```

## Variable Scope

### Local Variables
Visible only within the function:

```c
void function1(void) {
    int x = 10;  // Local to function1
}

void function2(void) {
    // Can't access x from function1
    int x = 20;  // Different x
}
```

### Global Variables
Visible to all functions (use sparingly):

```c
int global_count = 0;  // Global variable

void increment(void) {
    global_count++;  // Can access global
}

int main(void) {
    increment();
    printf("%d\n", global_count);  // Prints 1
    return 0;
}
```

## Function Best Practices

1. **Use meaningful names**: `calculate_average()` not `func1()`
2. **Keep functions small**: One function, one task
3. **Use parameters, not globals**: Makes functions reusable
4. **Document complex functions**: Use comments
5. **Return early on errors**: Check conditions at the start
6. **Avoid deep recursion**: Can cause stack overflow

## Common Pitfalls

⚠️ **Forgetting to declare function before use**
```c
int main(void) {
    foo();  // ❌ Error: foo() not declared
    return 0;
}

void foo(void) {
    printf("Hello\n");
}

// ✅ Solution: Add prototype at top
void foo(void);  // Prototype
```

⚠️ **Not returning a value**
```c
int add(int a, int b) {
    int sum = a + b;
    // ❌ Missing return!
}

// ✅ Correct
int add(int a, int b) {
    return a + b;
}
```

⚠️ **Modifying array size parameter**
```c
void print_array(int arr[], int size) {
    size--;  // ❌ Only modifies local copy
}
```

⚠️ **Infinite recursion**
```c
int bad_factorial(int n) {
    return n * bad_factorial(n - 1);  // ❌ No base case!
}
```

⚠️ **Using function before declaration**
```c
int main(void) {
    int x = add(1, 2);  // ❌ add() not yet declared
    return 0;
}

int add(int a, int b) {
    return a + b;
}
```

## Complete Examples

### Example 1: Temperature Converter
```c
double celsius_to_fahrenheit(double celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

double fahrenheit_to_celsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

int main(void) {
    double temp_c = 25.0;
    double temp_f = celsius_to_fahrenheit(temp_c);
    printf("%.1f°C = %.1f°F\n", temp_c, temp_f);
    return 0;
}
```

### Example 2: Prime Number Checker
```c
int is_prime(int n) {
    if (n < 2) return 0;
    
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;  // Not prime
        }
    }
    return 1;  // Prime
}

int main(void) {
    for (int i = 2; i <= 20; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}
```

### Example 3: Array Operations
```c
int sum_array(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

double average_array(int arr[], int size) {
    if (size == 0) return 0.0;
    return (double)sum_array(arr, size) / size;
}

int main(void) {
    int numbers[] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("Sum: %d\n", sum_array(numbers, size));
    printf("Average: %.2f\n", average_array(numbers, size));
    
    return 0;
}
```

## Exercise

Modify `functions.c` to:
1. Create a function to check if a number is even
2. Implement a power function (x^n) using recursion
3. Create functions to find min, max, and average of an array
4. Write a function that reverses an array in-place

## Next Steps

- Learn about [Arrays](arrays.md) to work with collections of data
- Explore [Strings](strings.md) for text manipulation
- Study [Pointers](../intermediate/pointers.md) for advanced parameter passing

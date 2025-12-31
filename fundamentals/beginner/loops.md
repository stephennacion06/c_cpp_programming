# Loops in C

## Concept

Loops allow you to execute a block of code repeatedly. C provides three types of loops: `for`, `while`, and `do-while`.

## 1. for Loop

Best when you know in advance how many times to loop:

```c
for (initialization; condition; update) {
    // Code to repeat
}
```

**Execution flow:**
1. Execute initialization (once)
2. Check condition
3. If true, execute loop body
4. Execute update
5. Repeat from step 2

**Example:**
```c
for (int i = 0; i < 5; i++) {
    printf("%d ", i);  // Prints: 0 1 2 3 4
}
```

### Common for Loop Patterns

```c
// Counting up
for (int i = 0; i < 10; i++) {
    printf("%d ", i);
}

// Counting down
for (int i = 10; i > 0; i--) {
    printf("%d ", i);
}

// Step by 2
for (int i = 0; i < 10; i += 2) {
    printf("%d ", i);  // 0 2 4 6 8
}

// Multiple variables
for (int i = 0, j = 10; i < 5; i++, j--) {
    printf("i=%d, j=%d\n", i, j);
}
```

## 2. while Loop

Best when you don't know how many iterations in advance:

```c
while (condition) {
    // Code to repeat
}
```

**Execution flow:**
1. Check condition
2. If true, execute loop body
3. Repeat from step 1

**Example:**
```c
int count = 0;
while (count < 5) {
    printf("%d ", count);
    count++;
}
```

### Common while Loop Patterns

```c
// Input validation
int num;
printf("Enter a positive number: ");
scanf("%d", &num);
while (num <= 0) {
    printf("Invalid! Try again: ");
    scanf("%d", &num);
}

// Reading until end of input
char ch;
while ((ch = getchar()) != '\n') {
    printf("%c", ch);
}

// Infinite loop with break
while (1) {
    // Do something
    if (exit_condition) {
        break;
    }
}
```

## 3. do-while Loop

Executes at least once, then checks condition:

```c
do {
    // Code to repeat
} while (condition);
```

**Execution flow:**
1. Execute loop body
2. Check condition
3. If true, repeat from step 1

**Example:**
```c
int num;
do {
    printf("Enter a number (1-10): ");
    scanf("%d", &num);
} while (num < 1 || num > 10);
```

### while vs do-while

**while:** Checks condition first (may not execute at all)
```c
int x = 10;
while (x < 5) {
    printf("%d ", x);  // Never executes
}
```

**do-while:** Executes first, then checks (always executes at least once)
```c
int x = 10;
do {
    printf("%d ", x);  // Executes once, prints 10
} while (x < 5);
```

## 4. Nested Loops

A loop inside another loop:

```c
for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
        printf("(%d,%d) ", i, j);
    }
    printf("\n");
}
```

**Output:**
```
(1,1) (1,2) (1,3)
(2,1) (2,2) (2,3)
(3,1) (3,2) (3,3)
```

### Pattern Printing Example

Right triangle:
```c
for (int i = 1; i <= 5; i++) {
    for (int j = 1; j <= i; j++) {
        printf("* ");
    }
    printf("\n");
}
```

**Output:**
```
* 
* * 
* * * 
* * * * 
* * * * *
```

## 5. Loop Control Statements

### break Statement

Immediately exits the loop:

```c
for (int i = 1; i <= 10; i++) {
    if (i == 5) {
        break;  // Exit loop when i is 5
    }
    printf("%d ", i);  // Prints: 1 2 3 4
}
```

**Common use:** Searching for an element
```c
int found = 0;
for (int i = 0; i < n; i++) {
    if (array[i] == target) {
        found = 1;
        break;
    }
}
```

### continue Statement

Skips the rest of the current iteration:

```c
for (int i = 1; i <= 5; i++) {
    if (i == 3) {
        continue;  // Skip 3
    }
    printf("%d ", i);  // Prints: 1 2 4 5
}
```

**Common use:** Filtering
```c
// Print only odd numbers
for (int i = 1; i <= 10; i++) {
    if (i % 2 == 0) {
        continue;  // Skip even numbers
    }
    printf("%d ", i);
}
```

## Choosing the Right Loop

| Loop Type | Use When |
|-----------|----------|
| **for** | You know the number of iterations |
| **while** | Number of iterations depends on a condition |
| **do-while** | Loop must execute at least once |

## Common Loop Patterns

### 1. Accumulator Pattern
```c
int sum = 0;
for (int i = 1; i <= 100; i++) {
    sum += i;
}
printf("Sum: %d\n", sum);
```

### 2. Counter Pattern
```c
int count = 0;
for (int i = 0; i < n; i++) {
    if (condition) {
        count++;
    }
}
```

### 3. Search Pattern
```c
int found_index = -1;
for (int i = 0; i < n; i++) {
    if (array[i] == target) {
        found_index = i;
        break;
    }
}
```

### 4. Max/Min Pattern
```c
int max = array[0];
for (int i = 1; i < n; i++) {
    if (array[i] > max) {
        max = array[i];
    }
}
```

## Best Practices

1. **Initialize loop variables** before the loop
2. **Avoid modifying loop counters** inside the loop body
3. **Use meaningful variable names** (not just `i, j, k`)
4. **Keep loop bodies simple** - extract complex logic into functions
5. **Avoid infinite loops** - ensure the condition will eventually be false
6. **Use `break` carefully** - too many can make code hard to follow

## Common Pitfalls

⚠️ **Off-by-one errors**
```c
// ❌ Loop runs 11 times (0 to 10)
for (int i = 0; i <= 10; i++)

// ✅ Loop runs 10 times (0 to 9)
for (int i = 0; i < 10; i++)
```

⚠️ **Infinite loops**
```c
// ❌ Infinite loop - counter never changes
int i = 0;
while (i < 10) {
    printf("%d ", i);
    // Missing: i++;
}
```

⚠️ **Modifying loop counter inside loop**
```c
// ❌ Confusing and error-prone
for (int i = 0; i < 10; i++) {
    i += 2;  // Don't do this!
}
```

⚠️ **Semicolon after loop header**
```c
// ❌ Empty loop body
for (int i = 0; i < 10; i++);
{
    printf("%d ", i);  // Only executes once!
}
```

⚠️ **Floating-point loop counters**
```c
// ❌ Can cause precision issues
for (float x = 0.0; x != 1.0; x += 0.1) {
    // May never reach 1.0 exactly!
}

// ✅ Better
for (int i = 0; i < 10; i++) {
    float x = i * 0.1;
}
```

## Complete Examples

### Example 1: Factorial
```c
int n = 5;
int factorial = 1;

for (int i = 1; i <= n; i++) {
    factorial *= i;
}

printf("%d! = %d\n", n, factorial);  // Output: 5! = 120
```

### Example 2: Prime Number Checker
```c
int num = 17;
int is_prime = 1;

if (num < 2) {
    is_prime = 0;
} else {
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            is_prime = 0;
            break;
        }
    }
}

printf("%d is %s\n", num, is_prime ? "prime" : "not prime");
```

### Example 3: Fibonacci Sequence
```c
int n = 10;
int a = 0, b = 1;

printf("Fibonacci sequence: %d %d ", a, b);

for (int i = 3; i <= n; i++) {
    int next = a + b;
    printf("%d ", next);
    a = b;
    b = next;
}
printf("\n");
```

### Example 4: Multiplication Table
```c
int num = 5;

printf("Multiplication table for %d:\n", num);
for (int i = 1; i <= 10; i++) {
    printf("%d x %d = %d\n", num, i, num * i);
}
```

## Exercise

Modify `loops.c` to:
1. Print a pyramid pattern of stars
2. Calculate the sum of all even numbers from 1 to 100
3. Find all perfect numbers between 1 and 1000
4. Implement a guessing game that continues until the user guesses correctly

## Next Steps

- Learn about [Functions](functions.md) to organize repeated code
- Explore [Arrays](arrays.md) which are often used with loops

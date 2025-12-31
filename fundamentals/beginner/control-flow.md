# Control Flow in C

## Concept

Control flow statements allow your program to make decisions and execute different code based on conditions. They control the order in which statements are executed.

## 1. if Statement

Executes code only if a condition is true:

```c
if (condition) {
    // Code executes if condition is true
}
```

**Example:**
```c
int age = 20;

if (age >= 18) {
    printf("You are an adult.\n");
}
```

## 2. if-else Statement

Provides an alternative when condition is false:

```c
if (condition) {
    // Code if condition is true
} else {
    // Code if condition is false
}
```

**Example:**
```c
int score = 75;

if (score >= 60) {
    printf("Pass\n");
} else {
    printf("Fail\n");
}
```

## 3. if-else if-else Ladder

Tests multiple conditions sequentially:

```c
if (condition1) {
    // Code if condition1 is true
} else if (condition2) {
    // Code if condition2 is true
} else if (condition3) {
    // Code if condition3 is true
} else {
    // Code if all conditions are false
}
```

**Example:**
```c
int marks = 85;

if (marks >= 90) {
    printf("Grade: A\n");
} else if (marks >= 80) {
    printf("Grade: B\n");
} else if (marks >= 70) {
    printf("Grade: C\n");
} else if (marks >= 60) {
    printf("Grade: D\n");
} else {
    printf("Grade: F\n");
}
```

## 4. Nested if Statements

An `if` statement inside another `if`:

```c
if (condition1) {
    if (condition2) {
        // Code if both conditions are true
    }
}
```

**Example:**
```c
int age = 25;
int has_license = 1;

if (age >= 18) {
    if (has_license) {
        printf("You can drive\n");
    } else {
        printf("You need a license\n");
    }
} else {
    printf("You are too young to drive\n");
}
```

## 5. switch Statement

Tests a variable against multiple values:

```c
switch (expression) {
    case value1:
        // Code for value1
        break;
    case value2:
        // Code for value2
        break;
    default:
        // Code if no case matches
}
```

**Important:** Use `break` to exit the switch, otherwise execution "falls through" to the next case.

**Example:**
```c
int day = 3;

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
```

### Switch with Fall-Through

Sometimes you want multiple cases to execute the same code:

```c
char grade = 'B';

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
```

## 6. Ternary Operator

A shorthand for simple `if-else` statements:

```c
result = (condition) ? value_if_true : value_if_false;
```

**Example:**
```c
int age = 20;
char *status = (age >= 18) ? "Adult" : "Minor";
printf("%s\n", status);

// Equivalent to:
char *status;
if (age >= 18) {
    status = "Adult";
} else {
    status = "Minor";
}
```

### Nested Ternary (use sparingly)

```c
int score = 75;
char *grade = (score >= 90) ? "A" :
              (score >= 80) ? "B" :
              (score >= 70) ? "C" : "F";
```

## Comparison: if-else vs switch

### Use `if-else` when:
- Testing ranges of values
- Using complex conditions
- Comparing different variables

```c
if (age >= 18 && age < 65) {
    printf("Adult\n");
}
```

### Use `switch` when:
- Testing a single variable against specific values
- You have many possible values to check
- Values are constants (not ranges)

```c
switch (menu_option) {
    case 1: /* ... */ break;
    case 2: /* ... */ break;
    case 3: /* ... */ break;
}
```

## Logical Operators in Conditions

Combine multiple conditions:

### AND (&&)
Both conditions must be true:
```c
if (age >= 18 && has_license) {
    printf("Can drive\n");
}
```

### OR (||)
At least one condition must be true:
```c
if (day == 6 || day == 7) {
    printf("Weekend!\n");
}
```

### NOT (!)
Inverts the condition:
```c
if (!(age < 18)) {
    printf("Adult\n");
}
```

### Combining Operators
```c
if ((age >= 18 && has_license) || is_supervised) {
    printf("Can drive\n");
}
```

## Best Practices

1. **Use braces `{}`** even for single statements (improves readability)
   ```c
   // ✅ Good
   if (x > 0) {
       printf("Positive\n");
   }
   
   // ❌ Avoid
   if (x > 0)
       printf("Positive\n");
   ```

2. **Avoid deep nesting** - Refactor into functions if needed

3. **Use `switch` for multiple specific values** instead of many `if-else`

4. **Put most common cases first** in `if-else` ladders for efficiency

5. **Always include `default` case** in `switch` statements

6. **Don't compare floating-point numbers with `==`**
   ```c
   // ❌ Bad
   if (value == 0.3)
   
   // ✅ Good
   if (fabs(value - 0.3) < 0.0001)
   ```

## Common Pitfalls

⚠️ **Assignment instead of comparison**
```c
if (x = 5)  // ❌ Assigns 5 to x (always true)
if (x == 5) // ✅ Compares x to 5
```

⚠️ **Semicolon after if**
```c
if (x > 0);  // ❌ Empty statement
    printf("Positive\n");  // Always executes!
```

⚠️ **Forgetting break in switch**
```c
switch (day) {
    case 1:
        printf("Monday\n");  // ❌ Falls through to case 2!
    case 2:
        printf("Tuesday\n");
        break;
}
```

⚠️ **Using = instead of == in conditions**
```c
if (x = 10)  // ❌ Assignment, not comparison
if (x == 10) // ✅ Correct
```

⚠️ **Incorrect logical operator precedence**
```c
if (x > 0 && y > 0 || z > 0)  // May not work as expected
if ((x > 0 && y > 0) || z > 0)  // ✅ Clear with parentheses
```

## Complete Example: Grade Calculator

```c
#include <stdio.h>

int main(void) {
    int marks;
    
    printf("Enter your marks (0-100): ");
    scanf("%d", &marks);
    
    // Validate input
    if (marks < 0 || marks > 100) {
        printf("Invalid marks!\n");
        return 1;
    }
    
    // Determine grade
    char grade;
    if (marks >= 90) {
        grade = 'A';
    } else if (marks >= 80) {
        grade = 'B';
    } else if (marks >= 70) {
        grade = 'C';
    } else if (marks >= 60) {
        grade = 'D';
    } else {
        grade = 'F';
    }
    
    // Display result
    printf("Your grade: %c\n", grade);
    
    // Display message based on grade
    switch (grade) {
        case 'A':
            printf("Excellent work!\n");
            break;
        case 'B':
            printf("Good job!\n");
            break;
        case 'C':
            printf("You passed.\n");
            break;
        case 'D':
            printf("Barely passed.\n");
            break;
        case 'F':
            printf("Failed. Better luck next time.\n");
            break;
    }
    
    return 0;
}
```

## Exercise

Modify `control_flow.c` to:
1. Create a simple calculator that uses `switch` for operator selection
2. Implement a leap year checker using nested if statements
3. Create a menu-driven program with multiple options
4. Add input validation for all user inputs

## Next Steps

- Learn about [Loops](loops.md) to repeat code execution
- Explore [Functions](functions.md) to organize control flow logic

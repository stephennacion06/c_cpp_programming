# Beginner Exercises

Practice your C programming skills with these beginner-level exercises. Each exercise includes a description, example input/output, and hints.

## Exercise 1: Simple Calculator

**Difficulty:** ⭐ Easy

**Description:**
Create a calculator that performs basic arithmetic operations (+, -, *, /) based on user input.

**Requirements:**
- Ask user for two numbers
- Ask user for an operation (+, -, *, /)
- Display the result
- Handle division by zero

**Example:**
```
Enter first number: 10
Enter second number: 5
Enter operation (+, -, *, /): +
Result: 10 + 5 = 15
```

**Hints:**
- Use `scanf()` for input
- Use `switch` statement for operations
- Check if divisor is zero before division

---

## Exercise 2: Temperature Converter

**Difficulty:** ⭐ Easy

**Description:**
Convert temperature between Celsius and Fahrenheit.

**Requirements:**
- Ask user to choose conversion type (1 for C→F, 2 for F→C)
- Ask for temperature value
- Display converted temperature

**Formulas:**
- Celsius to Fahrenheit: F = (C × 9/5) + 32
- Fahrenheit to Celsius: C = (F - 32) × 5/9

**Example:**
```
Choose conversion:
1. Celsius to Fahrenheit
2. Fahrenheit to Celsius
Enter choice: 1
Enter temperature in Celsius: 25
25.0°C = 77.0°F
```

---

## Exercise 3: Palindrome Checker

**Difficulty:** ⭐⭐ Medium

**Description:**
Check if a given string is a palindrome (reads the same forwards and backwards).

**Requirements:**
- Read a string from user
- Check if it's a palindrome
- Ignore case (e.g., "Racecar" is a palindrome)

**Example:**
```
Enter a string: racecar
"racecar" is a palindrome!

Enter a string: hello
"hello" is not a palindrome.
```

**Hints:**
- Convert to lowercase before checking
- Compare characters from both ends moving inward

---

## Exercise 4: Prime Number Checker

**Difficulty:** ⭐⭐ Medium

**Description:**
Determine if a number is prime (only divisible by 1 and itself).

**Requirements:**
- Read a number from user
- Check if it's prime
- Display appropriate message

**Example:**
```
Enter a number: 17
17 is a prime number!

Enter a number: 24
24 is not a prime number.
```

**Hints:**
- Numbers less than 2 are not prime
- Only need to check divisors up to √n
- Use modulus operator (%)

---

## Exercise 5: Fibonacci Sequence

**Difficulty:** ⭐⭐ Medium

**Description:**
Generate the first n numbers of the Fibonacci sequence.

**Requirements:**
- Ask user for how many numbers to generate
- Display the sequence
- Handle n ≤ 0

**Example:**
```
How many Fibonacci numbers? 10
0 1 1 2 3 5 8 13 21 34
```

**Hints:**
- First two numbers are 0 and 1
- Each subsequent number is sum of previous two
- Use a loop

---

## Exercise 6: Array Statistics

**Difficulty:** ⭐⭐ Medium

**Description:**
Calculate statistics for an array of numbers.

**Requirements:**
- Ask user for array size
- Read numbers into array
- Calculate and display:
  - Sum
  - Average
  - Maximum
  - Minimum

**Example:**
```
Enter array size: 5
Enter 5 numbers: 10 25 30 15 20
Sum: 100
Average: 20.00
Maximum: 30
Minimum: 10
```

---

## Exercise 7: Grade Calculator

**Difficulty:** ⭐⭐ Medium

**Description:**
Calculate average grade and letter grade for multiple test scores.

**Requirements:**
- Ask for number of tests
- Read test scores
- Calculate average
- Assign letter grade (A: 90-100, B: 80-89, C: 70-79, D: 60-69, F: <60)

**Example:**
```
How many tests? 4
Enter scores: 85 92 78 88
Average: 85.75
Grade: B
```

---

## Exercise 8: Multiplication Table

**Difficulty:** ⭐ Easy

**Description:**
Generate a multiplication table for a given number.

**Requirements:**
- Ask user for a number
- Display multiplication table (1-10)
- Format output neatly

**Example:**
```
Enter a number: 5
5 x 1 = 5
5 x 2 = 10
5 x 3 = 15
...
5 x 10 = 50
```

---

## Exercise 9: Reverse an Array

**Difficulty:** ⭐⭐ Medium

**Description:**
Reverse the elements of an array in place.

**Requirements:**
- Create an array with some initial values
- Reverse the array without creating a new array
- Display original and reversed arrays

**Example:**
```
Original: 1 2 3 4 5
Reversed: 5 4 3 2 1
```

**Hints:**
- Swap elements from both ends moving toward center
- Use temporary variable for swapping

---

## Exercise 10: Guess the Number

**Difficulty:** ⭐⭐ Medium

**Description:**
Create a number guessing game.

**Requirements:**
- Generate random number between 1-100
- Let user guess
- Provide "too high" or "too low" hints
- Count number of guesses
- Game ends when user guesses correctly

**Example:**
```
I'm thinking of a number between 1 and 100.
Guess: 50
Too high!
Guess: 25
Too low!
Guess: 37
Correct! You guessed it in 3 tries.
```

**Hints:**
- Use `rand()` function (include `<stdlib.h>`)
- Seed random generator with `srand(time(NULL))`
- Use a loop until correct guess

---

## Exercise 11: Count Vowels

**Difficulty:** ⭐ Easy

**Description:**
Count the number of vowels in a string.

**Requirements:**
- Read a string from user
- Count vowels (a, e, i, o, u) - case insensitive
- Display the count

**Example:**
```
Enter a string: Hello World
Number of vowels: 3
```

---

## Exercise 12: Bubble Sort

**Difficulty:** ⭐⭐⭐ Hard

**Description:**
Implement the bubble sort algorithm to sort an array.

**Requirements:**
- Create an array of integers
- Sort it using bubble sort
- Display array before and after sorting

**Algorithm:**
- Compare adjacent elements
- Swap if they're in wrong order
- Repeat until array is sorted

**Example:**
```
Before: 64 34 25 12 22 11 90
After:  11 12 22 25 34 64 90
```

**Hints:**
- Use nested loops
- Outer loop: number of passes
- Inner loop: compare and swap

---

## Exercise 13: Factorial Calculator

**Difficulty:** ⭐ Easy

**Description:**
Calculate the factorial of a number (both iteratively and recursively).

**Requirements:**
- Read a number from user
- Calculate factorial
- Handle n = 0 (0! = 1)
- Implement both iterative and recursive versions

**Example:**
```
Enter a number: 5
5! = 120
```

**Formula:** n! = n × (n-1) × (n-2) × ... × 1

---

## Exercise 14: String Manipulation

**Difficulty:** ⭐⭐ Medium

**Description:**
Create a program with multiple string operations.

**Requirements:**
Implement functions to:
- Convert string to uppercase
- Convert string to lowercase
- Count words in a string
- Remove spaces from a string

**Example:**
```
Enter a string: Hello World
Uppercase: HELLO WORLD
Lowercase: hello world
Word count: 2
No spaces: HelloWorld
```

---

## Exercise 15: Matrix Operations

**Difficulty:** ⭐⭐⭐ Hard

**Description:**
Perform operations on 2D arrays (matrices).

**Requirements:**
- Create two 3x3 matrices
- Implement matrix addition
- Implement matrix multiplication
- Display results

**Example:**
```
Matrix A:
1 2 3
4 5 6
7 8 9

Matrix B:
9 8 7
6 5 4
3 2 1

A + B:
10 10 10
10 10 10
10 10 10
```

---

## Solutions

Solutions to these exercises will be added in the `solutions/` directory. Try to solve them yourself first!

## Tips for Success

1. **Read the requirements carefully** - Make sure you understand what's being asked
2. **Plan before coding** - Write pseudocode or draw flowcharts
3. **Test with different inputs** - Try edge cases
4. **Debug systematically** - Use printf() to check intermediate values
5. **Refactor** - Improve your code after it works
6. **Compare solutions** - Learn from different approaches

## Next Steps

Once you're comfortable with these exercises:
- Move to [Intermediate Exercises](../../exercises/intermediate/README.md)
- Explore [Data Structures](../../data-structures/beginner/README.md)
- Try [Small Projects](../../projects/beginner/README.md)

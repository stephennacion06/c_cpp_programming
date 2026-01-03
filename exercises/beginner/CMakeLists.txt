# CMakeLists.txt for Beginner Exercises

# Exercise 1: Simple Calculator
add_executable(ex01_calculator ex01_calculator.c)

# Exercise 2: Temperature Converter
add_executable(ex02_temperature ex02_temperature.c)

# Exercise 3: Prime Number Checker
add_executable(ex03_prime_checker ex03_prime_checker.c)

# Exercise 4: Factorial Calculator
add_executable(ex04_factorial ex04_factorial.c)

# Exercise 5: Fibonacci Sequence
add_executable(ex05_fibonacci ex05_fibonacci.c)

# Exercise 6: Array Max/Min
add_executable(ex06_array_max_min ex06_array_max_min.c)

# Exercise 7: Reverse Array
add_executable(ex07_reverse_array ex07_reverse_array.c)

# Exercise 8: Vowel Counter
add_executable(ex08_vowel_counter ex08_vowel_counter.c)

# Exercise 9: Sum of Digits
add_executable(ex09_sum_digits ex09_sum_digits.c)

# Exercise 10: Multiplication Table
add_executable(ex10_multiplication_table ex10_multiplication_table.c)

# Set output directory for all exercises
set_target_properties(
    ex01_calculator
    ex02_temperature
    ex03_prime_checker
    ex04_factorial
    ex05_fibonacci
    ex06_array_max_min
    ex07_reverse_array
    ex08_vowel_counter
    ex09_sum_digits
    ex10_multiplication_table
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/exercises/beginner/$<CONFIG>"
)

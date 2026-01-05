# Intermediate C Programming Exercises

This directory contains intermediate-level programming exercises designed to reinforce:
- Dynamic memory allocation
- File I/O operations
- Pointers and structures
- String manipulation
- Data structures implementation
- Algorithm development

## Exercise List

### Memory Management
1. **ex01_dynamic_array.c** - Dynamic array with resize capability
2. **ex02_linked_list.c** - Basic singly linked list implementation

### File Processing
3. **ex03_file_copy.c** - File copy utility with error handling
4. **ex04_csv_parser.c** - Parse and process CSV files

### String Processing
5. **ex05_word_frequency.c** - Count word frequencies in text

### Data Structures
6. **ex06_stack.c** - Stack implementation using dynamic array
7. **ex07_queue.c** - Queue implementation using linked list

### Algorithms
8. **ex08_merge_sort.c** - Merge sort implementation
9. **ex09_binary_search_tree.c** - Basic BST operations

### Mixed Concepts
10. **ex10_contact_manager.c** - Contact management with file persistence

## Learning Objectives

After completing these exercises, you should be able to:
- Allocate and manage dynamic memory safely
- Handle file operations with proper error checking
- Implement common data structures from scratch
- Apply algorithms to real-world problems
- Write maintainable, well-structured code

## How to Use

1. Read the problem description in each file
2. Implement the required functions
3. Compile: `gcc -Wall -Wextra -std=c11 -o exercise exercise.c`
4. Test your implementation
5. Compare with provided solution (if available)

## Compilation Notes

All exercises should compile with:
```bash
gcc -Wall -Wextra -std=c11 -pedantic -O2 -o output file.c
```

For exercises requiring math library:
```bash
gcc -Wall -Wextra -std=c11 -o output file.c -lm
```

## Tips

- Always check return values from functions
- Free all allocated memory
- Handle edge cases (NULL pointers, empty inputs)
- Use valgrind to check for memory leaks
- Write clean, documented code

## Resources

- [C Reference](https://en.cppreference.com/w/c)
- [Memory Management Guide](../../memory-management/)
- [Data Structures Guide](../../data-structures/)

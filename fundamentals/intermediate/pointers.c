/**
 * Pointers - Fundamentals
 * 
 * Demonstrates essential pointer concepts in C:
 * - Pointer declaration and initialization
 * - Dereferencing and address-of operators
 * - Pointer arithmetic
 * - Pointers and arrays
 * - Pointer to pointer (double pointers)
 * - Common pitfalls and best practices
 * 
 * Memory Addresses: Every variable has an address in memory
 * Pointers: Variables that store memory addresses
 * 
 * Why Pointers Matter:
 * - Dynamic memory allocation
 * - Efficient array/string manipulation
 * - Pass by reference in functions
 * - Data structures (linked lists, trees, graphs)
 * - System programming and hardware access
 */

#include <stdio.h>
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Function declarations
void demonstrate_basics(void);
void demonstrate_arithmetic(void);
void demonstrate_arrays(void);
void demonstrate_double_pointers(void);
void demonstrate_function_pointers(void);
void swap_by_value(int a, int b);
void swap_by_pointer(int* a, int* b);

int main(void) {
#ifdef _WIN32
    // Enable UTF-8 output on Windows console
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IOFBF, 1000);
#endif

    printf("========================================\n");
    printf("       POINTERS FUNDAMENTALS           \n");
    printf("========================================\n\n");

    demonstrate_basics();
    demonstrate_arithmetic();
    demonstrate_arrays();
    demonstrate_double_pointers();
    demonstrate_function_pointers();

    printf("========================================\n");
    printf("     ALL DEMONSTRATIONS COMPLETED      \n");
    printf("========================================\n");

    return 0;
}

/**
 * Pointer Basics
 * Demonstrates pointer declaration, initialization, and dereferencing
 */
void demonstrate_basics(void) {
    printf("========================================\n");
    printf("1. POINTER BASICS\n");
    printf("========================================\n\n");

    // Variable and pointer declaration
    int value = 42;
    int* ptr = &value;  // ptr stores address of value

    printf("Direct Access:\n");
    printf("  value = %d\n", value);
    printf("  Address of value = %p\n\n", (void*)&value);

    printf("Pointer Access:\n");
    printf("  ptr = %p (address stored in ptr)\n", (void*)ptr);
    printf("  *ptr = %d (value at that address)\n", *ptr);
    printf("  Address of ptr itself = %p\n\n", (void*)&ptr);

    // Modifying through pointer
    *ptr = 100;
    printf("After '*ptr = 100':\n");
    printf("  value = %d\n", value);
    printf("  *ptr = %d\n\n", *ptr);

    // NULL pointer (best practice)
    int* null_ptr = NULL;
    printf("NULL Pointer:\n");
    printf("  null_ptr = %p\n", (void*)null_ptr);
    printf("  Always check before dereferencing!\n");
    if (null_ptr != NULL) {
        printf("  *null_ptr = %d\n", *null_ptr);
    } else {
        printf("  ✓ Avoided NULL dereference\n");
    }

    // Pointer size (architecture dependent)
    printf("\nPointer Size:\n");
    printf("  sizeof(int*) = %zu bytes\n", sizeof(int*));
    printf("  sizeof(char*) = %zu bytes\n", sizeof(char*));
    printf("  sizeof(double*) = %zu bytes\n\n", sizeof(double*));
}

/**
 * Pointer Arithmetic
 * Demonstrates how pointers move through memory
 */
void demonstrate_arithmetic(void) {
    printf("========================================\n");
    printf("2. POINTER ARITHMETIC\n");
    printf("========================================\n\n");

    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr;  // Points to first element

    printf("Array: [");
    for (int i = 0; i < 5; i++) {
        printf("%d%s", arr[i], i < 4 ? ", " : "");
    }
    printf("]\n\n");

    printf("Pointer Arithmetic (int = %zu bytes):\n", sizeof(int));
    for (int i = 0; i < 5; i++) {
        printf("  ptr + %d: address = %p, value = %d\n", 
               i, (void*)(ptr + i), *(ptr + i));
    }

    printf("\nIncrementing Pointer:\n");
    ptr = arr;  // Reset to start
    printf("  Initial: ptr = %p, *ptr = %d\n", (void*)ptr, *ptr);
    ptr++;
    printf("  After ptr++: ptr = %p, *ptr = %d\n", (void*)ptr, *ptr);
    ptr += 2;
    printf("  After ptr += 2: ptr = %p, *ptr = %d\n\n", (void*)ptr, *ptr);

    // Pointer subtraction
    int* ptr1 = &arr[4];
    int* ptr2 = &arr[0];
    printf("Pointer Subtraction:\n");
    printf("  ptr1 - ptr2 = %td (elements apart)\n\n", ptr1 - ptr2);
}

/**
 * Pointers and Arrays
 * Demonstrates the relationship between pointers and arrays
 */
void demonstrate_arrays(void) {
    printf("========================================\n");
    printf("3. POINTERS AND ARRAYS\n");
    printf("========================================\n\n");

    int numbers[] = {100, 200, 300, 400, 500};

    printf("Array Name as Pointer:\n");
    printf("  numbers = %p\n", (void*)numbers);
    printf("  &numbers[0] = %p\n", (void*)&numbers[0]);
    printf("  ✓ They're the same!\n\n");

    printf("Two Ways to Access Elements:\n");
    for (int i = 0; i < 5; i++) {
        printf("  numbers[%d] = %d  |  *(numbers + %d) = %d\n",
               i, numbers[i], i, *(numbers + i));
    }

    printf("\nUsing Pointer to Traverse Array:\n");
    int* ptr = numbers;
    for (int i = 0; i < 5; i++) {
        printf("  Element %d: %d\n", i, *ptr);
        ptr++;
    }

    // String as character pointer
    printf("\nString Pointers:\n");
    char* message = "Hello, Pointers!";  // Points to string literal
    printf("  message = \"%s\"\n", message);
    printf("  First char: message[0] = '%c', *message = '%c'\n\n", 
           message[0], *message);
}

/**
 * Swap functions demonstrating pass-by-value vs pass-by-pointer
 */
void swap_by_value(int a, int b) {
    printf("    Inside swap_by_value: ");
    int temp = a;
    a = b;
    b = temp;
    printf("a = %d, b = %d\n", a, b);
}

void swap_by_pointer(int* a, int* b) {
    printf("    Inside swap_by_pointer: ");
    int temp = *a;
    *a = *b;
    *b = temp;
    printf("*a = %d, *b = %d\n", *a, *b);
}

/**
 * Double Pointers (Pointer to Pointer)
 * Demonstrates multi-level indirection
 */
void demonstrate_double_pointers(void) {
    printf("========================================\n");
    printf("4. POINTER TO POINTER\n");
    printf("========================================\n\n");

    int value = 99;
    int* ptr = &value;
    int** ptr_to_ptr = &ptr;

    printf("Multi-level Indirection:\n");
    printf("  value = %d\n", value);
    printf("  ptr points to value: *ptr = %d\n", *ptr);
    printf("  ptr_to_ptr points to ptr: **ptr_to_ptr = %d\n\n", **ptr_to_ptr);

    // Modify through double pointer
    **ptr_to_ptr = 777;
    printf("After '**ptr_to_ptr = 777':\n");
    printf("  value = %d\n", value);
    printf("  *ptr = %d\n", *ptr);
    printf("  **ptr_to_ptr = %d\n\n", **ptr_to_ptr);

    // Common use: modifying pointer in function
    printf("Swap Function Demonstration:\n");
    int x = 10, y = 20;
    printf("  Before swap_by_value: x = %d, y = %d\n", x, y);
    swap_by_value(x, y);
    printf("    After swap_by_value:  x = %d, y = %d ✗ No change\n\n", x, y);

    printf("  Before swap_by_pointer: x = %d, y = %d\n", x, y);
    swap_by_pointer(&x, &y);
    printf("    After swap_by_pointer:  x = %d, y = %d ✓ Swapped!\n\n", x, y);
}

// Helper functions for function pointer demonstration
static int add_func(int a, int b) { return a + b; }
static int subtract_func(int a, int b) { return a - b; }
static int multiply_func(int a, int b) { return a * b; }

/**
 * Function Pointers
 * Demonstrates function pointers for callbacks and dynamic behavior
 */
void demonstrate_function_pointers(void) {
    printf("========================================\n");
    printf("5. FUNCTION POINTERS\n");
    printf("========================================\n\n");

    // Function pointers for operations
    int (*operation)(int, int);

    printf("Function Pointers for Dynamic Behavior:\n");
    
    operation = add_func;
    printf("  operation(5, 3) with add = %d\n", operation(5, 3));

    operation = subtract_func;
    printf("  operation(5, 3) with subtract = %d\n", operation(5, 3));

    operation = multiply_func;
    printf("  operation(5, 3) with multiply = %d\n\n", operation(5, 3));

    printf("Use Cases:\n");
    printf("  • Callbacks in event systems\n");
    printf("  • Strategy pattern implementation\n");
    printf("  • Sorting with custom comparators\n");
    printf("  • Dispatch tables/state machines\n\n");
}

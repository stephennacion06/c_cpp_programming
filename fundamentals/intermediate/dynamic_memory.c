/**
 * dynamic_memory.c
 * 
 * Demonstrates dynamic memory allocation in C.
 * Topics covered:
 * - malloc() - allocate uninitialized memory
 * - calloc() - allocate zero-initialized memory
 * - realloc() - resize previously allocated memory
 * - free() - deallocate memory
 * - Memory leak prevention
 * - Error handling for allocation failures
 * 
 * Memory Implications:
 * - Dynamic allocation happens on the heap (not stack)
 * - Heap memory persists until explicitly freed
 * - malloc/calloc have O(1) average time complexity
 * - realloc may require O(n) copy if buffer can't grow in place
 * - Always check for NULL after allocation (out-of-memory condition)
 * 
 * RAII Pattern in C:
 * While C doesn't have RAII destructors, we demonstrate:
 * - Single exit point pattern for cleanup
 * - goto-based error handling (common in kernel code)
 * - Proper resource cleanup on all paths
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Windows UTF-8 console setup */
#ifdef _WIN32
#include <windows.h>
void setup_utf8_console(void) {
    SetConsoleOutputCP(CP_UTF8);
}
#else
void setup_utf8_console(void) {}
#endif

/**
 * Example 1: Basic malloc usage
 * malloc() allocates raw bytes without initialization
 */
void example_malloc(void) {
    printf("\n=== Example 1: malloc() ===\n");
    
    /* Allocate memory for 5 integers */
    int *arr = (int*)malloc(5 * sizeof(int));
    
    /* Always check if allocation succeeded */
    if (arr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return;
    }
    
    /* Initialize and use the memory */
    printf("Allocated array of 5 integers:\n");
    for (int i = 0; i < 5; i++) {
        arr[i] = (i + 1) * 10;
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    /* CRITICAL: Always free allocated memory */
    free(arr);
    arr = NULL; /* Best practice: nullify pointer after free */
    
    printf("Memory freed successfully.\n");
}

/**
 * Example 2: calloc usage
 * calloc() allocates AND zero-initializes memory
 * Slightly slower than malloc but safer for certain use cases
 */
void example_calloc(void) {
    printf("\n=== Example 2: calloc() ===\n");
    
    /* Allocate memory for 5 integers, all initialized to 0 */
    int *arr = (int*)calloc(5, sizeof(int));
    
    if (arr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return;
    }
    
    /* calloc guarantees zero-initialization */
    printf("Allocated and zero-initialized array:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d (zero-initialized)\n", i, arr[i]);
    }
    
    free(arr);
    arr = NULL;
    
    printf("Memory freed successfully.\n");
}

/**
 * Example 3: realloc usage
 * realloc() resizes previously allocated memory
 * - May reuse the same block if space available
 * - May allocate new block and copy data if needed
 */
void example_realloc(void) {
    printf("\n=== Example 3: realloc() ===\n");
    
    /* Initial allocation */
    int *arr = (int*)malloc(3 * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Error: Initial allocation failed\n");
        return;
    }
    
    /* Initialize initial array */
    for (int i = 0; i < 3; i++) {
        arr[i] = i + 1;
    }
    
    printf("Initial array (3 elements):\n");
    for (int i = 0; i < 3; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    /* Resize to hold 6 integers */
    int *temp = (int*)realloc(arr, 6 * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Error: Reallocation failed\n");
        free(arr); /* Original memory still valid, must free */
        return;
    }
    
    /* realloc succeeded, update pointer */
    arr = temp;
    
    /* Initialize new elements */
    for (int i = 3; i < 6; i++) {
        arr[i] = i + 1;
    }
    
    printf("\nResized array (6 elements):\n");
    for (int i = 0; i < 6; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    free(arr);
    arr = NULL;
    
    printf("Memory freed successfully.\n");
}

/**
 * Example 4: Dynamic string allocation
 * Practical example with error handling
 */
void example_dynamic_string(void) {
    printf("\n=== Example 4: Dynamic String ===\n");
    
    const char *source = "Hello, Dynamic Memory!";
    size_t length = strlen(source);
    
    /* Allocate memory for string (+1 for null terminator) */
    char *dynamic_str = (char*)malloc((length + 1) * sizeof(char));
    
    if (dynamic_str == NULL) {
        fprintf(stderr, "Error: String allocation failed\n");
        return;
    }
    
    /* Copy string to allocated memory */
    strcpy(dynamic_str, source);
    
    printf("Original: %s\n", source);
    printf("Dynamic:  %s\n", dynamic_str);
    printf("Length:   %zu bytes\n", length);
    
    free(dynamic_str);
    dynamic_str = NULL;
    
    printf("String memory freed.\n");
}

/**
 * Example 5: 2D array allocation
 * Demonstrates contiguous vs. array-of-pointers allocation
 */
void example_2d_array(void) {
    printf("\n=== Example 5: 2D Array Allocation ===\n");
    
    int rows = 3;
    int cols = 4;
    
    /* Method 1: Allocate array of pointers (non-contiguous) */
    int **matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        fprintf(stderr, "Error: Matrix allocation failed\n");
        return;
    }
    
    /* Allocate each row */
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Error: Row %d allocation failed\n", i);
            /* Cleanup already allocated rows */
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return;
        }
    }
    
    /* Initialize matrix */
    printf("Allocated %dx%d matrix:\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    /* Free all allocated memory (reverse order) */
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    matrix = NULL;
    
    printf("Matrix memory freed.\n");
}

/**
 * Example 6: Memory leak demonstration (what NOT to do)
 * Educational example showing common mistakes
 */
void example_memory_leak_warning(void) {
    printf("\n=== Example 6: Memory Leak Prevention ===\n");
    
    printf("Common mistakes to avoid:\n\n");
    
    /* Mistake 1: Losing pointer without freeing */
    printf("1. DON'T lose pointer before freeing:\n");
    printf("   int *ptr = malloc(100);\n");
    printf("   ptr = NULL; // LEAK! Memory lost forever\n\n");
    
    /* Mistake 2: Freeing stack memory */
    printf("2. DON'T free stack-allocated memory:\n");
    printf("   int x = 10;\n");
    printf("   free(&x); // UNDEFINED BEHAVIOR!\n\n");
    
    /* Mistake 3: Double free */
    printf("3. DON'T free the same memory twice:\n");
    printf("   int *ptr = malloc(100);\n");
    printf("   free(ptr);\n");
    printf("   free(ptr); // UNDEFINED BEHAVIOR!\n\n");
    
    /* Mistake 4: Use after free */
    printf("4. DON'T use memory after freeing:\n");
    printf("   int *ptr = malloc(100);\n");
    printf("   free(ptr);\n");
    printf("   *ptr = 10; // UNDEFINED BEHAVIOR!\n\n");
    
    printf("Always:\n");
    printf("- Check for NULL after allocation\n");
    printf("- Free every malloc/calloc/realloc\n");
    printf("- Set pointers to NULL after free\n");
    printf("- Use tools like valgrind to detect leaks\n");
}

/**
 * Example 7: Proper error handling pattern (goto-based cleanup)
 * This pattern is common in Linux kernel and system programming
 */
int example_proper_cleanup(void) {
    printf("\n=== Example 7: Proper Cleanup Pattern ===\n");
    
    int *buffer1 = NULL;
    int *buffer2 = NULL;
    int *buffer3 = NULL;
    int result = 0;
    
    /* First allocation */
    buffer1 = (int*)malloc(100 * sizeof(int));
    if (buffer1 == NULL) {
        fprintf(stderr, "Error: buffer1 allocation failed\n");
        result = -1;
        goto cleanup;
    }
    printf("Allocated buffer1\n");
    
    /* Second allocation */
    buffer2 = (int*)malloc(200 * sizeof(int));
    if (buffer2 == NULL) {
        fprintf(stderr, "Error: buffer2 allocation failed\n");
        result = -1;
        goto cleanup;
    }
    printf("Allocated buffer2\n");
    
    /* Third allocation */
    buffer3 = (int*)malloc(300 * sizeof(int));
    if (buffer3 == NULL) {
        fprintf(stderr, "Error: buffer3 allocation failed\n");
        result = -1;
        goto cleanup;
    }
    printf("Allocated buffer3\n");
    
    /* Simulate work */
    printf("Performing operations with allocated buffers...\n");
    buffer1[0] = 42;
    buffer2[0] = 100;
    buffer3[0] = 200;
    
    printf("Work completed successfully.\n");
    result = 0;
    
cleanup:
    /* Single cleanup point - frees only what was allocated */
    if (buffer3 != NULL) {
        free(buffer3);
        printf("Freed buffer3\n");
    }
    if (buffer2 != NULL) {
        free(buffer2);
        printf("Freed buffer2\n");
    }
    if (buffer1 != NULL) {
        free(buffer1);
        printf("Freed buffer1\n");
    }
    
    return result;
}

/**
 * Main function demonstrating all examples
 */
int main(void) {
    setup_utf8_console();
    
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║        Dynamic Memory Allocation in C                      ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    printf("\nMemory Allocation Functions:\n");
    printf("- malloc(size)       : Allocate uninitialized memory\n");
    printf("- calloc(n, size)    : Allocate zero-initialized memory\n");
    printf("- realloc(ptr, size) : Resize allocated memory\n");
    printf("- free(ptr)          : Deallocate memory\n");
    
    printf("\nCPU & Memory Overhead:\n");
    printf("- malloc/calloc/free: O(1) average, may be O(log n) worst case\n");
    printf("- realloc: O(1) if expanded in place, O(n) if moved\n");
    printf("- calloc: ~20%% slower than malloc due to zeroing\n");
    printf("- Heap allocation: ~100-300 CPU cycles typical\n");
    printf("- Stack allocation: ~1-5 CPU cycles typical\n");
    
    /* Run all examples */
    example_malloc();
    example_calloc();
    example_realloc();
    example_dynamic_string();
    example_2d_array();
    example_memory_leak_warning();
    example_proper_cleanup();
    
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║ Key Takeaways:                                             ║\n");
    printf("║ 1. Always check for NULL after allocation                 ║\n");
    printf("║ 2. Always free what you allocate (no leaks)               ║\n");
    printf("║ 3. Never use memory after freeing it                      ║\n");
    printf("║ 4. Never free the same memory twice                       ║\n");
    printf("║ 5. Set pointers to NULL after freeing                     ║\n");
    printf("║ 6. Use valgrind to detect memory errors                   ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    return 0;
}

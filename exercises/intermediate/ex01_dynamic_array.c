/**
 * ex01_dynamic_array.c
 * 
 * Exercise: Implement a dynamic array that can grow and shrink.
 * 
 * Requirements:
 * 1. Create a structure to hold array data, size, and capacity
 * 2. Implement functions:
 *    - create_array() - Initialize with given capacity
 *    - append() - Add element, resize if needed
 *    - insert() - Insert at specific index
 *    - delete() - Remove element at index
 *    - get() - Get element at index
 *    - destroy() - Free all memory
 * 3. Use proper error handling
 * 4. Resize strategy: double capacity when full, halve when 1/4 full
 * 
 * Memory Implications:
 * - realloc() may copy entire array: O(n) worst case
 * - Doubling strategy amortizes to O(1) per insertion
 * - Memory overhead: unused capacity space
 * 
 * Learning objectives:
 * - Dynamic memory management
 * - Amortized analysis
 * - Structure encapsulation
 * - Memory reallocation strategies
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
 * Dynamic array structure
 */
typedef struct {
    int *data;      /* Pointer to array data */
    size_t size;    /* Number of elements currently in array */
    size_t capacity; /* Total allocated capacity */
} DynamicArray;

/**
 * Create and initialize a dynamic array
 * Time complexity: O(1)
 * Space complexity: O(capacity)
 */
DynamicArray* create_array(size_t initial_capacity) {
    DynamicArray *arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (arr == NULL) {
        return NULL;
    }
    
    arr->data = (int*)malloc(initial_capacity * sizeof(int));
    if (arr->data == NULL) {
        free(arr);
        return NULL;
    }
    
    arr->size = 0;
    arr->capacity = initial_capacity;
    
    return arr;
}

/**
 * Resize the array (internal helper function)
 * Time complexity: O(n) - must copy all elements
 */
static bool resize_array(DynamicArray *arr, size_t new_capacity) {
    if (arr == NULL || new_capacity < arr->size) {
        return false;
    }
    
    int *new_data = (int*)realloc(arr->data, new_capacity * sizeof(int));
    if (new_data == NULL) {
        return false;
    }
    
    arr->data = new_data;
    arr->capacity = new_capacity;
    
    return true;
}

/**
 * Append element to end of array
 * Time complexity: O(1) amortized, O(n) worst case
 */
bool append(DynamicArray *arr, int value) {
    if (arr == NULL) {
        return false;
    }
    
    /* Resize if at capacity */
    if (arr->size >= arr->capacity) {
        size_t new_capacity = arr->capacity * 2;
        if (!resize_array(arr, new_capacity)) {
            return false;
        }
    }
    
    arr->data[arr->size++] = value;
    return true;
}

/**
 * Insert element at specific index
 * Time complexity: O(n) - must shift elements
 */
bool insert(DynamicArray *arr, size_t index, int value) {
    if (arr == NULL || index > arr->size) {
        return false;
    }
    
    /* Resize if needed */
    if (arr->size >= arr->capacity) {
        size_t new_capacity = arr->capacity * 2;
        if (!resize_array(arr, new_capacity)) {
            return false;
        }
    }
    
    /* Shift elements right */
    for (size_t i = arr->size; i > index; i--) {
        arr->data[i] = arr->data[i - 1];
    }
    
    arr->data[index] = value;
    arr->size++;
    
    return true;
}

/**
 * Delete element at specific index
 * Time complexity: O(n) - must shift elements
 */
bool delete(DynamicArray *arr, size_t index) {
    if (arr == NULL || index >= arr->size) {
        return false;
    }
    
    /* Shift elements left */
    for (size_t i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    
    arr->size--;
    
    /* Shrink if using less than 1/4 capacity and capacity > 4 */
    if (arr->capacity > 4 && arr->size < arr->capacity / 4) {
        resize_array(arr, arr->capacity / 2);
    }
    
    return true;
}

/**
 * Get element at specific index
 * Time complexity: O(1)
 */
bool get(const DynamicArray *arr, size_t index, int *value) {
    if (arr == NULL || index >= arr->size || value == NULL) {
        return false;
    }
    
    *value = arr->data[index];
    return true;
}

/**
 * Print array contents
 */
void print_array(const DynamicArray *arr) {
    if (arr == NULL) {
        printf("NULL array\n");
        return;
    }
    
    printf("Array[size=%zu, capacity=%zu]: [", arr->size, arr->capacity);
    for (size_t i = 0; i < arr->size; i++) {
        printf("%d", arr->data[i]);
        if (i < arr->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

/**
 * Destroy array and free memory
 * Time complexity: O(1)
 */
void destroy_array(DynamicArray *arr) {
    if (arr != NULL) {
        free(arr->data);
        free(arr);
    }
}

/**
 * Main function with test cases
 */
int main(void) {
    setup_utf8_console();
    
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║        Dynamic Array Implementation                        ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    /* Create array with initial capacity of 2 */
    DynamicArray *arr = create_array(2);
    if (arr == NULL) {
        fprintf(stderr, "Failed to create array\n");
        return 1;
    }
    
    printf("\n1. Created array with capacity 2\n");
    print_array(arr);
    
    /* Test append - should trigger resize */
    printf("\n2. Appending elements 10, 20, 30, 40, 50\n");
    append(arr, 10);
    print_array(arr);
    
    append(arr, 20);
    print_array(arr);
    
    append(arr, 30);
    printf("   (Resize triggered! Capacity doubled)\n");
    print_array(arr);
    
    append(arr, 40);
    print_array(arr);
    
    append(arr, 50);
    printf("   (Resize triggered! Capacity doubled)\n");
    print_array(arr);
    
    /* Test insert */
    printf("\n3. Inserting 25 at index 2\n");
    insert(arr, 2, 25);
    print_array(arr);
    
    /* Test get */
    printf("\n4. Getting element at index 3\n");
    int value;
    if (get(arr, 3, &value)) {
        printf("   arr[3] = %d\n", value);
    }
    
    /* Test delete - should trigger shrink */
    printf("\n5. Deleting elements to trigger shrink\n");
    delete(arr, 0);
    print_array(arr);
    
    delete(arr, 0);
    print_array(arr);
    
    delete(arr, 0);
    print_array(arr);
    
    delete(arr, 0);
    printf("   (Shrink triggered! Capacity halved)\n");
    print_array(arr);
    
    /* Clean up */
    destroy_array(arr);
    printf("\n6. Array destroyed, memory freed\n");
    
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║ Performance Analysis:                                      ║\n");
    printf("║ - Append: O(1) amortized                                   ║\n");
    printf("║ - Insert: O(n) due to shifting                             ║\n");
    printf("║ - Delete: O(n) due to shifting                             ║\n");
    printf("║ - Get: O(1) direct access                                  ║\n");
    printf("║ - Space: O(n) with some overhead                           ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    return 0;
}

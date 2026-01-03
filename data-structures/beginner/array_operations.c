/**
 * Array Operations
 * 
 * Demonstrates common array operations:
 * - Insertion, deletion, search
 * - Reversal, rotation
 * - Finding min/max
 * - Merging arrays
 * 
 * Time Complexity:
 * - Access: O(1)
 * - Insert/Delete: O(n)
 * - Search: O(n)
 * - Reverse: O(n)
 * - Rotate: O(n)
 */

#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_SIZE 100

// Function declarations
void print_array(int arr[], int size);
int insert_element(int arr[], int size, int element, int position);
int delete_element(int arr[], int size, int position);
int linear_search(int arr[], int size, int target);
void reverse_array(int arr[], int size);
void rotate_left(int arr[], int size, int positions);
void rotate_right(int arr[], int size, int positions);
int find_max(int arr[], int size);
int find_min(int arr[], int size);
void merge_arrays(int arr1[], int size1, int arr2[], int size2, int result[]);

int main(void) {
#ifdef _WIN32
    // Enable UTF-8 output on Windows console
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IOFBF, 1000);
#endif

    printf("========================================\n");
    printf("     ARRAY OPERATIONS DEMONSTRATION     \n");
    printf("========================================\n\n");
    
    // Initialize array
    int arr[MAX_SIZE] = {10, 20, 30, 40, 50};
    int size = 5;
    
    // 1. Display initial array
    printf("1. INITIAL ARRAY\n");
    printf("   ");
    print_array(arr, size);
    printf("\n");
    
    // 2. Insert element
    printf("2. INSERT ELEMENT\n");
    printf("   Inserting 25 at position 2...\n");
    size = insert_element(arr, size, 25, 2);
    printf("   Result: ");
    print_array(arr, size);
    printf("\n");
    
    // 3. Search for element
    printf("3. LINEAR SEARCH\n");
    int target = 30;
    printf("   Searching for %d...\n", target);
    int index = linear_search(arr, size, target);
    if (index != -1) {
        printf("   ✓ Found at index: %d\n", index);
    } else {
        printf("   ✗ Not found\n");
    }
    
    target = 99;
    printf("   Searching for %d...\n", target);
    index = linear_search(arr, size, target);
    if (index != -1) {
        printf("   ✓ Found at index: %d\n", index);
    } else {
        printf("   ✗ Not found\n");
    }
    printf("\n");
    
    // 4. Find min and max
    printf("4. FIND MIN AND MAX\n");
    printf("   Current array: ");
    print_array(arr, size);
    printf("   Minimum: %d\n", find_min(arr, size));
    printf("   Maximum: %d\n", find_max(arr, size));
    printf("\n");
    
    // 5. Reverse array
    printf("5. REVERSE ARRAY\n");
    printf("   Before: ");
    print_array(arr, size);
    reverse_array(arr, size);
    printf("   After:  ");
    print_array(arr, size);
    printf("\n");
    
    // 6. Rotate array left
    printf("6. ROTATE LEFT\n");
    printf("   Before rotation (2 positions): ");
    print_array(arr, size);
    rotate_left(arr, size, 2);
    printf("   After rotation:                ");
    print_array(arr, size);
    printf("\n");
    
    // 7. Rotate array right
    printf("7. ROTATE RIGHT\n");
    printf("   Before rotation (3 positions): ");
    print_array(arr, size);
    rotate_right(arr, size, 3);
    printf("   After rotation:                ");
    print_array(arr, size);
    printf("\n");
    
    // 8. Delete element
    printf("8. DELETE ELEMENT\n");
    printf("   Before deletion (position 3): ");
    print_array(arr, size);
    size = delete_element(arr, size, 3);
    printf("   After deletion:               ");
    print_array(arr, size);
    printf("\n");
    
    // 9. Merge arrays
    printf("9. MERGE ARRAYS\n");
    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8};
    int size1 = 4, size2 = 4;
    int merged[MAX_SIZE];
    
    printf("   Array 1: ");
    print_array(arr1, size1);
    printf("   Array 2: ");
    print_array(arr2, size2);
    
    merge_arrays(arr1, size1, arr2, size2, merged);
    printf("   Merged:  ");
    print_array(merged, size1 + size2);
    printf("\n");
    
    printf("========================================\n");
    printf("     OPERATIONS COMPLETED SUCCESSFULLY  \n");
    printf("========================================\n");
    
    return 0;
}

/**
 * Print array elements
 */
void print_array(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("] (size: %d)\n", size);
}

/**
 * Insert element at specified position
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
int insert_element(int arr[], int size, int element, int position) {
    // Validate position
    if (position < 0 || position > size) {
        printf("   Error: Invalid position %d (valid range: 0-%d)\n", position, size);
        return size;
    }
    
    if (size >= MAX_SIZE) {
        printf("   Error: Array is full\n");
        return size;
    }
    
    // Shift elements to the right
    for (int i = size; i > position; i--) {
        arr[i] = arr[i - 1];
    }
    
    // Insert new element
    arr[position] = element;
    return size + 1;
}

/**
 * Delete element at specified position
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
int delete_element(int arr[], int size, int position) {
    // Validate position
    if (position < 0 || position >= size) {
        printf("   Error: Invalid position %d (valid range: 0-%d)\n", position, size - 1);
        return size;
    }
    
    // Shift elements to the left
    for (int i = position; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    
    return size - 1;
}

/**
 * Linear search for target element
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
int linear_search(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1; // Not found
}

/** * Helper function to reverse a subarray from start to end indices
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
static void reverse_subarray(int arr[], int start, int end) {
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

/** * Reverse array in-place
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
void reverse_array(int arr[], int size) {
    int left = 0;
    int right = size - 1;
    
    while (left < right) {
        // Swap elements
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        
        left++;
        right--;
    }
}

/**
 * Rotate array left by specified positions
 * Time Complexity: O(n)
 * Space Complexity: O(k) where k is positions
 */
void rotate_left(int arr[], int size, int positions) {
    if (size == 0) return;
    
    // Handle positions greater than size
    positions = positions % size;
    if (positions == 0) return;
    
    // Store first 'positions' elements (use static buffer for MSVC compatibility)
    #define MAX_ROTATE_BUFFER 256
    int temp[MAX_ROTATE_BUFFER];
    if (positions > MAX_ROTATE_BUFFER) {
        // For larger rotations, use reversal algorithm instead
        reverse_subarray(arr, 0, positions - 1);
        reverse_subarray(arr, positions, size - 1);
        reverse_subarray(arr, 0, size - 1);
        return;
    }
    for (int i = 0; i < positions; i++) {
        temp[i] = arr[i];
    }
    
    // Shift remaining elements left
    for (int i = 0; i < size - positions; i++) {
        arr[i] = arr[i + positions];
    }
    
    // Copy temp elements to end
    for (int i = 0; i < positions; i++) {
        arr[size - positions + i] = temp[i];
    }
}

/**
 * Rotate array right by specified positions
 * Time Complexity: O(n)
 * Space Complexity: O(k) where k is positions
 */
void rotate_right(int arr[], int size, int positions) {
    if (size == 0) return;
    
    // Handle positions greater than size
    positions = positions % size;
    if (positions == 0) return;
    
    // Store last 'positions' elements (use static buffer for MSVC compatibility)
    int temp[MAX_ROTATE_BUFFER];
    if (positions > MAX_ROTATE_BUFFER) {
        // For larger rotations, use reversal algorithm instead
        reverse_subarray(arr, 0, size - 1);
        reverse_subarray(arr, 0, positions - 1);
        reverse_subarray(arr, positions, size - 1);
        return;
    }
    for (int i = 0; i < positions; i++) {
        temp[i] = arr[size - positions + i];
    }
    
    // Shift elements right
    for (int i = size - 1; i >= positions; i--) {
        arr[i] = arr[i - positions];
    }
    
    // Copy temp elements to beginning
    for (int i = 0; i < positions; i++) {
        arr[i] = temp[i];
    }
}

/**
 * Find maximum element in array
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
int find_max(int arr[], int size) {
    if (size == 0) {
        printf("Error: Empty array\n");
        return -1;
    }
    
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

/**
 * Find minimum element in array
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
int find_min(int arr[], int size) {
    if (size == 0) {
        printf("Error: Empty array\n");
        return -1;
    }
    
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

/**
 * Merge two arrays into result array
 * Time Complexity: O(n + m)
 * Space Complexity: O(n + m)
 */
void merge_arrays(int arr1[], int size1, int arr2[], int size2, int result[]) {
    // Copy first array
    for (int i = 0; i < size1; i++) {
        result[i] = arr1[i];
    }
    
    // Copy second array
    for (int i = 0; i < size2; i++) {
        result[size1 + i] = arr2[i];
    }
}
